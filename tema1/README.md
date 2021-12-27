# Tema 1: Análisis de algoritmos

> **Objetivo**: predecir el comportamiento del algoritmo.

Aspectos cuantitativos:

- tiempo de ejecución
- cantidad de memoria

Se dispone de una medida de la eficiencia teórica y no exacta (utilizada para aproximar, clasificar y comparar algoritmos).

Acotar T(n), siendo n el tamaño del problema (a veces, la entrada). Cuando n → ∞ se considera comportamiento asintótico.
T(n) = O(f(n)) → f(n) es una cota superior, que *crece más deprisa* que T(n).

## Notación asintótica

> Establece un orden relativo entre las funciones, cpomparando la tasa de crecmiento.

### Cota superior: O

<!--
```latex
T(n), f(n): \mathbb{Z}^+ \rightarrow \mathbb{R}^+
\\
T(n) = O(f(n)) \rightarrow \exists c > 0, n_0 > 0 \quad|\quad T(n) \le cf(n) \quad\forall n \ge n_0
```
-->
![Big O Definition](images/bigO.svg)
