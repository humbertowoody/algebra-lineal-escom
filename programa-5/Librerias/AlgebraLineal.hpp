/**
 * AlgebraLineal.hpp
 * En este archivo se describe el espacio de nombres "algebralineal" en el cual
 * se colocan distintas operaciones para la materia de álgebra lineal que se apoyan
 * de las librerías previamente escritas para manipulación de matrices y el
 * procedimiento de Gauss-Jordan.
 */
#include <iostream>
#include "./Matriz.hpp"
#include "./GaussJordan.hpp"

namespace algebralineal
{
  // Tipos de datos re-definidos.
  typedef std::vector<float> vectorReal;          // Vector con números reales
  typedef std::vector<vectorReal> vectoresReales; // Vector con vectores de números reales.

  // Dependencia lineal.
  bool vectoresLinealmenteIndependientes(vectoresReales);                                                              // Verifica si un conjunto de vectores son L.I. entre sí.
  bool vectoresLinealmenteDependientes(vectoresReales);                                                                // Verifica si un conjunto de vectores son L.D. entre sí.
  vectoresReales busquedaCombinacionLinealmenteIndependiente(int, int, int, vectoresReales &, const vectoresReales &); // Verifica si existe una permutación en dónde cierto número de vectores sean L.I.

  // Subespacios vectoriales.
  bool esBase(vectoresReales, vectorReal);                // Determina si un vector es una base de un grupo de vectores determinado.
  bool generaATodoElEspacio(vectoresReales, vectorReal);  // Determina si un vector es generador de todo el espacio en cuestión.
  vectoresReales obtenerBaseEspacioNulo(Matriz<float>);   // Obtiene una base del espacio nulo de un conjunto de vectores reales.
  vectoresReales obtenerBaseEspacioImagen(Matriz<float>); // Obtiene una base del esapcio imagen de un conjunto de vectores reales.

  // Impresión.
  void imprimirVectoresReales(vectoresReales);
  void imprimirVectorReal(vectorReal);

} // namespace algebralineal
