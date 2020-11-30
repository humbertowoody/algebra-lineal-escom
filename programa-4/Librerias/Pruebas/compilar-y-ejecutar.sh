#!/bin/bash

# Prueba de Matriz.
g++ PruebaMatriz.cpp ../*.cpp -o PruebaMatriz.out -std=c++17 && echo "¡PruebaMatriz compilado exitosamente! Ejecutando binario..." && ./PruebaMatriz.out;

# Prueba de GaussJordan.
g++ PruebaGaussJordan.cpp ../*.cpp -o PruebaGaussJordan.out -std=c++17 && echo "¡PruebaGaussJordan compilado exitosamente! Ejecutando binario..." && ./PruebaGaussJordan.out;

# Humberto Alejandro Ortega Alcocer.
# 2020.