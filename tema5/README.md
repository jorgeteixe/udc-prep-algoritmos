# Tema 5: Diseño de algoritmos por inducción

## Divide y vencerás

### Características

- Descomponer el caso a resolver en subcasos del mismo problema, resolverlos independientemente de manera recursiva, y combinar las soluciones de los subcasos para componer una solución final.
- Ejemplos:
  - Suma de la subsecuencia máxima.
  - Mergesort
  - Quicksort
  - Búsqueda binaria
- Esquema para la técnica:
  - un problema (ej: ordenar)
  - un algoritmo ad-hoc: eficiente para casos pequeños (ej: inserción)

### Pseudocódigo

```pseudo
función Divide y Vencerás (x) : Solución
    si x es suficientemente pequeño entonces
        devolver ad-hoc (x)
    sino
        descomponer x en casos más pequeños x1, x2..., xa
        para i := hasta a hacer
            yi := Divide y Vencerás (xi)
        fin para
        combinar yi para obtener una solución x de y
        devolver y
fin función
```

Características de a (nº subcasos):

- pequeño: 2 en quicksort, mergesort, ...
- independiente de la entrada
- caso particular: a = 1 algoritmo de reducción
  - ej. búsqueda binaria

Problemas:

- descomposición y combinación ¿posibles? ¿eficientes?
- subcasos del mismo tamaño: n / b
  - donde b es una constante, importante balancear el tamaño de los subcasos
- umbral para el algoritmo ad-hoc

### Análisis

Reglas para el cálculo de la complejidad: usar relaciones de recurrencia.

Se suele poder usar el teorema de resolución de recurrencias Divide y Vencerás (que no es lo mismo), aunque no siempre se puede usar.

## Programación dinámica

Puede ser, usando un algoritmo Divide y vencerás, que tengamos un número de subcasos idénticos muy alto, lo cual es ineficiente.

La programación dinámica resuelve cada subcaso una sóla vez, guardando las soluciones en una tabla de soluciones, que se va completando hasta alcanzar la solución buscada.

### Coeficientes binomiales

<!--
```latex
{n\choose k} = \left\{
    \begin{array}{ll}
        1 & \quad \text{si }k = 0 \text{ o } k = n \\
        {n-1\choose k-1}+{n-1\choose k} & \quad \text{si }0 < k < n \\
        0 & \quad \text{en caso contrario}
    \end{array}
\right.
```
-->

![Binomial Coefficient](images/binomialcoefficient.svg)

```pseudo
función C (n, k)
    si k = 0 o k = n entonces devolver 1
    sino devolver C(n - 1, k - 1) + C(n - 1, k)
```

Con este pseudocódigo calculamos una y otra vez los mismos valores. Si en cambio utilizamos una tabla de resultados intermedio (el triángulo de Pascal), obtenemos un algoritmo más enficiente.

Pseudocódigo usando tabla:

```pseudo
función binomial (n, k)
    para i := 0 hacer
        para j := hasta min (i, k) hacer
            si j = 0 o j = i hacer
                C[i, j] := 1
            sino
                C[i, j] := C[i - 1, j - 1] + C[i - 1, j]
    devolver C[n, k]
```

### Devolver el cambio

El algoritmo voraz es eficiente pero no funciona siempre, dependiendo del sistema monetario que se use, funcionará o no.

Se usa una tabla C[1..m, 0..n], siendo m el número de valores diferentes de moneda, y n el número de unidades a pagar, donde C[i, j] es el número mínimo para pagar j utilizando monedas de valor <= i. El resultado final de haya en la última posición de la tabla C[m, n].

```pseudo
función monedas (n) : número de monedas
    const v[1..m] := [1, 4, 6]  { denominación del 'sistema monetario' }
    para i := 1 hasta m hacer
        c[i, 0] := 0
    para i := 1 hasta m hacer
        para j := 1 hasta n hacer
            si i = 1 y j < v[i] entonces
                c[1, j] := ∞
            sino si i = 1 entonces
                c[1, j] := 1 + c[1, j - v[1]]
            sino si j < v[i] entonces
                c[i, j] := c[i, j] := c[i - 1, j]
            sino
                c[i, j] := min (c[i - 1, j], 1 + c[i, j - v[i]])
    devolver c[m, n]
fin función
```

La complejidad de crear esta tabla es Θ(mn), y conseguir la traza Θ(m + c[m, n]).

### El problema de la mochila

Tabla v[1..n, 0..W], siendo n los objetos y W el peso máximo. Dónde v[i, j] es el valor máximo para la capicidad *j* considerando los objetos anteriores a *i*, *i* incluido.

> Observación: a diferencia del algoritmo anterior, cada elemento solo se puede incluir una vez.

```pseudo
función mochila (v[1..n], w[1..n], W)
    para i := 0 hasta W hacer
        V[0, w] := 0
    para i := 1 hasta n hacer
        para j := 0 hasta W hacer
            si w[i] <= w hacer
                V[i, w] = max (V[i - 1, w], v[i] + V[i - 1, w - w[i]])
            sino
                V[i, w] = V[i - 1, w]
    return V[n, W]
fin función
```

La complejidad del algoritmo es Θ(nW), y para hacer la traza necesitamos Θ(n + W).
