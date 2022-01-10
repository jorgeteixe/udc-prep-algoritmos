#include <stdlib.h>

#include "grafos.h"


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
        minx = INT8_MAX;
        for (i = 0; i < nodos; i++) {
            if (visitados[i] == 0 && distancias[i] < minx) {
                minx = distancias[i];
                mini = i;
            }
        }

        // visitamos el mínimo
        visitados[i] = 1;

        // calculamos mínimos
        for (i = 0; i < nodos; i++) {
            if (visitados[i] == 0) {
                distancias[i] = distancias[i] < distancias[mini] + m[mini][i]
                            ? distancias[i] 
                            : distancias[mini] + m[mini][i];
            }
        }
    }
    // hago el free peta luego asi que algo hago mal, 
    // da casi bien, es el ejemplo del ej2 que hicimos antes
    // free(visitados);
}
