# Tema 1: Análisis de algoritmos

> **Objetivo**: predecir el comportamiento del algoritmo.

Aspectos cuantitativos:

- tiempo de ejecución
- cantidad de memoria

Se dispone de una medida de la eficiencia teórica y no exacta (utilizada para aproximar, clasificar y comparar algoritmos).

Acotar T(n), siendo n el tamaño del problema (a veces, la entrada). Cuando n → ∞ se considera comportamiento asintótico.

T(n) = O(f(n)) → f(n) es una cota superior, que *crece más deprisa* que T(n).

## Notación asintótica

> Establece un orden relativo entre las funciones, comparando la tasa de crecmiento.

### Cota superior: O

<!--
```latex
T(n), f(n): \mathbb{Z}^+ \rightarrow \mathbb{R}^+
\\
T(n) = O(f(n)) \rightarrow \exists c > 0, n_0 > 0 \quad|\quad T(n) \le cf(n) \quad\forall n \ge n_0
```
-->
![Big O Definition](images/bigO.svg)

### Cota inferior: Ω

<!--
```latex
T(n), f(n): \mathbb{Z}^+ \rightarrow \mathbb{R}^+
\\
T(n) = \Omega(f(n)) \rightarrow \exists c > 0, n_0 > 0 \quad|\quad T(n) \ge cf(n) \quad\forall n \ge n_0
```
-->
![Big Ω Definition](images/bigOmega.svg)

### Cota exacta: Θ

<!--
```latex
T(n), f(n): \mathbb{Z}^+ \rightarrow \mathbb{R}^+
\\
T(n) = \Theta(f(n)) \rightarrow \exists c_1, c_2, n_0 \quad|\quad c_1f(n) \le T(n) \le c_2f(n) \quad\forall n \ge n_0
```
-->
![Big Ω Definition](images/bigTheta.svg)

> Se omite por simplicidad que las tres constantes tienen que ser estrictamente superiores a 0.

### Reglas prácticas

#### Cálculo de f(n)

Si T(n) es un polinomio de grado k, se tiene una cota exacta Θ(n^k).

<!-- 
```latex
T(n) = n^k + n^{k-1} + n^{k-2} + \dotso +  n + c\\
T(n) = \Theta (n^k)
```
-->

![Theta of poly degree K](images/polyK.svg)

Otra utilidad, la siguiente:

<!--
```latex
\forall c > 0, a>1 \text{ y } f(n) \text{ monotona creciente}\\
(f(n))^c = \omicron(a^{f(n)})
```
-->

![Little o power of function](images/poweroffn.svg)

#### Operaciones sobre notación asintótica

La suma equivale al máximo de los sumandos, el producto se opera como producto normal.
<!--
```latex
T_1(n) + T_2(n) = O(f(n) + g(n)) = O(max(f(n), g(n)))\\
T_1(n) * T_2(n) = O(f(n) * g(n)) 
```
-->
![Big O operations](images/operations.svg)

### Gráficos

Comparación de las posibles cotas.

![Comparison between bounds](images/comparison.png)

Cotas comunes:
<!--
```latex
O(1) \rightarrow \text{ constante}\\
O(\log{}n) \rightarrow \text{ logarítmica}\\
O(\log{}\log{}n) \rightarrow \text{ log-logarítmica}\\
O(n) \rightarrow \text{ lineal}\\
O(n\log{}n) \rightarrow \text{ linear logarítmica}\\
O(n^2) \rightarrow \text{ cuadrática}\\
O(n^3) \rightarrow \text{ cúbica}\\
O(2^n) \rightarrow \text{ exponencial}\\
O(n!) \rightarrow \text{ factorial}\\
```
-->

![Common bounds](images/commonbounds.svg)

Gráfico de las cotas comunes:

![Common bounds chart](images/commonboundschart.png)

## Resolución de recurrencias divide y vencerás

Para resolver recurrencias de divide y vencerás podemos ayudarnos de la siguiente regla.

<!--
```latex
\begin{equation*}
T(n) = ℓT(n/b)+cn^k
\\
T(n) \in \left\{
        \begin{array}{ll}
            \Theta(n^k) & \quad ℓ < b^k \\
            \Theta(n^k\log_b{n}) & \quad  ℓ = b^k \\
            \Theta(n^{log_b{ℓ}}) & \quad  ℓ > b^k \\
        \end{array}
    \right.
\end{equation*}
```
-->
![Divide and conquer: Recurrence solution](images/divideconquerSolution.svg)
