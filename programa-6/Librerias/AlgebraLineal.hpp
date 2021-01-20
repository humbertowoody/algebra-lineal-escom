/**
 * AlgebraLineal.hpp
 * En este archivo se describe el espacio de nombres "algebralineal" en el cual
 * se colocan distintas operaciones para la materia de álgebra lineal que se apoyan
 * de las librerías previamente escritas para manipulación de matrices y el
 * procedimiento de Gauss-Jordan.
 */
#ifndef ALGEBRA_LINEAL_HPP_INCLUDED
#define ALGEBRA_LINEAL_HPP_INCLUDED

// Librerías para operaciones.
#include "./Matriz.hpp"
#include "./GaussJordan.hpp"

namespace algebralineal
{
  // Tipos de datos re-definidos.
  typedef std::vector<float> vectorReal;          // Vector con números reales
  typedef std::vector<vectorReal> vectoresReales; // Vector con vectores de números reales.

  // Estructura que representa una coordenada.
  typedef struct struct_coordenada
  {
    float x;
    float y;
  } coordenada;

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
  void imprimirVectoresReales(vectoresReales); // Imprime un conjunto de vectores reales en la terminal.
  void imprimirVectorReal(vectorReal);         // Imprime un vector real en la terminal.

  // Operaciones con coordenadas.
  Matriz<float> matrizDesdeCoordenada(coordenada); // Realiza la conversión de una coordenada en una matriz.
  coordenada coordenadaDesdeMatriz(Matriz<float>); // Realiza la conversión de una matriz en una coordenada.

  // Transformaciones Lineales en R^2
  coordenada reflexionRespectoAEjeX(coordenada); // Transformación lineal de reflexión en eje x.
  coordenada reflexionRespectoAEjeY(coordenada); // Transformación lineal de reflexión en eje y.
  coordenada corteEjeX(float, coordenada);       // Transformación lineal de corte en eje x.
  coordenada corteEjeY(float, coordenada);       // Transformación lineal de corte en eje y.
  coordenada expansionEjeX(float, coordenada);   // Transformación lineal de expansión en eje x.
  coordenada expansionEjeY(float, coordenada);   // Transformación lineal de expansión en eje y.
  coordenada compresionEjeX(float, coordenada);  // Transformación lineal de compresión en eje x.
  coordenada compresionEjeY(float, coordenada);  // Transformación lineal de compresión en eje y.
  coordenada rotacion(float, coordenada);        // Transformación lineal de rotación.

} // namespace algebralineal

#endif // ALGEBRA_LINEAL_HPP_INCLUDED
