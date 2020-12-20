/**
 * ExcepcionMatriz.cpp
 * Implementación de la clase ExcepcionMatriz para el manejo de excepciones al trabajar
 * con Matrices.
 */
#include <string>                   // Para el manejo de cadenas de caracteres.
#include <sstream>                  // Para convertir una cadena de caracteres en un flujo válido para operaciones de I/O.
#include "ExcepcionGaussJordan.hpp" // Para la definición del prototipo de la clase.

/**
 * Excepcion Gauss Jordan
 * Constructor de la clase.
 */
ExcepcionGaussJordan::ExcepcionGaussJordan(std::string mensaje_excepcion)
{
  // Creamos un flujo de strings para leer los datos.
  std::stringstream ss(mensaje_excepcion);

  // Tratamos de extraer el id del error.
  ss >> id_error;

  // Verificamos que el id del error esté en el rango aceptable.
  if (id_error < 0 || id_error > NUMERO_EXCEPCIONES_GAUSS_JORDAN)
  {
    // El default será 0.
    id_error = 0;
  }

  // Buscamos la posición del primer espacio en blanco.
  std::string::size_type posicion = mensaje_excepcion.find(' ');

  // Si se encontró una posición para el espacio, guardamos el mensaje
  // sino, añadimos una clarificación.
  if (posicion != std::string::npos)
  {
    // Una sub-cadena a partir de la posición + 1.
    mensaje_error = mensaje_excepcion.substr(posicion + 1);
  }
  else
  {
    mensaje_error = mensaje_excepcion + std::string(" (Excepción no reconocida)");
  }
}