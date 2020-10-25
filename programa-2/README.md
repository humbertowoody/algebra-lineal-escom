# Programa 2

Programa que realiza la verificación de un sistema de ecuaciones lineales de MxN utilizando el método de Gauss-Jordan.

## Instalación

El programa está escrito en C++11, por lo que se requiere un compiolador compatible con el estándar C++11 o posterior.

Se anexa un script de ejecución y compilación para simplificar dichas tareas ya que descompuse mi código en varios
archivo fuente para poder tener flexibilidad de implementación, además de que, en un futuro, aprovechar los beneficios
de compilación incremental para re-utilizar la librería `Matriz.hpp` en otros proyectos de la materia.

Si se quiere realizar la compilación manual, el comando sería:

```bash
g++ -std=c++11 *.cpp -o Programa2.out
```

Con lo cual tendremos nuestro binario `Programa2.out` el cuál podemos ejecutar usando:

```bash
./Programa2.out
```

### Usar el script `compilar-y-ejecutar.sh`

Si se desea, se incluye el script `compilar-y-ejecutar.sh` con el cual se pueden realizar dos tareas principales:

1. Compilar y ejecutar el programa en modo interactivo, es decir, sin entradas de otros lados.
2. Compilar y ejecutar el programa en modo no interactivo, es decir, la entrada del programa serán todos los archivos `*.txt` dentro del directorio `entradas` y cada salida será almacenada en un archivo con el formato: `resultados-ejecucion-dia_mes_año-hora-minuto.out` dentro de la carpeta `ejecuciones`.

La razón del inciso 2 es muy simple, si queremos probar el programa frente a una serie de entradas, sería muy complicado ingresarlas una por una, además de tardado y repetitivo. **Es una solución temporal, en la siguiente versión el programa mismo podrá leer los archivos, lo prometo**.

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
Programa: 2

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
Se ha leído la matriz de 4 columnas y 3 filas siguiente:
[          1          2          3          4 ]
[          1          2          3          4 ]
[          1          2          3          4 ]

Paso 2: Diagonalizar la parte inferior de la matriz extendida.
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
La matriz extendida diagonalizada es:
[          1          2          3          4 ]
[          0          0          0          0 ]
[          0          0          0          0 ]

Paso 3: Verificar el tipo de solución.
Matriz coeficientes diagonalizada:
[          1          2          3 ]
[          0          0          0 ]
[          0          0          0 ]

El rango de la matriz extendida diagonalizada (R(A*)) es: 1
El rango de la matriz de coeficientes diagonalizada (R(A)) es: 1
Conclusión: El sistema tiene una infinidad de soluciones (los rangos son iguales entre sí, pero distintos al número de incógnitas: R(A)=1 igual a R(A*)=1, pero distintos del número de incógnitas (3)).

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
Programa: 2

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
Se ha leído la matriz de 4 columnas y 3 filas siguiente:
[          1          2          3          4 ]
[          5          6          7          8 ]
[          9         10         11         12 ]

Paso 2: Diagonalizar la parte inferior de la matriz extendida.
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
La matriz extendida diagonalizada es:
[          1          2          3          4 ]
[          0          1          2          3 ]
[          0          0          0          0 ]

Paso 3: Verificar el tipo de solución.
Matriz coeficientes diagonalizada:
[          1          2          3 ]
[          0          1          2 ]
[          0          0          0 ]

El rango de la matriz extendida diagonalizada (R(A*)) es: 2
El rango de la matriz de coeficientes diagonalizada (R(A)) es: 2
Conclusión: El sistema tiene una infinidad de soluciones (los rangos son iguales entre sí, pero distintos al número de incógnitas: R(A)=2 igual a R(A*)=2, pero distintos del número de incógnitas (3)).

Fin de ejecución de programa.

```

## Conclusión

El desarrollo del programa me ha tomado más de 2 semanas, esto porque desde preparatoria he querido tener una librería de manipulación de matrices funcional y de la cual pudiera estar orgulloso. Uno de los problemas más grandes al trabajar con el lenguaje C/C++ es que los tipos de datos se reducen a categorías muy simples como `int`, `float`, `double` y combinaciones con `long` (y muchos `long`) por lo que me era primordial cumplir una serie de requisitos para que la librería realmente pudiera servirme en varios casos:

1. Debe ser capaz de realizar las operaciones con "tipos de datos variables", por ello utilizo los `template` de C++, los cuales nos permiten generar clases y definiciones de datos que puedan mutar a comodidad de la implementación.
2. Debe exponer un sistema de control de errores mediante excepciones, esto porque utilizar el clásico: "regreso 0 si todo salió bien, -1 si algo salió mal", con el que funcionan muchas cosas en C, realmente no nos permite poder reaccionar ante distintos casos de errores que sucedan durante la ejecución, más aún pensando en ejecuciones interactivas, lo mejor siempre será poder controlar el error de la forma más específica que se requiera.
3. Debe abstrer correctamente la "Matriz" del "Solucionador por Gauss-Jordan", esto porque la "Matriz" es el objetivo de reutilización, ya que puede ser empleada en problemas más allá de la solución de sistemas de ecuaciones lineales por Gauss-Jordan e inclusive para cosas que no se refieran a sistemas de ecuaciones lineales en lo absoluto.
4. Todas las operaciones matriciales deben ser inmutables, refiriéndose a que no realizarán cambios a la Matriz directamente, sino que realizarán las operaciones sobre una copia y regresarán la Matriz con el resultado de dicha operación. De esta forma, garantizamos concistencia a través de múltiples casos de uso.

Si se revisa el archivo `Matriz.hpp` se puede ver cómo tengo planeado añadir funciones para volver esta la librería que (en mi imaginación) podría ayudarme con muchos problemas de matrices a lo largo del semestre. ¡Quién sabe! Inclusive algún día la podría publicar.

## Alumno

Humberto Alejandro Ortega Alcocer
2016630495
Correo: [hortegaa1500@alumno.ipn.mx](mailto:hortegaa1500@alumno.ipn.mx)

Semestre: Septiembre 2020 - Febrero 2021

23 de Octubre de 2020.
