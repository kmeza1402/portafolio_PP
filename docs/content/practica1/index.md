+++
date = '2026-02-20T23:13:29-08:00'
draft = false
title = 'Practica1: Elementos basicos de los lenguajes de programacion'
+++

## __Introduccion__

El proyecto describe el desarrollo de un simulador de colas de impresion en lenguaje C, diseñado para administrar trabajos bajo una estructura FIFO (First-In, First-Out). Se tenia como objetivo es aplicar conceptos como el alcance de variables, la gestión de memoria estatica y dinamica, y la simulacion de procesos con estados y retrasos temporales.



## __Diseño__

### __Estructura de datos PrintJob_t__

- __id__: Identificador numérico unico para cada trabajo.
- __usuario__: Nombre del propietario del trabajo
- __documento__: Nombre del archivo a procesar
- __paginas_total__: Cantidad total de paginas del documento
- __paginas_restantes__: Variable que decrementa durante la simulación para reflejar el progreso de paginas ya impresas
- __estado__: Indica la fase actual del trabajo (EN_COLA, IMPRIMIENDO, COMPLETADO o CANCELADO)
- __ms_por_pagina__: Determina la velocidad de la simulacion mediante un retraso en milisegundos.

### __Estructura de la cola__

1. __Estatica (sesion 1)__: El almacenamiento se limito a un arreglo fijo de 10 elementos. Esta implementacion requiere el desplazamiento fisico de los datos en memoria cada vez que se procesa un elemento del frente.

2. __Dinamica (sesion 2 y 3)__: Se empleo una lista enlazada simple donde cada nodo es reservado en tiempo de ejecucion. Esta arquitectura optimiza el uso de recursos al no depender de un tamaño maximo predefinido.



## __Implementacion__

### __Catalogo de funciones__

#### __Gestion de memoria dinamica__

- __qd_init__: Establece los punteros front y rear en NULL y el tamaño en 0. Prepara la estructura para su uso inicial.
- __qd_is_empty__: Verifica si la cola carece de elementos. Es una medida de seguridad antes de cualquier operacion de lectura o extraccion.
- __qd_enqueue__: Reserva memoria en el Heap para un nuevo nodo, asigna los datos del trabajo y lo enlaza al final de la lista, actualizando el puntero rear.
- __qd_dequeue__: Extrae el elemento al frente. Copia los datos, reasigna el puntero front y libera fisicamente la memoria del nodo mediante free().
- __qd_peek__: Consulta los datos del primer trabajo en espera sin modificar los punteros ni eliminar el nodo de la estructura.
- __qd_print__: Recorre la lista de principio a fin para mostrar en consola el estado de todos los trabajos pendientes.
- __qd_destroy__: Libera de forma iterativa todos los nodos remanentes en el Heap al cerrar el programa, garantizando que no existan fugas de memoria.

#### __Simulacion y control__

- __simular_impresion__: Cambia el estado del trabajo a IMPRIMIENDO y ejecuta un bucle que reduce paginas_restantes una por una, actualizando el progreso visualmente.
- __delay_ms__: Utiliza el reloj del sistema para generar una pausa controlada en milisegundos, permitiendo que la simulación de impresion sea perceptible.

#### __Utilidades__

- __menu__: Gestiona el flujo principal del programa y la interaccion del usuario con las distintas funcionalidades.
- __my_gets__: Lee cadenas de texto de forma segura, eliminando el salto de linea y limpiando el buffer de entrada para evitar errores de lectura.
- __validacion_num__: Filtra la entrada del usuario para admitir solo digitos y asegurar que el valor este dentro de los rangos permitidos por el sistema.

### __Desciciones relevantes__

- __Manejo de NULL__: Todas las funciones de la cola verifican si front es nulo antes de operar, evitando fallos de segmentacion.
- __Validacion__: Se opto por limpiar el buffer con fflush(stdin) y procesar cadenas con my_gets para evitar errores comunes de scanf.



## __Demostracion de conceptos__

### __Alcance y duracion__

- __Local__: opcion dentro de menu(). Solo existe mientras la funcion se ejecuta.
- __Parámetro por valor__: El PrintJob_t job en qd_enqueue. Se crea una copia local al llamar a la funcion.
- __Puntero__: QueueDynamic_t* q. Permite que la funcion modifique la estructura original fuera de su ámbito local.

### __Memoria__

- __Stack__: Aquí viven las variables locales de menu() y los punteros de control. Es memoria de acceso rapido y gestion automatica.
- __Heap__: Los nodos (Nodo_t) se crean aquí mediante malloc(). Esta memoria es persistente.
- __Liberacion__: Se realiza explicitamente en qd_dequeue mediante free(aux) y de forma masiva en qd_destroy.

### __Subprogramas__

- __Punteros__: Se pasan punteros (*q) para evitar copiar toda la estructura de la cola en cada llamada y permitir modificaciones.
- __const__: En qd_print(const QueueDynamic_t* q), el calificador asegura que la funcion sea de "solo lectura", protegiendo la integridad de la lista.

### __Tipos de datos__

- __struct__: Justificado para agrupar variables de distinta naturaleza (int, char, enum) que pertenecen a una misma entidad lógica.
- __enum__: Utilizado para legibilidad semantica. Es mas claro comparar estado == COMPLETADO que usar numeros.


## __Simulacion__

### __Progreso por paginas__

El progreso no se realiza de forma instantanea; en su lugar, el sistema procesa el trabajo extraido de la cola mediante un ciclo. La funcion simular_impresion recibe un puntero al trabajo (PrintJob_t *job) y realiza lo siguiente:

```C

void simular_impresion(PrintJob_t* job) 
{
    job->estado = IMPRIMIENDO;

    printf(">> INICIANDO IMPRESION ID: %d <<\n", job->id);
    printf("Doc: %s | Usuario: %s\n\n", job->documento, job->usuario);

    while (job->paginas_restantes > 0) 
    {
        printf("Imprimiendo pagina %d de %d... ", (job->paginas_total - job->paginas_restantes) + 1, job->paginas_total);
        
        delay_ms(job->ms_por_pagina);
        job->paginas_restantes--;

        printf("OK\n");
    }

    job->estado = COMPLETADO;
    
    printf("\n--- TRABAJO FINALIZADO CON EXITO ---\n\n");
}

```
1. __Actualización de Estado__: El campo estado cambia de EN_COLA a IMPRIMIENDO.
2. __Ciclo de Ejecucion__: Se utiliza un bucle while que se repite mientras paginas_restantes > 0.
3. __Decremento de Atributos__: En cada iteracion, el atributo paginas_restantes se reduce en una unidad, simulando que avanza.

### __Implementación del Retraso__

Para que el progreso sea visible, se implemento la función delay_ms. Esta funcion utiliza la libreria <time.h> para consultar el reloj del procesador mediante clock().

```C

void delay_ms(int milisegundos) 
{
    clock_t start_time = clock();

    while (clock() < start_time + milisegundos * (CLOCKS_PER_SEC / 1000));
}

```

1. __Logica__: Se calcula el tiempo de finalizacion sumando el tiempo actual mas el intervalo deseado. El programa entra en una espera activa hasta que el reloj alcanza dicho valor.
2. __Visualizacion__: Por cada iteración del ciclo, la consola muestra una actualización del tipo "Imprimiendo pagina X de Y", seguida de una pausa controlada antes de continuar con la siguiente pagina.


## __Analisis comparativo: estatica vs dinamica__

### Introduccion

En el desarrollo de software, la eleccion de la estructura de datos adecuada influye directamente en el rendimiento y la eficiencia de un sistema. Un ejemplo comun donde esto se vuelve evidente es en los sistemas de gestion de impresion, los cuales utilizan el modelo de cola para organizar los trabajos que se envian a una impresora. Este tipo de sistema sigue el principio FIFO (First In, First Out), donde el primer trabajo que entra es el primero en ser procesado.

Existen varias formas de implementar una cola en el lenguaje C, pero dos de las mas utilizadas son la implementacion estatica mediante arreglos y la implementacion dinamica mediante listas enlazadas. En una primera etapa del sistema de impresion, la cola puede implementarse utilizando un arreglo de tamano fijo. Esta solucion es sencilla y facil de programar, pero presenta ciertas limitaciones relacionadas con el manejo de memoria y la escalabilidad.

La diferencia principal entre ambas implementaciones se relaciona con el segmento de memoria que utilizan. Las estructuras estaticas suelen almacenarse en el Stack, donde el tamano de la estructura se define desde el inicio del programa. Esto significa que la memoria reservada es fija y no puede cambiar durante la ejecucion. En cambio, las estructuras dinamicas utilizan el Heap, donde la memoria se asigna en tiempo de ejecucion mediante funciones como malloc(). Esta caracteristica permite que la estructura crezca o disminuya segun las necesidades del sistema.

En el caso de un sistema de impresion que evoluciona de una implementacion con arreglo fijo a una lista enlazada con punteros front y rear, se observa una mejora significativa en la flexibilidad del sistema y en la forma en que se administran los recursos de memoria.

### Gestion de Memoria y Escalabilidad

Uno de los principales factores que diferencian las implementaciones estaticas y dinamicas es la manera en que manejan la memoria. En una cola basada en un arreglo fijo, el programador debe definir previamente la capacidad maxima del sistema. Esto implica tomar una decision anticipada sobre cuantos trabajos de impresion podran almacenarse al mismo tiempo.

Si el arreglo es demasiado pequeno, el sistema puede experimentar un desbordamiento (overflow) cuando la cola alcanza su limite. Esto significa que nuevos trabajos de impresion no podran agregarse al sistema. Por otro lado, si se define un arreglo demasiado grande, parte de la memoria reservada podria quedar sin utilizar, generando un desperdicio innecesario de recursos.

En contraste, una implementacion dinamica mediante listas enlazadas permite que la cola crezca segun sea necesario. Cada elemento de la cola se representa mediante un nodo que contiene la informacion del trabajo de impresion y un puntero al siguiente nodo. Cuando llega un nuevo trabajo, el programa solicita memoria al Heap utilizando la funcion malloc(). De esta manera, el sistema solo utiliza la memoria que realmente necesita en ese momento.

Sin embargo, este enfoque tambien introduce ciertos costos adicionales conocidos como overhead, ya que cada nodo debe almacenar un puntero adicional. Ademas, el uso continuo de asignaciones y liberaciones de memoria puede provocar fragmentacion en el Heap, lo cual puede afectar la eficiencia del manejo de memoria a largo plazo.

### Eficiencia

Otro aspecto importante al comparar ambas implementaciones es el costo computacional de las operaciones principales de la cola, especialmente la operacion dequeue, que consiste en eliminar el primer elemento de la estructura.

En una implementacion basada en un arreglo no circular, la operacion dequeue tiene una complejidad temporal de O(n). Esto ocurre porque, al eliminar el primer elemento, todos los elementos restantes deben desplazarse una posicion hacia el inicio del arreglo para mantener el orden de la cola. Este proceso implica realizar multiples operaciones de copia, lo cual incrementa el tiempo de ejecucion a medida que aumenta el numero de elementos.

Por el contrario, en una lista enlazada la operacion dequeue tiene una complejidad de O(1). En este caso, eliminar el primer nodo solo requiere actualizar el puntero front para que apunte al siguiente nodo de la lista. No es necesario mover otros elementos ni realizar desplazamientos en memoria. Gracias a este re-enlace de punteros, la operacion se ejecuta en tiempo constante independientemente del tamano de la cola.

### Robustez y Seguridad

Desde la perspectiva de robustez del sistema, cada tipo de implementacion presenta riesgos diferentes. En una estructura estatica basada en arreglos, el problema principal es el desbordamiento de la cola cuando se alcanza su capacidad maxima. Si el programa no maneja adecuadamente esta situacion, el sistema podria perder trabajos de impresion o generar errores en tiempo de ejecucion.

Por otro lado, las estructuras dinamicas presentan un riesgo distinto relacionado con la gestion de memoria. Si los nodos eliminados de la cola no liberan correctamente la memoria utilizando la funcion free(), se producen memory leaks o fugas de memoria. Con el tiempo, estas fugas pueden consumir una cantidad significativa de memoria del sistema y afectar el rendimiento general de la aplicacion.

Por esta razon, en las implementaciones dinamicas es fundamental liberar la memoria de cada nodo eliminado, asegurando que el programa mantenga un uso eficiente de los recursos del sistema.

### Conclusion

Ambas implementaciones tienen ventajas y desventajas dependiendo del contexto en el que se utilicen. Las colas estaticas basadas en arreglos suelen ser apropiadas en sistemas embebidos o aplicaciones donde el limite de elementos es conocido y la memoria disponible es restringida. En estos casos, la simplicidad de la implementacion puede resultar beneficiosa.

En cambio, las colas dinamicas basadas en listas enlazadas son mas adecuadas para aplicaciones de proposito general donde el numero de elementos puede variar considerablemente. Su capacidad de crecer dinamicamente y su eficiencia en operaciones como dequeue las convierten en una solucion mas flexible para sistemas como los gestores de impresion.


## __Conclusiones__

Se logró comprender la importancia de la abstracción de datos mediante el uso de structs y enums, lo que facilita la lectura y el mantenimiento del código. Asimismo, la práctica reforzó la habilidad para gestionar manualmente el ciclo de vida de la memoria, identificando claramente cuándo un recurso debe ser reservado en el heap y cuándo debe ser liberado para evitar la saturación del sistema.

### __Mejoras__
- __Cola de Prioridad__: Implementar un algoritmo que inserte los trabajos con Prioridad_t URGENTE al inicio de la cola, independientemente de su orden de llegada.
- __Persistencia de Datos__: Añadir una función para guardar el historial de trabajos completados en un archivo de texto o binario.
- __Interfaz Grafica__: Migrar la visualización de consola a una biblioteca como Raylib para representar visualmente el avance de las paginas con barras de progreso.


## __Referencias__

- GeeksforGeeks. (2023, 22 de agosto). Queue Data Structure. https://www.geeksforgeeks.org/queue-data-structure/
- Microsoft Learn. (2023, 14 de junio). C Storage Classes: auto, register, static, and extern. https://learn.microsoft.com/en-us/cpp/c-language/c-storage-classes
- Programiz. (s.f.). C Dynamic Memory Allocation: malloc, calloc, free and realloc. https://www.programiz.com/c-programming/c-dynamic-memory-allocation
- TutorialsPoint. (s.f.). C - Structures and Unions. https://www.tutorialspoint.com/cprogramming/c_structures.htm
- IBM Documentation. (2021, 23 de marzo). The const variable qualifier. https://www.ibm.com/docs/en/zos/2.4.0?topic=qualifiers-const-variable-qualifier


## __Mis Enlaces__
* **Mi Portafolio en GitHub:** [https://github.com/kmeza1402/portafolio_PP]
* **Mi Página en Vivo:** [https://kmeza1402.github.io/portafolio_PP/practica1/]

