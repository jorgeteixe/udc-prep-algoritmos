#include <stdlib.h>
#include <stdio.h>

#define INFINITO 1601

typedef int ** matriz;

void print_matrix(matriz, int);
matriz crear_matriz(int);
void inicializar_matriz(matriz, int);
void liberar_matriz(matriz, int);
