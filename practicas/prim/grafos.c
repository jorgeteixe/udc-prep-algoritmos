#include <math.h>
#include "grafos.h"


void prim(matriz m, int nodos, cola *aristas) {
/* calcular el árbol de recubrimiento mínimo devolviendo
las aristas del arbol en la cola ’aristas’ */
    int min, i, j, k;
    arista a;
    int *masProximo = (int *) malloc(nodos * sizeof(int));
    int *distanciaMinima = (int *) malloc(nodos * sizeof(int));
    crear_cola(aristas);
    distanciaMinima[0] = -1;
    for (i = 1; i < nodos; i++) {
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }

    for (i = 0; i < nodos - 1; i++) {       // Bucle Voraz
        min = INFINITO;
        for (j = 1; j < nodos; j++) {
            if ((0 <= distanciaMinima[j]) && (distanciaMinima[j] < min)) {
                min = distanciaMinima[j];
                k = j;
            }
        }
        a.x = masProximo[k];
        a.y = k;
        a.peso = m[a.x][a.y];
        insertar(a, aristas);
        distanciaMinima[k] = -1;
        for (j = 1; j < nodos; j++) {
            if (m[j][k] < distanciaMinima[j]) {
                distanciaMinima[j] = m[j][k];
                masProximo[j] = k;
            }
        }
    }
    free(masProximo);
    free(distanciaMinima);
}
