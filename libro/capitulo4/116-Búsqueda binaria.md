# Búsqueda binaria

> Página 116

```pseudo
función Búsqueda binaria (T[1..n], x)
{ Este algoritmo supone que x se encuentra en T }
    i ← 1; j ← n
    mientras i < j hacer
    { T[i] ≤ x ≤ T[j] }
        k ← (i + j) ÷ 2
        caso_de x < T[k]: j ← k - 1
                x = T[k]: i, j ← k    { devolver k }
                x > T[k]: i ← k + 1
    devolver i
```
