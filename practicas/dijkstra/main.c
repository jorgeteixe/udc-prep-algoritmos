#include <stdio.h>
#include <math.h>
#include "grafos.h"

typedef struct cota {
    char* nombre;
    double (*f)(int, double);
} cota;

typedef struct algoritmo {
    char* nombre;
    void (*f)(matriz m, int n, int *minimo);
    cota cota_inferior;
    cota cota_acotada;
    cota cota_superior;
} algoritmo;

void generar_ns(int ns[], int filas, int primer_n) {
    int i, n = primer_n;
    for (i = 0; i < filas; ++i) {
        ns[i] = n;
        n = n * 2;
    }
}

double tiempo(algoritmo algo, int n, matriz m, int minimos[]) {
    int i, k = 1000;
    double ta, tb, t1, t2, t;

    // medición normal
    inicializar_matriz(m, n);
    ta = microsegundos();
    algo.f(m, n, minimos);
    tb = microsegundos();
    t = tb - ta;

    // medición si el tiempo es muy rápido, media de 1000 veces
    if (t < 500) {
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            inicializar_matriz(m, n);
            algo.f(m, n, minimos);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            inicializar_matriz(m, n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        return (t1 - t2) / k;
    }
    return t;
}

void imprimir_tabla(int ns[], double ts[], double inf[], double aco[],
                    double sup[], int filas,
                    algoritmo ordena) {
    int i;
    printf("[+] Caminos mínimos: %s.\n", ordena.nombre);
    printf("%10s%15s%15s%15s%15s\n", "n", "t(n)", ordena.cota_inferior.nombre,
            ordena.cota_acotada.nombre, ordena.cota_superior.nombre);

    char *marca;
    for (i = 0; i < filas; i++) {
        marca = "";
        if (ts[i] < 500) {
            marca = "(*)";
        }
        printf("%10d%15.6f%15.6f%15.6f%15.6f%4s\n", 
                ns[i], ts[i], inf[i], aco[i], sup[i], marca);
    }
}

void tiempos(algoritmo ordena) {
    int i;
    int filas = 7;
    int primer_n = 15;
    int boost = 10;
    int ns[filas];
    double ts[filas];
    double inferior[filas];
    double acotada[filas];
    double superior[filas];
    matriz m;
    int *minimos = malloc(sizeof (int) * ns[filas - 1]);

    // Generamos las longitudes que vamos a usar para los arrays, la columa n
    generar_ns(ns, filas, primer_n);


    // calculamos los tiempos que nos lleva cada fila, la columna t(n)
    // - reusamos el mismo vector, de tamaño de la última fila
    m = crear_matriz(ns[filas - 1]);

    // Cargamos el proceso de trabajo para obtener mejores resultados
    while (boost-- != 0) {
        inicializar_matriz(m, ns[filas / 2]);
    }

    for (i = 0; i < filas; i++) {
        ts[i] = tiempo(ordena, ns[i], m, minimos);
    }
    
    liberar_matriz(m, ns[filas - 1]);
    free(minimos);

    // aplicamos las cotas a los tiempos
    for (i = 0; i < filas; i++) {
        inferior[i] = ordena.cota_inferior.f(ns[i], ts[i]);
        acotada[i] = ordena.cota_acotada.f(ns[i], ts[i]);
        superior[i] = ordena.cota_superior.f(ns[i], ts[i]);
    }

    // imprimimos la tabla
    imprimir_tabla(ns, ts, inferior, acotada, superior, filas, ordena);
}

double finferior(int n, double t) {
    return t / pow(n, 1.8);
}

double facotada(int n, double t) {
    return t / pow(n, 2);
}

double fsuperior(int n, double t) {
    return t / pow(n, 2.2);
}

void test(algoritmo algo, int n, matriz m, int *minimos) {
    algo.f(m, n, minimos);
    print_matrix(m, n);
    listar_vector(minimos, n);
}

void test1(algoritmo algo) {
    int n = 8;
    matriz m = crear_matriz(n);
    int *minimos = malloc(sizeof (int) * n);
    m[0][0] = INFINITO; m[0][1] = 5; m[0][2] = 2; m[0][3] = INFINITO;
    m[0][4] = INFINITO; m[0][5] = INFINITO; m[0][6] = INFINITO;
    m[0][7] = INFINITO; m[1][0] = INFINITO; m[1][1] = INFINITO;
    m[1][2] = INFINITO; m[1][3] = INFINITO; m[1][4] = INFINITO;
    m[1][5] = INFINITO; m[1][6] = 2; m[1][7] = INFINITO;
    m[2][0] = INFINITO; m[2][1] = 3; m[2][2] = INFINITO; m[2][3] = 4;
    m[2][4] = 2; m[2][5] = INFINITO; m[2][6] = 1; m[2][7] = INFINITO;
    m[3][0] = INFINITO; m[3][1] = INFINITO; m[3][2] = INFINITO;
    m[3][3] = INFINITO; m[3][4] = 3; m[3][5] = INFINITO;
    m[3][6] = INFINITO; m[3][7] = 1;  m[4][0] = INFINITO; m[4][1] = INFINITO;
    m[4][2] = INFINITO; m[4][3] = INFINITO; m[4][4] = INFINITO; m[4][5] = 2;
    m[4][6] = INFINITO; m[4][7] = 1; m[5][0] = INFINITO; m[5][1] = INFINITO;
    m[5][2] = INFINITO; m[5][3] = INFINITO; m[5][4] = INFINITO;
    m[5][5] = INFINITO; m[5][6] = INFINITO; m[5][7] = INFINITO;
    m[6][0] = INFINITO; m[6][1] = INFINITO; m[6][2] = INFINITO; 
    m[6][3] = INFINITO; m[6][4] = 1; m[6][5] = 4; m[6][6] = INFINITO;
    m[6][7] = INFINITO; m[7][0] = INFINITO; m[7][1] = INFINITO;
    m[7][2] = INFINITO; m[7][3] = INFINITO; m[7][4] = INFINITO; m[7][5] = 2;
    m[7][6] = INFINITO; m[7][7] = INFINITO;
    test(algo, n, m, minimos);
    liberar_matriz(m, n);
    free(minimos);
}

void tests(algoritmo algo) {
    test1(algo);
}

int main() {
    algoritmo algo;
    cota inferior;
    cota acotada;
    cota superior;

    algo.nombre = "Dijkstra";
    algo.f = dijkstra_normal;

    inferior.nombre = "t(n)/n^1.8";
    inferior.f = finferior;

    acotada.nombre = "t(n)/n^2";
    acotada.f = facotada;

    superior.nombre = "t(n)/n^2.2";
    superior.f = fsuperior;

    // unimos cotas con algoritmo
    algo.cota_inferior = inferior;
    algo.cota_acotada = acotada;
    algo.cota_superior = superior;

    tests(algo);

    tiempos(algo);
}