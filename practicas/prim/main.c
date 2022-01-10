#include <stdio.h>
#include <math.h>
#include "grafos.h"

typedef struct cota {
    char* nombre;
    double (*f)(int, double);
} cota;

typedef struct algoritmo {
    char* nombre;
    void (*f)(matriz m, int n, cola* aristas);
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

double tiempo(algoritmo ordena, int n, matriz m) {
    int i, k = 1000;
    double ta, tb, t1, t2, t;
    cola c;

    // medición normal
    inicializar_matriz(m, n);
    ta = microsegundos();
    prim(m, n, &c);
    tb = microsegundos();
    t = tb - ta;

    // medición si el tiempo es muy rápido, media de 1000 veces
    if (t < 500) {
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            inicializar_matriz(m, n);
            prim(m, n, &c);
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
    printf("[+] Árbol recubrimiento mínimo: %s.\n", ordena.nombre);
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
        ts[i] = tiempo(ordena, ns[i], m);
    }
    
    liberar_matriz(m, ns[filas - 1]);

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

void test(int n, matriz m) {
    cola c;
    crear_cola(&c);
    prim(m, n, &c);
    print_matrix(m, n);
    mostrar_cola(c);
}

void test1() {
    int n = 5;
    matriz m = crear_matriz(5);
    m[0][0] = 0; m[0][1] = 1; m[0][2] = 8; m[0][3] = 4; m[0][4] = 7;
    m[1][0] = 1; m[1][1] = 0; m[1][2] = 2; m[1][3] = 6; m[1][4] = 5;
    m[2][0] = 8; m[2][1] = 2; m[2][2] = 0; m[2][3] = 9; m[2][4] = 5;
    m[3][0] = 4; m[3][1] = 6; m[3][2] = 9; m[3][3] = 0; m[3][4] = 3;
    m[4][0] = 7; m[4][1] = 5; m[4][2] = 5; m[4][3] = 3; m[4][4] = 0;
    test(n, m);
    liberar_matriz(m, n);
}

void test2() {
    int n = 4;
    matriz m = crear_matriz(4);
    m[0][0] = 0; m[0][1] = 1; m[0][2] = 4; m[0][3] = 7;
    m[1][0] = 1; m[1][1] = 0; m[1][2] = 2; m[1][3] = 8;
    m[2][0] = 4; m[2][1] = 2; m[2][2] = 0; m[2][3] = 3;
    m[3][0] = 7; m[3][1] = 8; m[3][2] = 3; m[3][3] = 0;
    test(n, m);
    liberar_matriz(m, n);
}

void test3() {
    int n = 7;
    matriz m = crear_matriz(7);
    m[0][0] = 0; m[0][1] = 7; m[0][2] = INFINITO;
    m[0][3] = 5; m[0][4] = INFINITO; m[0][5] = INFINITO; m[0][6] = INFINITO;
    m[1][0] = 7; m[1][1] = 0; m[1][2] = 8;
    m[1][3] = 9; m[1][4] = 7; m[1][5] = INFINITO; m[1][6] = INFINITO;
    m[2][0] = INFINITO; m[2][1] = 8; m[2][2] = 0;
    m[2][3] = INFINITO; m[2][4] = 5; m[2][5] = INFINITO; m[2][6] = INFINITO;
    m[3][0] = 5; m[3][1] = 9; m[3][2] = INFINITO;
    m[3][3] = 0; m[3][4] = 15; m[3][5] = 6; m[3][6] = INFINITO;
    m[4][0] = INFINITO; m[4][1] = 7; m[4][2] = 5;
    m[4][3] = 15; m[4][4] = 0; m[4][5] = 8; m[4][6] = 9;
    m[5][0] = INFINITO; m[5][1] = INFINITO; m[5][2] = INFINITO;
    m[5][3] = 6; m[5][4] = 8; m[5][5] = 0; m[5][6] = 11;
    m[6][0] = INFINITO; m[6][1] = INFINITO; m[6][2] = INFINITO;
    m[6][3] = INFINITO; m[6][4] = 9; m[6][5] = 11; m[6][6] = 0;
    test(n, m);
    liberar_matriz(m, n);
}

void tests() {
    test1();
    test2();
    test3();
}

int main() {
    algoritmo ordena;
    cota inferior;
    cota acotada;
    cota superior;

    ordena.nombre = "Prim";
    ordena.f = prim;

    inferior.nombre = "t(n)/n^1.8";
    inferior.f = finferior;

    acotada.nombre = "t(n)/n^2";
    acotada.f = facotada;

    superior.nombre = "t(n)/n^2.2";
    superior.f = fsuperior;

    // unimos cotas con algoritmo
    ordena.cota_inferior = inferior;
    ordena.cota_acotada = acotada;
    ordena.cota_superior = superior;

    tests();

    tiempos(ordena);
}