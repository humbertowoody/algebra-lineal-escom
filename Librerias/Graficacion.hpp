/**
 * Graficacion.hpp
 * En este archivo se describe el espacio de nombres con las funciones para realizar operaciones
 * de graficación para álgebra lineal.
 */
#ifndef GRAFICACION_AL_HPP_INCLUDED
#define GRAFICACION_AL_HPP_INCLUDED

// Librerías necesarias.
#include "AlgebraLineal.hpp"
#include <vector>
#include <string>

// Espacio de nombres para funciones y operaciones de graficación.
namespace graficacion
{
  void graficarMatrizCoordenadas(std::vector<std::vector<algebralineal::coordenada>>, std::vector<std::string>); // Para realizar la graficación de una matriz con coordenadas.
} // namespace graficacion

#endif // GRAFICACION_AL_HPP_INCLUDED
