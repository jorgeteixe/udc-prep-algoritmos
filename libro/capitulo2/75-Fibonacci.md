# Fibonacci

> Página 75

```pseudo
función Fibonacci (n)
{ Calcula el n-ésimo término de la sucesión de Fibonacci }
    i ← 1; j ← 0
    para k ← 1 hasta n hacer
        j ← i + j
        i ← j - i
    devolver j
```
