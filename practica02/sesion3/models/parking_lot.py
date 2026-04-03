from .spot import ParkingSpot
from .vehicle import Vehicle, VehicleType

class ParkingLot:
    def __init__(self, policy):
      
        self.__spots = [
            ParkingSpot("A1", VehicleType.CAR),
            ParkingSpot("M1", VehicleType.MOTORCYCLE)
        ]
        self.__active_tickets = {}
        self.__policy = policy
        self.__next_id = 1

    def registrar_entrada(self, placa: str, tipo_num: str):
        v_type = VehicleType.CAR
        if tipo_num == "2":
            v_type = VehicleType.MOTORCYCLE
        
        vehiculo = Vehicle(placa, v_type)
        
        for spot in self.__spots:
            if spot.is_available(vehiculo):
                spot.occupy(vehiculo)
                ticket = {"id": self.__next_id, "v": vehiculo, "s": spot}
                self.__active_tickets[self.__next_id] = ticket
                self.__next_id += 1
                return ticket
        return None

    def registrar_salida(self, ticket_id: int, horas: float):
        if ticket_id not in self.__active_tickets:
            return None
        
        ticket = self.__active_tickets.pop(ticket_id)
        
        costo = self.__policy.calculate(horas, ticket["v"])
        ticket["s"].release()
        return costo