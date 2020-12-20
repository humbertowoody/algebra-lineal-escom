# Programa 5

Programa que a partir de una matriz inicial calcula una base para su espacio imagen y una base para su espacio nulo.

## Instalación

El programa está escrito en C++11, por lo que se requiere un compiolador compatible con el estándar C++11 o posterior.

Se anexa un script de ejecución y compilación para simplificar dichas tareas ya que descompuse mi código en varios
archivo fuente para poder tener flexibilidad de implementación, además de que en este programa se emplean ya librerías que se desarrollaron
para programas anteriores.

Si se quiere realizar la compilación manual, el comando sería:

```bash
g++ -std=c++11 main.cpp ./Librerias/*.cpp -o Programa5.out
```

Con lo cual tendremos nuestro binario `Programa5.out` el cuál podemos ejecutar usando:

```bash
./Programa5.out
```

### Usar el script `compilar-y-ejecutar.sh`

Si se desea, se incluye el script `compilar-y-ejecutar.sh` con el cual se puede realizar la compilación y ejecución del código de forma directa.

## Ejecución

La ejecución del programa es muy simple e intuitiva, pero podría mejorar en su interacción con el usuario para volverlo más simple, por ahora la salida sería:

```txt
Generador de bases del espacio nulo e imagen a partir de una matriz inicial
Escuela Superior de Cómputo - Instituto Politécnico Nacional
Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal

Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
Programa: 5

¿Cuántas filas tendrá la matriz?
[2 - 20]> 4
¿Cuántas columnas tendrá la matriz?
[2 - 20]> 4

A continuación se leerá una matriz de 4x4.

[Fila 1] 1 4 3 2
[Fila 2] -1 -4 -3 -2
[Fila 3] 2 8 6 4
[Fila 4] -2 -8 -6 -4

La matriz leída fue:
[  1  4  3  2 ]
[ -1 -4 -3 -2 ]
[  2  8  6  4 ]
[ -2 -8 -6 -4 ]

La base del espacio nulo es:
Nu(A) = { ( -2, -0, -0, 1 ), ( -3, -0, 1, -0 ), ( -4, 1, -0, -0 ) }

La base del espacio imagen es:
Im(A) = { ( 1, -1, 2, -2 ) }
```

## Conclusión

En este programa pude crear una nueva librería `AlgebraLineal.hpp` con la cual implemento funcionalidades que requieren de `Matriz.hpp` y `GaussJordan.hpp` con lo que puedo simplificar cada vez más el desarrollo de distintos programas que utilicen estos conceptos.

Una de las partes más importantes del desarrollo de este programa fue la parte de permutaciones para encontrar una base en el espacio imagen. Esto debido a que, para hacer la prueba, tenía que encontrar una permutación válida de `n` vectores teniendo un conjunto de `k` vectores iniciales en dónde por válida nos referimos a que los vectores son linealmente independientes entre sí. El algoritmo final emplea una búsqueda en profundidad en su forma recursiva.

## Alumno

Humberto Alejandro Ortega Alcocer
2016630495
Correo: [hortegaa1500@alumno.ipn.mx](mailto:hortegaa1500@alumno.ipn.mx)

Semestre: Septiembre 2020 - Febrero 2021

20 de Diciembre del 2020.
