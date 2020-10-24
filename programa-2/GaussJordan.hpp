/**
 * GaussJordan.hpp
 * Definición de la clase GaussJordan para resolver sistemas de ecuaciones lineales mediante
 * matrices.
 *
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 * Programa que resuelve un sistema de ecuaciones lineales por el método: Gauss-Jordan.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 2
 * 23 de Octubre de 2020.
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-2
 *
 */
#ifndef GAUSS_JORDAN_HPP
#define GAUSS_JORDAN_HPP

#include "Matriz.cpp" // Para el manejo de matrices.

// Constantes para Gauss-Jordan.
#define MAX_VARIABLES (MAX_COLUMNAS - 1) // Máximo número de columnas en una matriz reservando un espacio para los términos independientes.
#define MIN_VARIABLES 2                  // Mínimo número de variables para el sistema de ecuaciones.
#define MAX_ECUACIONES MAX_FILAS         // Máximo número de ecuaciones.
#define MIN_ECUACIONES 2                 // Mínimo número de ecuaciones.
#define SOLUCION_UNICA 0                 // El sistema tiene una solución unica.
#define INFINIDAD_SOLUCIONES 1           // El sistema tiene infinidad de soluciones.
#define SIN_SOLUCION 2                   // El sistema no tiene solución.
#define SOLUCION_NO_CALCULADA -1         // No se ha realizado el cálculo de la solución.

/**
 * Solucion Gauss Jordan
 * Clase que contiene todas las funciones para resolver sistemas
 * de ecuaciones por el método de Gauss Jordan.
 */
template <class P>
class GaussJordan
{
public:
  // Funciones base.
  GaussJordan();  //  Constructor base.
  ~GaussJordan(); // Destructor.

  // Funciones públicas.
  void leerDatos();             // Lee los datos de entrada.
  void diagonalizar();          // Diagonaliza la matriz extendida.
  void verificarTipoSolucion(); // Verifica e imprime qué tipo de solución tiene la matriz.
  void imprimirSolucion();      // Imprime la solución final.

private:
  Matriz<P> *matriz_extendida, // La matriz extendida.
      *matriz_diagonalizada;   // La matriz diagonalizada.

  int numero_variables,  // Número de variables en el sistema.
      numero_ecuaciones, // Número de ecuaciones en el sistema.
      bandera_solucion;  // Bandera que indica el tipo de solución (si la hay).
};

#endif
