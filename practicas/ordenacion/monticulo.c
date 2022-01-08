#include "monticulo.h"

void Inicializar_Monticulo(Monticulo *m) {
    m->tamano_monticulo = 0;
}

int Monticulo_Vacio(Monticulo m) {
    return m.tamano_monticulo == 0;
}

void Flotar(Monticulo *m, int i) {
    while (i > 0 && m->vector_monticulo[i / 2] < m->vector_monticulo[i]) {
        intercambiar(&m->vector_monticulo[i / 2], &m->vector_monticulo[i]);
        i /= 2;
    }
}

void Insertar(int x, Monticulo *m) {
    if (m->tamano_monticulo == MAX_TAM) {
        exit(1);
    }
    m->vector_monticulo[m->tamano_monticulo] = x;
    m->tamano_monticulo++;
    Flotar(m, m->tamano_monticulo);
}

void Hundir(Monticulo *m, int i) {
    int HijoIzq, HijoDer, j;
    do {
        HijoIzq = 2 * i;
        HijoDer = 2 * i + 1;
        j = i;
        if (HijoDer < m->tamano_monticulo 
            && m->vector_monticulo[HijoDer] > m->vector_monticulo[i]) {
            i = HijoDer;
        }
        if (HijoIzq < m->tamano_monticulo 
            && m->vector_monticulo[HijoIzq] > m->vector_monticulo[i]) {
            i = HijoIzq;
        }
        intercambiar(&m->vector_monticulo[i], &m->vector_monticulo[j]);
    } while (j != i);
}

int EliminarMax(Monticulo *m) {
    int x;
    if (Monticulo_Vacio(*m)) {
        exit(1);
    }
    x = m->vector_monticulo[0];
    m->vector_monticulo[0] = m->vector_monticulo[--m->tamano_monticulo];
    if (m->tamano_monticulo > 0) {
        Hundir(m, 0);
    }
    return x;
}

void Crear_Monticulo(const int vector_monticulo[MAX_TAM], int n,
                    Monticulo *m) {
    int i;
    for (i = 0; i < n; i++) {
        m->vector_monticulo[i] = vector_monticulo[i];
    }
    m->tamano_monticulo = n;
    for (i = m->tamano_monticulo / 2; i >= 0; i--) {
        Hundir(m, i);
    }
}
