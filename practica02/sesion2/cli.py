from models.parking_lot import ParkingLot
from models.rates import HourlyRatePolicy

def menu():
    politica = HourlyRatePolicy(car_rate=15.0, moto_rate=10.0)
    estacionamiento = ParkingLot(politica)

    while True:
        print("\n1. Entrada\n2. Salida\n3. Salir")
        op = input("Seleccione: ")

        if op == "1":
            p = input("Placa: ")
            t = input("Tipo (1. Carro, 2. Moto): ")
            res = estacionamiento.registrar_entrada(p, t)
            if res: print(f"Ticket #{res['id']} en {res['s'].spot_id}")
            if not res: print("Sin espacio")

        if op == "2":
            tid = int(input("ID Ticket: "))
            h = float(input("Horas: "))
            costo = estacionamiento.registrar_salida(tid, h)
            if costo is not None: print(f"Total: ${costo}")

        if op == "3":
            break

if __name__ == "__main__":
    menu()