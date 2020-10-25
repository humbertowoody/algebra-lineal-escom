#!/bin/bash

#
# Script que realiza la compilación y ejecución del programa 2 de la materia de Álgebra Lineal.
#
# Hay dos caminos de ejecución y compilación, si MODO=1 es modo interactivo (compila y ejecuta),
# si MODO=2, compila y ejecuta el programa vs todos los archivos *.txt del directorio y
# guarda las salidas en un archivo con la fecha del día de hoy.
#

# Aquí seleccionamos el tipo de ejecución:
MODO=2

if [[ "$MODO" = 1 ]]
then
# Esta línea realiza la compilación y ejecuta el programa de forma interactiva.
g++ *.cpp -o Programa2.out -std=c++17 && echo "¡Compilado Exitosamente! Ejecutando binario de forma interactiva..." && ./Programa2.out;
else
# Esta sección realiza la compilación y ejecuta el programa con las entradas en los archivos *.txt
g++ *.cpp -o Programa2.out -std=c++17 && echo "¡Compilado Exitosamente! Ejecutando binario con archivos de entrada *txt...";
fechaHoy=$(date +"%d_%m_%Y-%H:%M") # La fecha del día de hoy + la hora.
for i in ./entradas/*.txt
do
  # Primero añadimos división.
  echo "-------------------$i-------------------" >> "./ejecuciones/resultados-ejecucion-${fechaHoy}.txt";
  # Ejecutamos el programa en el archivo actual
  ./Programa2.out < "$i" >> "./ejecuciones/resultados-ejecucion-${fechaHoy}.txt";
done
fi

# Humberto Alejandro Ortega Alcocer.
# 2020.