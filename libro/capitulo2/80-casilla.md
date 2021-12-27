# casilla

> Página 80

```pseudo
procedimiento casilla (T[1..n])
{ ordena enteros entre 1 y 10.000 }
    matriz U[1..10.000]
    para k ← 1 hasta 10.000 hacer
        U[k] ← 0
    para i ← 1 hasta n hacer
        k ← T[i]
        U[k] ← U[k] + 1
    i ← 0
    para k ← 1 hasta 10.000 hacer
        mientras U[k] ≠ 0 hacer
            i ← i + 1
            T[i] ← k
            U[k] ← U[k] - 1
```
