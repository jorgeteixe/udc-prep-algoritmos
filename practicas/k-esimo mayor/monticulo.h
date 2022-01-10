#include <stdlib.h>
#include <stdio.h>

#include "util.h"

#define MAX_TAM 256000

typedef struct Monticulo {
    int tamano_monticulo;
    int vector_monticulo[MAX_TAM];
} Monticulo;

void Inicializar_Monticulo(Monticulo *m);
int Monticulo_Vacio(Monticulo m);
void Flotar(Monticulo *m, int i);
void Insertar(int x, Monticulo *m);
int EliminarMax(Monticulo *m);
void Crear_Monticulo(const int vector_monticulo[MAX_TAM], int n, Monticulo *m);
