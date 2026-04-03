from dataclasses import dataclass
from enum import Enum

class VehicleType(Enum):
    CAR = "CAR"
    MOTORCYCLE = "MOTORCYCLE"

@dataclass
class Vehicle:
    plate: str
    type: VehicleType