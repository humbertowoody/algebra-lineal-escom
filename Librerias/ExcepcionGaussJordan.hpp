/**
 * ExcepcionMatriz.hpp
 * Definición de la clase ExcepcionMatriz para el manejo de excepciones de la librería de matrices.
 *
 */
#ifndef EXCEPCION_GAUSS_JORDAN_HPP
#define EXCEPCION_GAUSS_JORDAN_HPP

// Este es el número de excepciones soportadas por nosotros.
#define NUMERO_EXCEPCIONES_GAUSS_JORDAN 4

// Aquí definimos todos los errores posibles.
#define ERROR_GAUSS_JORDAN_DESCONOCIDO "0 ¡Error desconocido!"
#define ERROR_GAUSS_JORDAN_DIMENSIONES_MATRIZ "1 Las dimensiones de la matriz proporcionada no representan un sistema de ecuaciones lineales válido"
#define ERROR_GAUSS_JORDAN_SOLUCION_UNICA_INEXISTENTE "2 No se pueden obtener soluciones únicas de un sistema que no tiene solución única"
#define ERROR_GAUSS_JORDAN_BANDERA_SOLUCION_IRRECONOCIBLE "3 La bandera de solución tiene un valor irreconocible"
#define ERROR_GAUSS_JORDAN_INFINIDAD_DE_SOLUCIONES_INEXISTENTES "4 No se pueden mostrar las ecuaciones para infinidad de soluciones de un sistema que no tiene infinidad de soluciones"

// Librerías requeridas.
#include <string> // Para el manejo de cadenas de caracteres.

/**
 * Excepción Gauss-Jordan
 * Clase para el manejo de excepciones en las operaciones del solucionador
 * Gauss-Jordan.
 */
class ExcepcionGaussJordan
{
public:
  ExcepcionGaussJordan(std::string mensaje = ERROR_GAUSS_JORDAN_DESCONOCIDO); // Constructor.

  inline std::string mensaje() const { return mensaje_error; } // Obtiene el mensaje.
  inline int id() const { return id_error; }                   // Obtiene el id del error.

private:
  std::string mensaje_error; // El mensaje de la excepción.
  int id_error;              // El número de error.
};

#endif // EXCEPCION_GAUSS_JORDAN_HPP
