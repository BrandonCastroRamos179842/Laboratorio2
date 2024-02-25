#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AUTOS 100

typedef struct {
    char nombre[50];
    char placas[10];
    int modelo;
} Automovil;

typedef struct Nodo {
    Automovil auto_obj;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *primero;
    Nodo *ultimo;
    int cantidad;
} Cola;

void inicializarCola(Cola *cola) {
    cola->primero = NULL;
    cola->ultimo = NULL;
    cola->cantidad = 0;
}

int colaVacia(Cola *cola) {
    return cola->cantidad == 0;
}

void encolar(Cola *cola, Automovil nuevoAuto) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nuevo->auto_obj.nombre, nuevoAuto.nombre);
    strcpy(nuevo->auto_obj.placas, nuevoAuto.placas);
    nuevo->auto_obj.modelo = nuevoAuto.modelo;
    nuevo->siguiente = NULL;

    if (colaVacia(cola)) {
        cola->primero = nuevo;
    } else {
        cola->ultimo->siguiente = nuevo;
    }

    cola->ultimo = nuevo;
    cola->cantidad++;
}

void desencolar(Cola *cola) {
    if (!colaVacia(cola)) {
        Nodo *temp = cola->primero;
        cola->primero = cola->primero->siguiente;
        free(temp);
        cola->cantidad--;
    } else {
        printf("Error: la cola esta vacia\n");
    }
}

Automovil primero(Cola *cola) {
    Automovil autoVacio = {"", "", 0};
    if (colaVacia(cola)) {
        printf("Error: la cola esta vacia\n");
        return autoVacio;
    } else {
        return cola->primero->auto_obj;
    }
}

Automovil ultimo(Cola *cola) {
    Automovil autoVacio = {"", "", 0};
    if (colaVacia(cola)) {
        printf("Error: la cola esta vacia\n");
        return autoVacio;
    } else {
        return cola->ultimo->auto_obj;
    }
}

void imprimirAuto(Automovil autoObj) {
    printf("Nombre: %s\n", autoObj.nombre);
    printf("Placas: %s\n", autoObj.placas);
    printf("Modelo: %d\n", autoObj.modelo);
    printf("\n");
}

void imprimirCola(Cola *cola) {
    Nodo *temp = cola->primero;
    while (temp != NULL) {
        imprimirAuto(temp->auto_obj);
        temp = temp->siguiente;
    }
}

int main() {
    Cola cola;
    inicializarCola(&cola);
    int opcion;

    do {
        printf("\n1) Imprimir la cantidad de autos en el estacionamiento\n");
        printf("2) Imprimir la lista de autos en el estacionamiento en orden\n");
        printf("3) Imprimir el primer auto que ingreso (caracteristicas)\n");
        printf("4) Imprimir el ultimo auto que ingreso (caracteristicas)\n");
        printf("5) Ingresar un nuevo auto al estacionamiento\n");
        printf("6) Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Cantidad de autos en el estacionamiento: %d\n", cola.cantidad);
                break;
            case 2:
                if (colaVacia(&cola)) {
                    printf("La cola esta vacia. No hay autos en el estacionamiento.\n");
                } else {
                    printf("Lista de autos en el estacionamiento:\n");
                    imprimirCola(&cola);
                }
                break;
            case 3:
                printf("Primer auto que ingreso:\n");
                imprimirAuto(primero(&cola));
                break;
            case 4:
                printf("Ultimo auto que ingreso:\n");
                imprimirAuto(ultimo(&cola));
                break;
            case 5:
                {
                    Automovil nuevoAuto;
                    printf("Ingrese el nombre del auto: ");
                    scanf("%s", nuevoAuto.nombre);
                    printf("Ingrese las placas del auto: ");
                    scanf("%s", nuevoAuto.placas);
                    printf("Ingrese el modelo del auto: ");
                    scanf("%d", &nuevoAuto.modelo);
                    encolar(&cola, nuevoAuto);
                    printf("Auto ingresado al estacionamiento.\n");
                }
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Ingrese nuevamente.\n");
        }

    } while (opcion != 6);

    while (!colaVacia(&cola)) {
        desencolar(&cola);
    }

    return 0;
}
