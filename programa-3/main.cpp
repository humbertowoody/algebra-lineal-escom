/**
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 * Programa que resuelve un sistema de ecuaciones lineales por el método: Gauss-Jordan.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 3
 * 31 de Octubre de 2020.
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-3
 */
#include <iostream>                 // Operaciones de entrada y salida estándar.
#include "GaussJordan.hpp"          // Definición de la clase.
#include "ExcepcionGaussJordan.hpp" // Excepciones del método Gauss Jordan.
#include "ExcepcionMatriz.hpp"      // Excepciones de alguna operación subyacente con matrices.

// Constantes principales de ejecución.
#define FIN_DE_PROGRAMA_EXITOSO 0              // Si el programa se ejecutó sin problemas.
#define FIN_DE_PROGRAMA_ERRONEO_MATRIZ -1      // Cuando hubo problemas con la clase matriz durante la ejecución del programa.
#define FIN_DE_PROGRAMA_ERRONEO_GAUSSJORDAN -2 // Cuando hubo problemas con la clase Gauss-Jordan durante la ejecución del programa.
#define FIN_DE_PROGRAMA_ERRONEO_DESCONOCIDO -3 // Cuando hubo algún problema que no conocemos y no podemos controlar.

/**
 * Función principal de programa.
 */
int main()
{
  // Creamos un objeto del Solucionador de Gauss Jordan con tipo de dato float.
  GaussJordan<float> *solucionadorGaussJordan = new GaussJordan<float>();

  // Imprimimos mensaje inicial sobre el programa.
  std::cout << "Sistemas de Ecuaciones Lineales de MxN por Gauss-Jordan" << std::endl
            << "Escuela Superior de Cómputo - Instituto Politécnico Nacional" << std::endl
            << "Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal" << std::endl
            << std::endl
            << "Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>" << std::endl
            << "Programa: 3" << std::endl
            << std::endl;

  // Ejecutamos el proceso dentro de un try/catch para controlar errores.
  try
  {
    std::cout << "Paso 1: Leer datos de entrada." << std::endl;
    solucionadorGaussJordan->leerDatos();
    std::cout << std::endl;

    std::cout << "Paso 2: Diagonalizar la matriz extendida." << std::endl;
    solucionadorGaussJordan->diagonalizarMatriz();
    std::cout << std::endl;

    std::cout << "Paso 3: Verificar el tipo de solución." << std::endl;
    solucionadorGaussJordan->verificarTipoSolucion();
    std::cout << std::endl;

    std::cout << "Paso 4: Calcular solución (si la hay)." << std::endl;
    solucionadorGaussJordan->calcularSolucionFinal();
    std::cout << std::endl;
  }
  catch (ExcepcionMatriz &e) // Excepciones de la clase Matriz.
  {
    std::cerr << "Error en sistema " << solucionadorGaussJordan->obtenerNumeroVariables() << "x" << solucionadorGaussJordan->obtenerNumeroEcuaciones() << std::endl;
    // Mostramos mensaje.
    std::cerr << "Ocurrió un problema manipulando la matriz:" << std::endl
              << e.id() << " - " << e.mensaje() << std::endl;

    // Terminamos ejecución con error, exit status = -1.
    return FIN_DE_PROGRAMA_ERRONEO_MATRIZ;
  }
  catch (ExcepcionGaussJordan &e) // Excepciones de la clase Gauss-Jordan.
  {
    // Mostramos mensaje.
    std::cerr << "Ocurrió un error en el proceso de Gauss-Jordan del programa:" << std::endl
              << e.id() << " - " << e.mensaje() << std::endl;

    // Terminamos ejecución con error, exit status = -2.
    return FIN_DE_PROGRAMA_ERRONEO_GAUSSJORDAN;
  }
  catch (const std::exception &e) // Excepciones estándar.
  {
    // Mostramos mensaje.
    std::cerr << "Ocurrió un error durante la ejecución inesperado:" << std::endl
              << "Error: " << e.what() << std::endl;

    // Terminamos ejecución con error, exit status = -3.
    return FIN_DE_PROGRAMA_ERRONEO_DESCONOCIDO;
  }

  // En este punto, el programa finalizó su ejecución correctamente.
  // Mostramos un mensaje de finalización.
  std::cout << "Fin de ejecución de programa." << std::endl
            << std::endl;

  // Regresamos un exit status = 0.
  return FIN_DE_PROGRAMA_EXITOSO;
}