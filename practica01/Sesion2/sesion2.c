#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER 32
#define MAX_DOC 48

typedef enum { NORMAL = 0, URGENTE = 1 } Prioridad_t;

typedef enum 
{
    EN_COLA = 0,
    IMPRIMIENDO = 1,
    COMPLETADO = 2,
    CANCELADO = 3
} 
Estado_t;

typedef struct 
{
    int id;
    char usuario[MAX_USER];
    char documento[MAX_DOC];
    int paginas_total;
    int paginas_restantes;
    int copias;
    Prioridad_t prioridad;
    Estado_t estado;
    int ms_por_pagina;
} 
PrintJob_t;

typedef struct Nodo 
{
    PrintJob_t data;
    struct Nodo* next;
} 
Nodo_t;

typedef struct 
{
    Nodo_t* front;
    Nodo_t* rear;
    int size;
} 
QueueDynamic_t;

void menu();
void qd_init(QueueDynamic_t* q);
int qd_is_empty(const QueueDynamic_t* q);
int qd_enqueue(QueueDynamic_t* q, PrintJob_t job);
int qd_peek(const QueueDynamic_t* q, PrintJob_t* out);
int qd_dequeue(QueueDynamic_t* q, PrintJob_t* out);
void qd_print(const QueueDynamic_t* q);
void qd_destroy(QueueDynamic_t* q);
char *my_gets (char *cadena, int tam);
int validacion_num(int xi, int xf, const char msge[]);

int main() 
{
    menu();

    return 0;
}

void menu() 
{
    QueueDynamic_t cola;
    qd_init(&cola);
    
    int opcion;
    int id_counter = 1;
    PrintJob_t job_aux;

    do 
    {
        system("CLS"); 

        printf(" MENU COLA DE IMPRESION (DINAMICA)\n\n");
        printf(" 1.- Agregar trabajo (Enqueue)\n");
        printf(" 2.- Ver siguiente trabajo (Peek)\n");
        printf(" 3.- Procesar trabajo (Dequeue)\n");
        printf(" 4.- Mostrar cola completa\n");
        printf(" 0.- Salir\n");

        opcion = validacion_num(0, 4, " Elija la accion que desea realizar: ");

        switch (opcion) 
        {
            case 1:
                system("CLS");
                printf("AGREGAR TRABAJO\n\n");

                PrintJob_t nuevo_job;
                nuevo_job.id = id_counter++;
                
                printf("Usuario: ");
                my_gets(nuevo_job.usuario, MAX_USER);
                printf("Documento: ");
                my_gets(nuevo_job.documento, MAX_DOC);
                
                nuevo_job.paginas_total = validacion_num(1, 1000, "Numero de paginas: ");
                nuevo_job.paginas_restantes = nuevo_job.paginas_total;
                nuevo_job.copias = 1;
                nuevo_job.prioridad = NORMAL;
                nuevo_job.estado = EN_COLA;
                nuevo_job.ms_por_pagina = 300;

                if (qd_enqueue(&cola, nuevo_job)) 
                {
                    printf("\nTrabajo agregado con ID: %d\n", nuevo_job.id);
                }
                
                system("PAUSE");
                break;

            case 2:
                system("CLS");
                printf("SIGUIENTE TRABAJO EN ESPERA\n\n");

                if (qd_peek(&cola, &job_aux)) 
                {
                    printf("ID: %d\nUsuario: %s\nDocumento: %s\nPaginas: %d\n", job_aux.id, job_aux.usuario, job_aux.documento, job_aux.paginas_total);
                } 
                else 
                {
                    printf("La cola esta vacia.\n");
                }
                system("PAUSE");
                break;

            case 3:
                system("CLS");
                printf("PROCESANDO TRABAJO...\n\n");

                if (qd_dequeue(&cola, &job_aux)) 
                {
                    printf("Se ha procesado y liberado el ID %d (%s)\n", job_aux.id, job_aux.documento);
                } 
                else 
                {
                    printf("Nada que procesar, cola vacia.\n");
                }

                system("PAUSE");
                break;

            case 4:
                system("CLS");
                printf("LISTADO DE LA COLA\n\n");

                qd_print(&cola);
                printf("\n");

                system("PAUSE");
                break;

            case 0:
                qd_destroy(&cola);
                printf("\nMemoria liberada. Saliendo...\n");
                break;
        }
    } 
    while (opcion != 0);
}


void qd_init(QueueDynamic_t* q) 
{
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int qd_is_empty(const QueueDynamic_t* q) 
{
    return q->front == NULL;
}

int qd_enqueue(QueueDynamic_t* q, PrintJob_t job) 
{
    Nodo_t* nuevo = (Nodo_t*)malloc(sizeof(Nodo_t));

    if (nuevo == NULL) return 0;

    nuevo->data = job;
    nuevo->next = NULL;

    if (qd_is_empty(q)) 
    {
        q->front = nuevo;
    } 
    else 
    {
        q->rear->next = nuevo;
    }
    
    q->rear = nuevo;
    q->size++;

    return 1;
}

int qd_peek(const QueueDynamic_t* q, PrintJob_t* out) 
{
    if (qd_is_empty(q)) return 0;

    *out = q->front->data;

    return 1;
}

int qd_dequeue(QueueDynamic_t* q, PrintJob_t* out) 
{
    if (qd_is_empty(q)) return 0;

    Nodo_t* aux = q->front;
    *out = aux->data;

    q->front = q->front->next;

    if (q->front == NULL) 
    {
        q->rear = NULL;
    }

    free(aux);
    q->size--;

    return 1;
}

void qd_print(const QueueDynamic_t* q) 
{
    if (qd_is_empty(q)) 
    {
        printf("Cola vacia\n");
        return;
    }

    Nodo_t* actual = q->front;
    int i = 1;

    while (actual != NULL) 
    {
        printf("[%d] ID: %d | Usuario: %s | Pags: %d\n", i++, actual->data.id, actual->data.usuario, actual->data.paginas_total);
        actual = actual->next;
    }
}

void qd_destroy(QueueDynamic_t* q) 
{
    PrintJob_t temp;
    while (qd_dequeue(q, &temp));
}

char *my_gets (char *cadena, int tam)
{
    int len;

    fflush(stdin);
    fgets(cadena, tam, stdin);

    if (cadena)
    {
        len = strlen(cadena);

        if (len > 0)
        {
            if (cadena[len - 1] == '\n')
            {
                cadena[len - 1] = '\0';
            }
        }

        return cadena;
    }

    return NULL;
}

int validacion_num(int xi, int xf, const char msge[])
{
    char snum[30];
    int num = 0, valido = 0, i = 0;

    do
    {
        valido = 1;

        printf("%s", msge);
        my_gets(snum, 30);

        if (snum[0] == '\0')
        {
            printf("Entrada vacia\n");

            valido = 0;
        }
        else
        {
            i = 0;

            while (snum[i] != '\0')
            {
                if (snum[i] < '0' || snum[i] > '9')
                {
                    valido = 0;
                }

                i++;
            }

            if (valido == 1)
            {
                num = atoi(snum);

                if (num < xi || num > xf)
                {
                    printf("Fuera del rango\n");
                    
                    valido = 0;
                }
            }
            else
            {
                printf("Solo se permiten numeros\n");
            }
        }

    } 
    while (valido == 0);

    return num;
}