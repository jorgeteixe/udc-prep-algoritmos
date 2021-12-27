# contar

> Página 128

```pseudo
procedimiento contar (C[1..m])
{ Este procedimiento supone que m ≥ 1 y que C[j] existe en {0, 1} para todo 1 ≤ j ≤ m }
    j ← m + 1
    repetir
        j ← j - 1
        C[j] ← 1 - C[j]
    hasta_que C[j] = 1 o j = 1
```
