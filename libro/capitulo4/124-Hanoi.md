# Hanoi

> Página 124

```pseudo
procedimiento Hanoi(m, i, j)
{ Traslada los m anillos más pequeños de la barra i a la barra j }
    si m > 0 entonces
        Hanoi (m - 1, i, 6 - i - j)
        escribir i " → " j
        Hanoi (m - 1, 6 - i - j, j)
```
