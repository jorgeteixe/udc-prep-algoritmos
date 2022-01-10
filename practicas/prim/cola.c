#include "cola.h"

void incrementar(int *x) {
    if (++(*x) == TAM_MAX)
        *x = 0;
}

void crear_cola(cola *c) {
    c->cabeza = 0;
    c->final = -1;
    c->tamano = 0;
}

int cola_vacia(cola c) {
    return c.tamano == 0;
}

void insertar(tipo_elemento x, cola *c) {
    if (c->tamano == TAM_MAX) {
        printf("error: cola llena: %d\n", c->tamano);
        exit(EXIT_FAILURE);
    }
    c->tamano++;
    incrementar(&(c->final));
    c->vector[c->final] = x;
}

tipo_elemento quitar_primero(cola *c) {
    tipo_elemento x;
    if (cola_vacia(*c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    c->tamano--;
    x = c->vector[c->cabeza];
    incrementar(&(c->cabeza));
    return x;
}

tipo_elemento primero(cola c) {
    if (cola_vacia(c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    return (c.vector[c.cabeza]);
}

void mostrar_cola(cola c) {
    int i = c.cabeza, n, total = 0;
    arista a;
    printf("Aristas: ");
    for (n = 0; n < c.tamano; n++) {
        a = c.vector[i];
        printf("(%d,%d) ", a.x, a.y);
        total += a.peso;
        i = (i + 1) % TAM_MAX;
    }
    printf("\nPeso total: %d\n", total);
}
