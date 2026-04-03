from flask import Flask, render_template, request
from models.parking_lot import ParkingLot
from models.rates import HourlyRatePolicy

app = Flask(__name__)

# Configuración del Modelo (Lógica de Negocio)
# Se define la política de cobro (Abstracción) y se inyecta al estacionamiento
politica = HourlyRatePolicy(car_rate=15.0, moto_rate=10.0)
estacionamiento = ParkingLot(politica)

@app.route('/')
def index():
    """Ruta de inicio: Muestra el menú principal (Vista)"""
    return render_template('index.html')

@app.route('/ingreso', methods=['GET', 'POST'])
def ingreso():
    """Controlador para el registro de entrada"""
    if request.method == 'GET':
        return render_template('ingreso.html')
    
    # Procesamiento de datos (POST)
    placa = request.form.get('placa')
    tipo = request.form.get('tipo')
    
    ticket = estacionamiento.registrar_entrada(placa, tipo)
    
    if ticket:
        res = f"Registro Exitoso: Ticket #{ticket['id']} en el lugar {ticket['s'].spot_id}"
        return f"<h2>{res}</h2><a href='/'>Volver al inicio</a>"
    
    return "<h2>Error: No hay cajones disponibles para este tipo de vehículo.</h2><a href='/ingreso'>Reintentar</a>"

@app.route('/cobro', methods=['GET', 'POST'])
def cobro():
    """Controlador para el procesamiento de salida y cobro"""
    if request.method == 'GET':
        return render_template('cobro.html')
    
    # Procesamiento de datos (POST)
    try:
        t_id = int(request.form.get('id'))
        hrs = float(request.form.get('horas'))
        
        total = estacionamiento.registrar_salida(t_id, hrs)
        
        if total is not None:
            res = f"Cobro Realizado: El total a pagar es de ${total:.2f} MXN"
            return f"<h2>{res}</h2><a href='/'>Volver al inicio</a>"
            
        return "<h2>Error: El ID de ticket no existe o ya fue liberado.</h2><a href='/cobro'>Reintentar</a>"
        
    except ValueError:
        return "<h2>Error: Ingrese valores numéricos válidos.</h2><a href='/cobro'>Reintentar</a>"

if __name__ == "__main__":
    # Ejecución del servidor en modo desarrollo
    app.run(debug=True)