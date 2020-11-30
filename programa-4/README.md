# Programa 4

Programa que verifica:

- Si un conjunto de vectores son linealmente dependientes (L.D.) o linealmente independientes (L.I.)
- Si un vector U representa una combinación lineal de este conjunto de vectores.

## Instalación

El programa está escrito en C++11, por lo que se requiere un compiolador compatible con el estándar C++11 o posterior.

Se anexa un script de ejecución y compilación para simplificar dichas tareas ya que descompuse mi código en varios
archivo fuente para poder tener flexibilidad de implementación, además de que en este programa se emplean ya librerías que se desarrollaron
para programas anteriores.

Si se quiere realizar la compilación manual, el comando sería:

```bash
g++ -std=c++11 main.cpp ./Librerias/*.cpp -o Programa4.out
```

Con lo cual tendremos nuestro binario `Programa4.out` el cuál podemos ejecutar usando:

```bash
./Programa4.out
```

### Usar el script `compilar-y-ejecutar.sh`

Si se desea, se incluye el script `compilar-y-ejecutar.sh` con el cual se puede realizar la compilación y ejecución del código de forma directa.

## Ejecución

La ejecución del programa es muy simple e intuitiva, pero podría mejorar en su interacción con el usuario para volverlo más simple, por ahora la salida sería:

```txt
Combinación, dependencia e independencia lineal
Escuela Superior de Cómputo - Instituto Politécnico Nacional
Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal

Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
Programa: 4

¿Cuántos vectores, además del vector u, deseas ingresar?
[2 - 10]> 3
¿Cuántos elementos tendrán los vectores?
[2 - 10]> 3
A continuación, se realizará la lectura de los 3 vectores del esapcio generado.
Leyendo datos para el vector #1:
Vector #1, elemento #1: 1
Vector #1, elemento #2: 2
Vector #1, elemento #3: 3
Leyendo datos para el vector #2:
Vector #2, elemento #1: -1
Vector #2, elemento #2: 4
Vector #2, elemento #3: 5
Leyendo datos para el vector #3:
Vector #3, elemento #1: 7
Vector #3, elemento #2: 3
Vector #3, elemento #3: 3
Ahora se leerá el vector u.
Vector U, elemento #1: 1
Vector U, elemento #2: 1
Vector U, elemento #3: 1

¿Los vectores son linealmente dependientes?
Conclusión: Los vectores son linealmente independientes (L.I.) ya que los escalares solución son todos cero.

¿U es una combinación lineal de <v1, v2,...,vn>?
Conclusión: U si es combinación lineal de los vectores en el esapcio generado. El sistema tuvo solución única, por lo que existen escalares que satisfacen las condiciones.

Los escalares que prueban que U es una combinación lineal de los vectores son:

    · a_{1}: -0.2
    · a_{2}: 0.2
    · a_{3}: 0.2

Fin de ejecución.
```

## Conclusión

Este programa me ayudó a consolidar mis librerías `Matriz.hpp` y `GaussJordan.hpp` para poder operar con matrices y solucionar sistemas de ecuaciones mediante las mismas. Debido a esto, el código del programa (`main.cpp`) es realmente trivial y únicamente reutiliza conceptos y funcionalidades de las librerías ya mencionadas.

Me queda pendiente la parte de sustituir directamente valores para cuando se tienen infinidad de soluciones, tengo el problema de que cuando hay más de un delta, no logro visualizar cómo recibir parámetros para cada delta de forma variable además de que no logré implementar la funcionalidad para interpretar, a partir de una ecuación, una función que regrese valores. Espero poder complementarla posteriormente.

## Alumno

Humberto Alejandro Ortega Alcocer
2016630495
Correo: [hortegaa1500@alumno.ipn.mx](mailto:hortegaa1500@alumno.ipn.mx)

Semestre: Septiembre 2020 - Febrero 2021

29 de Noviembre de 2020.
