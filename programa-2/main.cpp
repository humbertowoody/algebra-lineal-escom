/**
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 * Programa que resuelve un sistema de ecuaciones lineales por el método: Gauss-Jordan.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 2
 * 23 de Octubre de 2020.
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-2
 */
#include <iostream>            // Operaciones de entrada y salida estándar.
#include "GaussJordan.hpp"     // Definición de la clase.
#include "ExcepcionMatriz.hpp" // Excepciones.

// Constantes principales de ejecución.
#define FIN_DE_PROGRAMA_EXITOSO 0  // Si el programa se ejecutó sin problemas.
#define FIN_DE_PROGRAMA_ERRONEO -1 // Cuando hubo problemas durante la ejecución del programa.

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
            << "Programa: 2" << std::endl
            << std::endl;

  // Ejecutamos el proceso dentro de un try/catch para una futura implementación de excepciones
  // en la clase Gauss Jordan.
  try
  {
    std::cout << "Paso 1: Leer datos de entrada." << std::endl;
    solucionadorGaussJordan->leerDatos();
    std::cout << std::endl;

    std::cout << "Paso 2: Diagonalizar la matriz extendida." << std::endl;
    solucionadorGaussJordan->diagonalizar();
    std::cout << std::endl;

    std::cout << "Paso 3: Verificar el tipo de solución." << std::endl;
    solucionadorGaussJordan->verificarTipoSolucion();
    std::cout << std::endl;

    std::cout << "Paso 4: Mostrar la solución (si existe)." << std::endl;
    solucionadorGaussJordan->imprimirSolucion(); // Falta completar implementación :(
    std::cout << std::endl;
  }
  catch (ExcepcionMatriz &e) // Por ahora sólamente implementé excepciones para la clase Matriz, pero la idea es que sean del solucionador GaussJordan.
  {
    // Mostramos mensaje.
    std::cerr << "Ocurrió un error durante la ejecución del programa:" << std::endl
              << e.id() << " - " << e.mensaje() << std::endl;

    // Terminamos ejecución con error, exit status = -1.
    return FIN_DE_PROGRAMA_ERRONEO;
  }

  // En este punto, el programa finalizó su ejecución correctamente.
  // Mostramos un mensaje de finalización.
  std::cout << "Fin de ejecución de programa." << std::endl
            << std::endl;

  // Regresamos un exit status = 0.
  return FIN_DE_PROGRAMA_EXITOSO;
}