#include <stdio.h>
#include <math.h>
#include "ordena.h"

typedef struct cota {
    char* nombre;
    double (*f)(int, double);
} cota;

typedef struct algoritmo_ordenacion {
    char* nombre;
    void (*f)(int[], int);
    cota cota_inferior;
    cota cota_acotada;
    cota cota_superior;
} algoritmo_ordenacion;

typedef struct algoritmo_rellena {
    char* nombre;
    void (*f)(int[], int);
} algoritmo_rellena;

int test(algoritmo_ordenacion ordena) {
    int n = 100;
    int fallo = 0;
    int *v = malloc(sizeof (int) * n);
    
    /* TEST YA ORDENADO */
    rellena_ascendente(v, n);
    ordena.f(v, n);
    fallo += !ordenado(v, n);
    
    /* TEST DESCENDENTE */
    rellena_descendente(v, n);
    ordena.f(v, n);
    fallo += !ordenado(v, n);
    
    /* TEST ALEATORIO */
    rellena_aleatorio(v, n);
    ordena.f(v, n);
    fallo += !ordenado(v, n);
    
    /* TEST ALEATORIO n - 1 */
    rellena_aleatorio(v, n - 1);
    ordena.f(v, n - 1);
    fallo += !ordenado(v, n - 1);

    free(v);
    return fallo;
}

void generar_ns(int ns[], int filas, int primer_n) {
    int i, n = primer_n;
    for (i = 0; i < filas; ++i) {
        ns[i] = n;
        n = n * 2;
    }
}

double tiempo(algoritmo_ordenacion ordena, algoritmo_rellena rellena,
            int n, int *v) {
    int i, k = 1000;
    double ta, tb, t1, t2, t;
    // medición normal
    rellena.f(v, n);
    ta = microsegundos();
    ordena.f(v, n);
    tb = microsegundos();
    t = tb - ta;

    // medición si el tiempo es muy rápido, media de 1000 veces
    if (t < 500) {
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            rellena.f(v, n);
            ordena.f(v, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; ++i) {
            rellena.f(v, n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        return (t1 - t2) / k;
    }
    return t;
}

void imprimir_tabla(int ns[], double ts[], double inf[], double aco[],
                    double sup[], int filas,
                    algoritmo_ordenacion ordena, algoritmo_rellena rellena) {
    int i;
    printf("[+] Ordenacion: %s, rellenado con: %s\n",
            ordena.nombre, rellena.nombre);
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

void tiempos(algoritmo_ordenacion ordena, algoritmo_rellena rellena) {
    int i;
    int filas = 7;
    int primer_n = 500;
    int boost = INT8_MAX;
    int ns[filas];
    double ts[filas];
    double inferior[filas];
    double acotada[filas];
    double superior[filas];
    int *v;

    // Generamos las longitudes que vamos a usar para los arrays, la columa n
    generar_ns(ns, filas, primer_n);

    // Cargamos el proceso de trabajo para obtener mejores resultados
    while (boost-- != 0) {
        boost++;
        boost--;
    }

    // calculamos los tiempos que nos lleva cada fila, la columna t(n)
    // - reusamos el mismo vector, de tamaño de la última fila
    v = malloc(sizeof (int) * ns[filas - 1]);
    for (i = 0; i < filas; i++) {
        ts[i] = tiempo(ordena, rellena, ns[i], v);
    }
    free(v);

    // aplicamos las cotas a los tiempos
    for (i = 0; i < filas; i++) {
        inferior[i] = ordena.cota_inferior.f(ns[i], ts[i]);
        acotada[i] = ordena.cota_acotada.f(ns[i], ts[i]);
        superior[i] = ordena.cota_superior.f(ns[i], ts[i]);
    }

    // imprimimos la tabla
    imprimir_tabla(ns, ts, inferior, acotada,
                   superior, filas, ordena, rellena);
}

double finferior(int n, double t) {
    return t / pow(n, 1.8);
}

double facotada(int n, double t) {
    return t / pow(n, 2.0);
}

double fsuperior(int n, double t) {
    return t / pow(n, 2.2);
}

int main() {
    algoritmo_ordenacion ordena;
    algoritmo_rellena rellena;
    cota inferior;
    cota acotada;
    cota superior;

    ordena.nombre = "inserción";
    ordena.f = ordena_insercion;

    rellena.nombre = "aleatorio";
    rellena.f = rellena_aleatorio;

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


    printf("¿Error en %s? %s\n", ordena.nombre, test(ordena) ? "Si." : "No.");

    tiempos(ordena, rellena);
}
