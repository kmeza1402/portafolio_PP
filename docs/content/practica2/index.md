+++
date = '2026-02-20T23:15:19-08:00'
draft = true
title = 'Practica2: El paradigma orientado a objetos'
+++

## __Introduccion__

### __Contexto del Problema__
La gestión de un estacionamiento demanda un control riguroso sobre la disponibilidad de espacios y la aplicación de tarifas dinámicas según la categoría del vehículo. Los procesos manuales suelen presentar inconsistencias en la asignación de cajones (ej. permitir un automóvil en un área exclusiva para motocicletas) y errores en el cálculo de importes por tiempo de estancia.

### __Objetivos__
- Desarrollar un sistema de gestión integral utilizando el paradigma de Programación Orientada a Objetos (POO).
- Validar la implementación de los pilares de la POO: Encapsulación, Herencia, Polimorfismo y Abstracción.
- Estructurar la solución bajo el patrón de arquitectura Modelo-Vista-Controlador (MVC) utilizando el micro-framework Flask.


## __Modelo del Dominio__

### __Diagrama UML__
El diseño arquitectónico se fundamenta en una jerarquía de vehículos y una relación de composición con los espacios de estacionamiento, mediada por una abstracción de políticas de cobro.

### __Lista de Clases y Responsabilidades__
Vehicle (Clase Base): Entidad abstracta que centraliza los atributos comunes como la placa y el tipo.

- __Car / Motorcycle (Subtipos):__ Implementaciones concretas que permiten aplicar reglas de negocio específicas.
- __ParkingSpot:__ Responsable de gestionar su estado de ocupación y validar la compatibilidad técnica del vehículo entrante.
- __ParkingLot (Controlador de Dominio):__ Orquestador principal que administra la colección de cajones, gestiona la entrada/salida y la persistencia en memoria.
- __RatePolicy (Interfaz):__ Abstracción que define el contrato para el cálculo de costos, desacoplando la lógica financiera del núcleo del sistema.


## __Evidencia de Conceptos POO__

1. __Encapsulación:__
Se implementó mediante el uso de atributos privados (prefijo __), asegurando que el estado interno solo sea modificable a través de métodos públicos que validan la operación.

```Python

def occupy(self, vehicle):
    if self.__occupied:
        return False 
    self.__vehicle = vehicle
    self.__occupied = True
    return True

```

2. __Abstracción:__
Se utilizó typing.Protocol para definir la política de cobro. El sistema interactúa con la interfaz sin conocer la implementación interna de las tarifas.

```Python

class RatePolicy(Protocol):
    def calculate(self, hours: float, vehicle: Vehicle) -> float:

```

3. __Composicion:__
La clase ParkingLot no hereda de los espacios, sino que se compone de una colección de objetos ParkingSpot, delegando en ellos la gestión de su propio estado.

```Python

class ParkingLot:
    def __init__(self, policy):
        self.__spots = [ParkingSpot("A1", VehicleType.CAR), ...]

```

4. __Herencia y Subtipos:__
Se extendió la funcionalidad de Vehicle para crear categorías especializadas, permitiendo que el sistema realice búsquedas de cajones basadas en el tipo de objeto.

```Python

class Car(Vehicle):
    def __init__(self, plate: str):
        super().__init__(plate, VehicleType.CAR)

```

5. __Polimorfismo:__
El método de cálculo de tarifa reacciona dinámicamente al tipo de vehículo procesado, aplicando costos diferenciados bajo una misma firma de método.

```Python

def calculate(self, hours: float, vehicle: Vehicle) -> float:
    if vehicle.type == VehicleType.CAR:
        return hours * 15.0 
    return hours * 10.0

```