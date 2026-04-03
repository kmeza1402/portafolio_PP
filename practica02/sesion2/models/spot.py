class ParkingSpot:
    def __init__(self, spot_id: str, allowed_type):
        self.__spot_id = spot_id
        self.__allowed_type = allowed_type
        self.__occupied = False
        self.__vehicle = None

    def is_available(self, vehicle) -> bool:
        if self.__occupied:
            return False
        return self.__allowed_type == vehicle.type

    def occupy(self, vehicle):
        self.__vehicle = vehicle
        self.__occupied = True

    def release(self):
        self.__vehicle = None
        self.__occupied = False

    @property
    def spot_id(self):
        return self.__spot_id