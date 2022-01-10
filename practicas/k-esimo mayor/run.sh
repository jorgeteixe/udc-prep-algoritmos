#!/bin/bash

# Imprime las líneas que se pasan de 80 caracteres.
cat ./*.* |grep '.\{80\}'

# Compila el código en ./main
gcc -Wall *.c -lm -o main

# Ejecuta ./main
./main

# Elimina el ejecutable creado
rm main
