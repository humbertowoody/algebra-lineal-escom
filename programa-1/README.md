# Programa 1

Programa que resuelve un sistema de ecuaciones lineales de 2x2 (2 ecuaciones con 2 incógnitas) utilizando el método de diagonalización.

## Instalación

El programa está diseñado para Python 3.8, e incluye una carpeta para el uso de `venv`.

Lo único que se debe realizar es, desde una terminal ubicada en el directorio del programa:

```bash
$ source ./bin/activate
```

Con lo cual se activará nuestro entorno de desarrollo con las librerías y dependencias necesarias.


## Ejecución

Una ejecución promedio del programa presenta la siguiente salida en la terminal:

```txt
Sistemas de Ecuaciones Lineales de 2x2 por Gauss-Jordan
Escuela Superior de Cómputo - Instituto Politécnico Nacional
Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal

Alumno: Humberto Alejandro Ortega Alcocer
Programa: 1

Este programa no puede leer fracciones, si desea introducir números racionales, porfavor introdúzcalos usando representación decimal, gracias.

Leyendo datos para la primer ecuación.
Ingresa el valor para x1: 1
Ingresa el valor para y1: 1
Ingresa el valor para el término independiente 1: 10

Leyendo datos para la segunda ecuación.
Ingresa el valor para x2: -1
Ingresa el valor para y2: -1
Ingresa el valor para el término independiente 2: 20

Sistema de ecuaciones leído:
Ecuación 1: (1.0)x + (1.0)y = 10.0
Ecuación 2: (-1.0)x + (-1.0)y = 20.0

Matriz de Coeficientes Original (A):
(1.0,1.0)
(-1.0,-1.0)

Matriz Extendida Original (A*):
(1.0,1.0,10.0)
(-1.0,-1.0,20.0)

Matriz Diagonalizada:
(1.0,1.0,10.0)
(0.0,0.0,30.0)

Datos relevantes:
  ~ Rango matriz coeficientes R(A): 1
  ~ Rango matriz extendida R(A*): 2
  ~ Número de incógnitas: 2

Conclusión final:
  ~ El sistema no tiene solución (A_{22}=0.0; b_{2}=30.0; A_{22} es cero y b2 es distinto a 0).

Presione ENTER para mostrar las gráficas de las ecuaciones...
¡Mostrando gráficas de las ecuaciones en la ventana emergente!
¡Fin de ejecución!
```

Imágen muestra de la graficación para la salida anterior:

![Gráfica 1][grafica-1]

## Conclusión

Comencé el desarrollo del programa confundido sobre el método a emplear para la resolución del sistema y, por lo mismo, programé inicialmente la parte de la definición del tipo de solución utilizando el teorema de Rouché-Fröbenius. Por ello el programa muestra datos como los rangos de las matrices y el número de incógnitas.

Posteriormente pude ver los apuntes de la primer semana de clases y corregí empleando la metodología planteada, sin embargo decidí dejar esa información puesto que podría ser de utilidad para verificar el comportamiento del programa.

El proceso de diagonalización está codificado de forma dura porque tenemos la garantía de tamaño de nuestro sistema (2x2) por lo que resulta en código más simple de verificar y visualizar.

Las librerías `matplotlib` y `numpy` son empleadas únicamente con fines de graficación. En particular, `numpy` se utiliza únicamente para generar los rangos de graficado y `matplotlib` para, finalmente, mostrar las gráficas correspondientes a las ecuaciones presentes en nuestro sistema.

El programa asume que todas las entradas son de tipo `float`, esto porque Python asume el tipo de dato a `int` cuando se utiliza el método `input()` y, en caso de que lleguemos a realizar una división entre dos números enteros (`int`s), el tipo de dato del resultado será `int` por lo que perderemos precisión ya que los decimales son truncados.

La única razón por la que decidí usar Python es la librería `matplotlib`, la cual, en mi opinión, es la más simple y fácil de utilizar para realizar gráficas. 

## Alumno

Humberto Alejandro Ortega Alcocer
2016630495
Correo: [hortegaa1500@alumno.ipn.mx](mailto:hortegaa1500@alumno.ipn.mx)

Semestre: Septiembre 2020 - Febrero 2021.

19 de Octubre de 2020.

[grafica-1]: /assets/graph-1.png