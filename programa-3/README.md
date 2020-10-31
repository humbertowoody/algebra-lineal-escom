# Programa 3

Programa que realiza la resolución de un sistema de ecuaciones lineales mediante el método de Gauss-Jordan.

## Instalación

El programa está escrito en C++11, por lo que se requiere un compiolador compatible con el estándar C++11 o posterior.

Se anexa un script de ejecución y compilación para simplificar dichas tareas ya que descompuse mi código en varios
archivo fuente para poder tener flexibilidad de implementación, además de que, en un futuro, aprovechar los beneficios
de compilación incremental para re-utilizar la librería `Matriz.hpp` en otros proyectos de la materia.

Si se quiere realizar la compilación manual, el comando sería:

```bash
g++ -std=c++11 *.cpp -o Programa3.out
```

Con lo cual tendremos nuestro binario `Programa3.out` el cuál podemos ejecutar usando:

```bash
./Programa3.out
```

### Usar el script `compilar-y-ejecutar.sh`

Si se desea, se incluye el script `compilar-y-ejecutar.sh` con el cual se pueden realizar dos tareas principales:

1. Compilar y ejecutar el programa en modo interactivo, es decir, sin entradas de otros lados.
2. Compilar y ejecutar el programa en modo no interactivo, es decir, la entrada del programa serán todos los archivos `*.txt` dentro del directorio `/entradas` y cada salida será almacenada en un archivo con el formato: `resultados-ejecucion-dia_mes_año-hora-minuto.txt` dentro de la carpeta `/ejecuciones`.

La razón del inciso 2 es muy simple, si queremos probar el programa frente a una serie de entradas, sería muy complicado ingresarlas una por una, además de tardado y repetitivo.

El script `compilar-y-ejecutar.sh` contiene una variable llamada `MODO` la cual determina cuál de los dos flujos de ejecución mencionados más arriba será utilizado. La variable puede tener dos valores: `1` y `2`.

## Ejecución

Como tengo dos flujos de ejecución, incluyo ejemplos para cada uno.

### Modo interactivo

Una ejecución promedio del programa presenta la siguiente salida en la terminal, utilizando el script en `MODO=1` (interactivo):

```txt
$ ./compilar-y-ejecutar
¡Compilado Exitosamente! Ejecutando binario de forma interactiva...
Sistemas de Ecuaciones Lineales de MxN por Gauss-Jordan
Escuela Superior de Cómputo - Instituto Politécnico Nacional
Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal

Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
Programa: 3

Paso 1: Leer datos de entrada.
¿Cuántas variables tiene el sistema de ecuaciones?
[2 - 19]> 3
¿Cuántas ecuaciones tiene el sistema de ecuaciones?
[2 - 20]> 3
Se leerán los datos para la ecuación #1.
Introduce el valor para la variable x_{1}
> 1
Introduce el valor para la variable x_{2}
> 2
Introduce el valor para la variable x_{3}
> 3
Introduce el valor del término independiente b_{1}
> 4
Se leerán los datos para la ecuación #2.
Introduce el valor para la variable x_{1}
> 1
Introduce el valor para la variable x_{2}
> 2
Introduce el valor para la variable x_{3}
> 3
Introduce el valor del término independiente b_{2}
> 4
Se leerán los datos para la ecuación #3.
Introduce el valor para la variable x_{1}
> 1
Introduce el valor para la variable x_{2}
> 2
Introduce el valor para la variable x_{3}
> 3
Introduce el valor del término independiente b_{3}
> 4
El sistema de ecuaciones ingresado es:
 +1x_{1} +2x_{2} +3x_{3} = 4b_{1}
 +1x_{1} +2x_{2} +3x_{3} = 4b_{2}
 +1x_{1} +2x_{2} +3x_{3} = 4b_{3}
Se ha leído la matriz extendida (A*) de 4 columnas y 3 filas siguiente:
[          1          2          3          4 ]
[          1          2          3          4 ]
[          1          2          3          4 ]

Paso 2: Diagonalizar la matriz extendida.
Diagonalizando para el pivote en a_{1,1}:
[          1          2          3          4 ]
[          1          2          3          4 ]
[          1          2          3          4 ]

Diagonalizando para el pivote en a_{2,2}:
[          1          2          3          4 ]
[          0          0          0          0 ]
[          0          0          0          0 ]

Diagonalizando para el pivote en a_{3,3}:
[          1          2          3          4 ]
[          0          0          0          0 ]
[          0          0          0          0 ]

Diagonalización inferior final:
[          1          2          3          4 ]
[          0          0          0          0 ]
[          0          0          0          0 ]

Pivote inicial de diagonalización superior: 0
Diagonalización completa final:
[          1          2          3          4 ]
[          0          0          0          0 ]
[          0          0          0          0 ]


Paso 3: Verificar el tipo de solución.
Matriz extendida (A*) diagonalizada:
[          1          2          3          4 ]
[          0          0          0          0 ]
[          0          0          0          0 ]

Matriz coeficientes (A) diagonalizada:
[          1          2          3 ]
[          0          0          0 ]
[          0          0          0 ]

El rango de la matriz extendida diagonalizada (R(A*)) es: 1
El rango de la matriz de coeficientes diagonalizada (R(A)) es: 1
Conclusión: El sistema tiene una infinidad de soluciones (los rangos son iguales entre sí, pero distintos al número de incógnitas: R(A)=1 igual a R(A*)=1, pero distintos del número de incógnitas (3)).

Paso 4: Calcular solución (si la hay).
El sistema tiene una infinidad de soluciones.
El número de parámetros libres para nuestro sistema es: 2
~ x_{1} = -2x_{2} -3x_{3} + 4
~ x_{2} = Δ_{1}
~ x_{3} = Δ_{2}

Puede sustituir cualquier valor perteneciente a los números reales para cada Δ y obtendrá una solución válida.

Fin de ejecución de programa.

```

### Modo no interactivo

Una ejecución promedio del programa presenta la siguiente salida en la terminal, utilizando el script en `MODO=2` (no interactivo):

```txt
¡Compilado Exitosamente! Ejecutando binario con archivos de entrada *txt...
```

Contenido de `./entradas/input.txt` (único archivo para este ejemplo):

```txt
3
3
1
2
3
4
5
6
7
8
9
10
11
12

```

Resultados en `./ejecuciones/resultados-ejecucion-23_10_2020-20:45.txt`:

```txt
-------------------./entradas/input.txt-------------------
Sistemas de Ecuaciones Lineales de MxN por Gauss-Jordan
Escuela Superior de Cómputo - Instituto Politécnico Nacional
Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal

Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
Programa: 3

Paso 1: Leer datos de entrada.
¿Cuántas variables tiene el sistema de ecuaciones?
[2 - 19]> ¿Cuántas ecuaciones tiene el sistema de ecuaciones?
[2 - 20]> Se leerán los datos para la ecuación #1.
Introduce el valor para la variable x_{1}
> Introduce el valor para la variable x_{2}
> Introduce el valor para la variable x_{3}
> Introduce el valor del término independiente b_{1}
> Se leerán los datos para la ecuación #2.
Introduce el valor para la variable x_{1}
> Introduce el valor para la variable x_{2}
> Introduce el valor para la variable x_{3}
> Introduce el valor del término independiente b_{2}
> Se leerán los datos para la ecuación #3.
Introduce el valor para la variable x_{1}
> Introduce el valor para la variable x_{2}
> Introduce el valor para la variable x_{3}
> Introduce el valor del término independiente b_{3}
> El sistema de ecuaciones ingresado es:
 +1x_{1} +2x_{2} +3x_{3} = 4b_{1}
 +5x_{1} +6x_{2} +7x_{3} = 8b_{2}
 +9x_{1} +10x_{2} +11x_{3} = 12b_{3}
Se ha leído la matriz extendida (A*) de 4 columnas y 3 filas siguiente:
[          1          2          3          4 ]
[          5          6          7          8 ]
[          9         10         11         12 ]

Paso 2: Diagonalizar la matriz extendida.
Diagonalizando para el pivote en a_{1,1}:
[          1          2          3          4 ]
[          5          6          7          8 ]
[          9         10         11         12 ]

Diagonalizando para el pivote en a_{2,2}:
[          1          2          3          4 ]
[          0         -4         -8        -12 ]
[          0         -8        -16        -24 ]

Diagonalizando para el pivote en a_{3,3}:
[          1          2          3          4 ]
[          0          1          2          3 ]
[          0          0          0          0 ]

Diagonalización inferior final:
[          1          2          3          4 ]
[          0          1          2          3 ]
[          0          0          0          0 ]

Pivote inicial de diagonalización superior: 1
Diagonalizando para el pivote en A*_{22}:
[          1          2          3          4 ]
[          0          1          2          3 ]
[          0          0          0          0 ]

Diagonalización completa final:
[          1          0         -1         -2 ]
[          0          1          2          3 ]
[          0          0          0          0 ]


Paso 3: Verificar el tipo de solución.
Matriz extendida (A*) diagonalizada:
[          1          0         -1         -2 ]
[          0          1          2          3 ]
[          0          0          0          0 ]

Matriz coeficientes (A) diagonalizada:
[          1          0         -1 ]
[          0          1          2 ]
[          0          0          0 ]

El rango de la matriz extendida diagonalizada (R(A*)) es: 2
El rango de la matriz de coeficientes diagonalizada (R(A)) es: 2
Conclusión: El sistema tiene una infinidad de soluciones (los rangos son iguales entre sí, pero distintos al número de incógnitas: R(A)=2 igual a R(A*)=2, pero distintos del número de incógnitas (3)).

Paso 4: Calcular solución (si la hay).
El sistema tiene una infinidad de soluciones.
El número de parámetros libres para nuestro sistema es: 1
~ x_{1} = + 1x_{3} -2
~ x_{2} = -2x_{3} + 3
~ x_{3} = Δ_{1}

Puede sustituir cualquier valor perteneciente a los números reales para cada Δ y obtendrá una solución válida.

Fin de ejecución de programa.

```

## Conclusión

En esta versión del programa, se realiza por completo el proceso de resolución de un sistema de ecuaciones lineales
mediante Gauss-Jordan. Para ello, se tiene la clase `Matriz` que permite manipular matrices y ofrece algunas operaciones
elementales básicas. También se incluye la clase `GaussJordan` la cual contiene los métodos para ejecutar el proceso de
resolución Gauss-Jordan. Finalmente, en `main.cpp` se ejecuta el proceso por completo.

Se muestra el proceso de diagonlización con el fin de detectar errores de forma más simple al momento de desarrollar
pero también por si se desea visualizar el proceso.

Este programa ha sido un reto muy divertido e interesante de resolver, espero seguir desarrollando soluciones de este estilo
a lo largo del semestre.

## Alumno

Humberto Alejandro Ortega Alcocer
2016630495
Correo: [hortegaa1500@alumno.ipn.mx](mailto:hortegaa1500@alumno.ipn.mx)

Semestre: Septiembre 2020 - Febrero 2021

31 de Octubre de 2020.
