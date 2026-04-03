from typing import Protocol
from .vehicle import VehicleType

class RatePolicy(Protocol):
    def calculate(self, hours: float, vehicle) -> float:
        ...

class HourlyRatePolicy:
    def __init__(self, car_rate: float, moto_rate: float):
        self.__car_rate = car_rate
        self.__moto_rate = moto_rate

    def calculate(self, hours: float, vehicle) -> float:
        if vehicle.type == VehicleType.CAR:
            return hours * self.__car_rate
        return hours * self.__moto_rate