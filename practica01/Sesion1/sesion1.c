#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER 32
#define MAX_DOC 48
#define MAX_JOBS 10

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

typedef struct 
{
    PrintJob_t data[MAX_JOBS];
    int size;
} 
QueueStatic_t;

void menu();
void qs_init(QueueStatic_t* q);
int qs_is_empty(const QueueStatic_t* q);
int qs_is_full(const QueueStatic_t* q);
int qs_enqueue(QueueStatic_t* q, PrintJob_t job);
int qs_peek(const QueueStatic_t* q, PrintJob_t* out);
int qs_dequeue(QueueStatic_t* q, PrintJob_t* out);
void qs_print(const QueueStatic_t* q);
char *my_gets (char *cadena, int tam);
int validacion_num(int xi, int xf, const char msge[]);

int main() 
{
    menu();

    return 0;
}


void menu() 
{
    QueueStatic_t cola;

    qs_init(&cola);
    
    int opcion;
    int id_counter = 1;
    PrintJob_t job_aux;

    do 
    {
        system("CLS"); 

        printf(" MENU COLA DE IMPRESION\n\n");
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

                if (qs_is_full(&cola)) 
                {
                    printf("Error: La cola esta llena.\n");
                } 
                else 
                {
                    PrintJob_t nuevo_job;
                    nuevo_job.id = id_counter++;
                    
                    printf("Usuario: ");
                    my_gets(nuevo_job.usuario, 50);
                    printf("Documento: ");
                    my_gets(nuevo_job.documento, 50);
                    
                    nuevo_job.paginas_total = validacion_num(1, 1000, "Numero de paginas: ");
                    nuevo_job.paginas_restantes = nuevo_job.paginas_total;
                    nuevo_job.copias = 1;
                    nuevo_job.prioridad = NORMAL;
                    nuevo_job.estado = EN_COLA;
                    nuevo_job.ms_por_pagina = 300;

                    qs_enqueue(&cola, nuevo_job);
                    printf("\nTrabajo agregado exitosamente con ID: %d\n", nuevo_job.id);
                }
                
                system("PAUSE");
                break;

            case 2:
                system("CLS");
                printf("SIGUIENTE TRABAJO EN ESPERA\n\n");

                if (qs_peek(&cola, &job_aux)) 
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

                if (qs_dequeue(&cola, &job_aux)) 
                {
                    printf("Se ha procesado el ID %d (%s)\n", job_aux.id, job_aux.documento);
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

                qs_print(&cola);

                printf("\n");

                system("PAUSE");
                break;

            case 0:
                printf("\nSaliendo del sistema de impresion...\n");
                break;
        }
    } 
    while (opcion != 0);
}

void qs_init(QueueStatic_t* q) 
{
    q->size = 0;
}

int qs_is_empty(const QueueStatic_t* q) 
{
    return q->size == 0;
}

int qs_is_full(const QueueStatic_t* q) 
{
    return q->size == MAX_JOBS;
}

int qs_enqueue(QueueStatic_t* q, PrintJob_t job) 
{
    if (qs_is_full(q)) return 0;

    q->data[q->size] = job;
    q->size++;

    return 1;
}

int qs_peek(const QueueStatic_t* q, PrintJob_t* out) 
{
    if (qs_is_empty(q)) return 0;

    *out = q->data[0];

    return 1;
}

int qs_dequeue(QueueStatic_t* q, PrintJob_t* out) 
{
    if (qs_is_empty(q)) return 0;

    *out = q->data[0];

    for (int i = 1; i < q->size; i++) 
    {
        q->data[i - 1] = q->data[i];
    }
    q->size--;

    return 1;
}

void qs_print(const QueueStatic_t* q) 
{
    if (qs_is_empty(q)) 
    {
        printf("Cola vacia\n");

        return;
    }

    for (int i = 0; i < q->size; i++) 
    {
        printf("[%d] ID: %d | Usuario: %s | Pags: %d\n", i+1, q->data[i].id, q->data[i].usuario, q->data[i].paginas_total);
    }
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

    } while (valido == 0);

    return num;
}