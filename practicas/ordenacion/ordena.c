#include "ordena.h"


/* HELPERS */

int mediana3(int V[], int i, int j) {
    int k = (i + j) / 2;

    if (V[k] > V[j]) intercambiar(&V[k], &V[j]);
    if (V[k] > V[i]) intercambiar(&V[k], &V[i]);
    if (V[i] > V[j]) intercambiar(&V[i], &V[j]);

    return v[i];
}

void piv_aleatorio(int V[], int i, int j) {
    return srand() % (j - i + 1);
}

void rapida(int V[], int izq, int der) {
    int pivote, i, j;
    if (izq + UMBRAL <= der) {
        // pivote = piv_aleatorio(V, izq, der); // <- pivote aleatorio
        // pivote = V[izq]; // <- primer valor del vector
        pivote = mediana3(V, izq, der);
        i = izq;
        j = der;
        do {
            do { i++; } while (V[i] < pivote);
            do { j--; } while (V[j] > pivote);
            intercambiar(&V[i], &V[j]);
        } while (j > i);
        intercambiar(&V[i], &V[j]);
        intercambiar(&V[izq], &V[j]);
        rapida(V, izq, j - 1);
        rapida(V, j + 1, der);
    }
}

void fusion(int v[], int izq, int dch, int centro) {
    int aux_tam = dch - izq + 1;
    int aux[aux_tam];
    int i = izq;
    int j = centro + 1;
    int k = izq;
    while (i <= centro && j <= dch) {
        if (v[i] <= v[j]) {
            aux[izq - k] = v[i];
            i++;
        } else {
            aux[izq - k] = v[j];
            j++;
        }
        k++;
    }
    while (i <= centro) {
        aux[izq - k] = v[i];
        i++;
        k++;
    }
    while (j <= dch) {
        aux[izq - k] = v[j];
        j++;
        k++;
    }
    for (k = izq; k <= dch; k++) {
        v[k] = aux[izq - k];
    }
}

void fusion_recursivo(int v[], int izq, int dch) {
    int centro;
    if (izq + UMBRAL < dch) {
        centro = (izq + dch) / 2;
        fusion_recursivo(v, izq, centro);
        fusion_recursivo(v, centro + 1, dch);
        fusion(v, izq, dch, centro);
    } else {
        ordena_insercion(v + izq, dch - izq + 1);
    }
}



/* ALGORITMOS ORDENACIÓN */

void ordena_seleccion(int v[], int n) {
    int j, i, minj, minx;
    for (i = 0; i < n; i++) {
        minj = i;
        minx = v[i];
        for (j = i + 1; j < n; j++) {
            if (v[j] < minx) {
                minj = j;
                minx = v[j];
            }
        }
        v[minj] = v[i];
        v[i] = minx;
    }
}

void ordena_shell(int v[], int n) {
    int incremento = n, tmp, seguir, j, i;
    do {
        // CHANGEME: si se pide cambiar los incrementos
        incremento = incremento / 2;
        for (i = incremento; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = 1;
            while (j - incremento + 1 > 0 && seguir == 1) {
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                } else { seguir = 0; }
            }
            v[j] = tmp;
        }
    } while (incremento != 1);
}

void ordena_insercion(int v[], int n) {
    int x, j, i;
    for (i = 0; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void ordena_rapida(int v[], int n) {
    rapida(v, 0, n - 1);
    if (UMBRAL > 1) {
        ordena_insercion(v, n);
    }
}

void ordena_monticulos(int v[], int n) {
    int i, tam;
    Monticulo m;
    Inicializar_Monticulo(&m);
    Crear_Monticulo(v, n, &m);
    tam = m.tamano_monticulo;
    for (i = 0; i < tam; i++) {
        v[tam - i - 1] = EliminarMax(&m);
    }
}

void ordena_fusion(int v[], int n) {
    fusion_recursivo(v, 0, n - 1);
}