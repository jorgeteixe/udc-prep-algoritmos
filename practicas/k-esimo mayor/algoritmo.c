#include "algoritmo.h"

int kesimo_mayor(int v[], int n, int k) {
    Monticulo m;
    int i, x;

    Crear_Monticulo(v, n, &m);
    for (i = 0; i < k; i++) {
        x = EliminarMax(&m);
    }

    return x;
}
