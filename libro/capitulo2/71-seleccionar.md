# seleccionar

> Página 71

```pseudo
procedimiento seleccionar (T[1..n])
    para i ← 1 hasta n - 1 hacer
        minj ← i; minx ← T[i]
        para j ← i + 1 hasta n hacer
            si T[j] < minx entonces
                minj ← j
                minx ← T[j]
        T[minj] ← T[i]
        T[i] ← minx
```
