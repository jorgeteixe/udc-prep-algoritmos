#include "util.h"

void rellena_aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++) {
        v[i] = (rand() % m) - n;
    }
}

void rellena_ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
}

void rellena_descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i - 1;
    }
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return t.tv_usec + t.tv_sec * 1000000.0;
}

void listar_vector(int v[], int n) {
    int k;
    printf("[");
    for (k = 0; k < n; k++) {
        if (v[k] == INFINITO) {
            printf("  ∞ ");
        } else {
            printf("%3d ", v[k]);
        }
    }
    printf("]\n");
}

void inicializar_semilla() {
    srand(time(NULL));
}

int ordenado(int v[], int n) {
    int i = 0;
    while ((i < n - 1)) {
        if (v[i] > v[i + 1]) {
            return 0;
        }
        i++;
    }
    return 1;
}

void intercambiar(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}
