/**
 * GaussJordan.hpp
 * Definición de la clase GaussJordan para resolver sistemas de ecuaciones lineales mediante
 * matrices.
 *
 */
#ifndef GAUSS_JORDAN_HPP
#define GAUSS_JORDAN_HPP

#include "Matriz.cpp" // Para el manejo de matrices.

// Constantes para Gauss-Jordan.
#define MAX_VARIABLES (MAX_COLUMNAS - 1) // Máximo número de columnas en una matriz reservando un espacio para los términos independientes.
#define MIN_VARIABLES 2                  // Mínimo número de variables para el sistema de ecuaciones.

#define MAX_ECUACIONES MAX_FILAS // Máximo número de ecuaciones.
#define MIN_ECUACIONES 2         // Mínimo número de ecuaciones.

#define SOLUCION_UNICA 0         // El sistema tiene una solución unica.
#define INFINIDAD_SOLUCIONES 1   // El sistema tiene infinidad de soluciones.
#define SIN_SOLUCION 2           // El sistema no tiene solución.
#define SOLUCION_NO_CALCULADA -1 // No se ha realizado el cálculo de la solución.

#define SIMBOLO_DELTA "Δ" // Para imprimir el símbolo de Delta apropiadamente.

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
  GaussJordan(Matriz<P>); // Constructor general.
  ~GaussJordan();         // Destructor.

  // Funciones públicas.
  int obtenerTipoDeSolucion();                          // Regresa la bandera con el tipo de solución para el sistema proporcionado.
  Matriz<P> obtenerMatrizExtendidaOriginal();           // Regresa la matriz extendida original.
  Matriz<P> obtenerMatrizDeCoeficientesOriginal();      // Regresa la matriz de coeficientes original.
  Matriz<P> obtenerMatrizExtendidaDiagonalizada();      // Regresa la matriz extendida diagonalizada.
  Matriz<P> obtenerMatrizDeCoeficientesDiagonalizada(); // Regresa la matriz de coeficientes diagonalizada.
  int obtenerNumeroVariables();                         // Regresa el número de variables en nuestro sistema.
  int obtenerNumeroEcuaciones();                        // Regresa el número de ecuaciones
  std::vector<P> obtenerSolucionesUnicas();             // Regresa un vector con las soluciones correspondientes a las variables.
  void mostrarInfinidadDeSoluciones();                  // Muestra las ecuaciones que representan las soluciones válidas dada una infinidad de soluciones.
  void mostrarConclusion();                             // Muestra en la terminal la conclusión del procedimiento Gauss-Jordan.

private:
  // Funciones privadas.
  void resolver();              // Realiza el procedimiento Gauss-Jordan.
  void diagonalizarMatriz();    // Diagonaliza la matriz extendida.
  void verificarTipoSolucion(); // Verifica el tipo de solución a partir de la matriz diagonalizada.

  // Variables privadas.
  Matriz<P> matriz_extendida,         // La matriz extendida.
      matriz_extendida_diagonalizada; // La matriz extendida diagonalizada.

  int bandera_solucion; // Bandera que indica el tipo de solución.
};

#endif // GAUSS_JORDAN_HPP
