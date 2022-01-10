#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void rellena_aleatorio(int v[], int n);

void rellena_ascendente(int v[], int n);

void rellena_descendente(int v[], int n);

void listar_vector(int v[], int n);

int ordenado(int v[], int n);

void inicializar_semilla();

double microsegundos();

void intercambiar(int *x, int *y);

void ordena_insercion(int v[], int n);
