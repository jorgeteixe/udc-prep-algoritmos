#include <stdio.h>
#include <math.h>
#include "algoritmo.h"

typedef struct cota {
    char* nombre;
    double (*f)(int, double);
} cota;

typedef struct algoritmo {
    char* nombre;
    int (*f)(int[], int, int);
    cota cota_inferior;
    cota cota_acotada;
    cota cota_superior;
} algoritmo;

void test(algoritmo algo) {
    int n = 10, r, i, k = 3;
    int *v = malloc(sizeof (int) * n);

    // EJ 3
    for (i = 0; i < 10; i++) {
        rellena_aleatorio(v, n);
        r = algo.f(v, n, k);
        listar_vector(v, n);
        ordena_insercion(v, n);
        printf("¿%d = %d? %s\n\n", r, v[n - k], r == v[n - k] ? "Si." : "No.");
    }

    // EJ 4
    rellena_ascendente(v, 500);
    for (i = 1; i <= 500; i += 50) {
        r = algo.f(v, 500, i);
        printf("¿%d = %d? %s\n", r, 500 - i, r == 500 - i ? "Si." : "No.");
    }

    free(v);
}

void generar_ns(int ns[], int filas, int primer_n) {
    int i, n = primer_n;
    for (i = 0; i < filas; ++i) {
        ns[i] = n;
        n = n * 2;
    }
}

double tiempo(algoritmo algo, int n, int *v) {
    int i, k = 1000;
    double ta, tb, t1, t2, t;
    // medición normal
    rellena_aleatorio(v, n);
    ta = microsegundos();
    // 5 a
    //algo.f(v, n, 5);
    // 5 b
    algo.f(v, n, n / 2);
    tb = microsegundos();
    t = tb - ta;

    // medición si el tiempo es muy rápido, media de 1000 veces
    if (t < 500) {
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            rellena_aleatorio(v, n);
            // 5 a
            //algo.f(v, n, 5);
            // 5 b
            algo.f(v, n, n / 2);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            rellena_aleatorio(v, n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        return (t1 - t2) / k;
    }
    return t;
}

void imprimir_tabla(int ns[], double ts[], double inf[], double aco[],
                    double sup[], int filas,
                    algoritmo algo) {
    int i;
    printf("[+] Algoritmo: %s\n", algo.nombre);
    printf("%10s%15s%15s%15s%15s\n", "n", "t(n)", algo.cota_inferior.nombre,
            algo.cota_acotada.nombre, algo.cota_superior.nombre);

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

void tiempos(algoritmo algo) {
    int i;
    int filas = 10;
    int primer_n = 500;
    int boost = 10;
    int ns[filas];
    double ts[filas];
    double inferior[filas];
    double acotada[filas];
    double superior[filas];
    int *v;

    // Generamos las longitudes que vamos a usar para los arrays, la columa n
    generar_ns(ns, filas, primer_n);


    // calculamos los tiempos que nos lleva cada fila, la columna t(n)
    // - reusamos el mismo vector, de tamaño de la última fila
    v = malloc(sizeof (int) * ns[filas - 1]);

    // Cargamos el proceso de trabajo para obtener mejores resultados
    while (boost-- != 0) {
        rellena_aleatorio(v, ns[filas / 2]);
        algo.f(v, ns[filas / 2], 5);
    }

    for (i = 0; i < filas; i++) {
        ts[i] = tiempo(algo, ns[i], v);
    }
    free(v);

    // aplicamos las cotas a los tiempos
    for (i = 0; i < filas; i++) {
        inferior[i] = algo.cota_inferior.f(ns[i], ts[i]);
        acotada[i] = algo.cota_acotada.f(ns[i], ts[i]);
        superior[i] = algo.cota_superior.f(ns[i], ts[i]);
    }

    // imprimimos la tabla
    imprimir_tabla(ns, ts, inferior, acotada, superior, filas, algo);
}

double finferior(int n, double t) {
    return t / log2(n);
}

double facotada(int n, double t) {
    return t / (n * log2(n));
}

double fsuperior(int n, double t) {
    return t / pow(n, 2);
}

int main() {
    algoritmo algo;
    cota inferior;
    cota acotada;
    cota superior;

    algo.nombre = "k-ésimo mayor";
    algo.f = kesimo_mayor;

    inferior.nombre = "t(n)/logn";
    inferior.f = finferior;

    acotada.nombre = "t(n)/nlogn";
    acotada.f = facotada;

    superior.nombre = "t(n)/n^2";
    superior.f = fsuperior;

    // unimos cotas con algoritmo
    algo.cota_inferior = inferior;
    algo.cota_acotada = acotada;
    algo.cota_superior = superior;

    test(algo);

    tiempos(algo);
}