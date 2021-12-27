# insertar

> Página 71

```pseudo
procedimiento insertar (T[1..n])
    para i ← 2 hasta n hacer
        x ← T[i]; j ← i - 1
        mientras j > 0 y x < T[j] hacer
            T[j + 1] ← T[j]
            j ← j - 1
        T[j + 1] ← x
```
