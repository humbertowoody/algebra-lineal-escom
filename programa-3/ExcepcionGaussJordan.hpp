/**
 * ExcepcionMatriz.hpp
 * Definición de la clase ExcepcionMatriz para el manejo de excepciones de la librería de matrices.
 *
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 * Programa que resuelve un sistema de ecuaciones lineales por el método: Gauss-Jordan.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 3
 * 31 de Octubre de 2020.
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-2
 *
 */
#ifndef EXCEPCION_GAUSS_JORDAN_HPP
#define EXCEPCION_GAUSS_JORDAN_HPP

// Este es el número de excepciones soportadas por nosotros.
#define NUMERO_EXCEPCIONES_GAUSS_JORDAN 3

// Aquí definimos todos los errores posibles.
#define ERROR_GAUSS_JORDAN_DESCONOCIDO "0 ¡Error desconocido!"
#define ERROR_GAUSS_JORDAN_MATRIZ_EXISTENTE "1 No es posible leer la matriz extendida porque esta ya ha sido leída"
#define ERROR_GAUSS_JORDAN_MATRIZ_INEXISTENTE_PARA_DIAGONALIZACION "2 No existe una matriz extendida para diagonalizar"
#define ERROR_GAUSS_JORDAN_MATRIZ_DIAGONALIZADA_INEXISTENTE_PARA_VERIFICAR_SOLUCION "3 No existe una matriz diagonalizada para verificar la solución"
#define ERROR_GAUSS_JORDAN_SOLUCION_NO_VERIFICADA "4 No es posible calcular la solucion final si no se ha verificado previamente"
#define ERROR_GAUSS_JORDAN_BANDERA_SOLUCION_IRRECONOCIBLE "5 La bandera de solución tiene un valor irreconocible"

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