#include <stdlib.h>
#include <limits.h>

#include "grafos.h"

int min(int a, int b) {
    return a < b ? a : b;
}

void dijkstra_normal(matriz m, int nodos, int *distancias) {
    int i, j, minx, mini;
    int *visitados = malloc(sizeof (int) * nodos);

    // inicializamos
    for (i = 0; i < nodos; i++) {
        visitados[i] = 0;
        distancias[i] = m[0][i];
    }

    // empezamos por el primero
    visitados[0] = 1;

    // bucle voraz
    for (j = 1; j < nodos; j++) {
        // buscamos distancia mínima a un nodo no visitado
        // (camino especial mínimo)
        minx = INT_MAX;
        for (i = 0; i < nodos; i++) {
            if (visitados[i] == 0 && distancias[i] < minx) {
                minx = distancias[i];
                mini = i;
            }
        }

        // visitamos el mínimo
        visitados[mini] = 1;

        // calculamos mínimos
        for (i = 0; i < nodos; i++) {
            if (visitados[i] == 0) {
                distancias[i] = min(distancias[i],
                                    distancias[mini] + m[mini][i]);
            }
        }
    }
    free(visitados);
}
