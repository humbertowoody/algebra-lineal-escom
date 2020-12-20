/**
 * ExcepcionMatriz.hpp
 * Definición de la clase ExcepcionMatriz para el manejo de excepciones de la librería de matrices.
 *
 */
#ifndef EXCEPCION_MATRIZ_HPP
#define EXCEPCION_MATRIZ_HPP

// Este es el número de excepciones soportadas por nosotros.
#define NUMERO_EXCEPCIONES_MATRIZ 7

// Aquí definimos todos los errores posibles.
#define ERROR_MATRIZ_DESCONOCIDO "0 ¡Error desconocido!"
#define ERROR_MATRIZ_INDICE_FILA_INVALIDO "1 El índice para la fila no es válido"
#define ERROR_MATRIZ_INDICE_COLUMNA_INVALIDO "2 El índice para la columna no es válido"
#define ERROR_MATRIZ_FILA_INCONSISTENTE "3 La fila que se intentó ingresar no es consistente con los elementos presentes en la matriz"
#define ERROR_MATRIZ_COLUMNA_INCONSISTENTE "4 La columna que se intentó ingresar no es consistente con los elementos presentes en la matriz"
#define ERROR_MATRIZ_DIMENSIONES_SUMA "5 Las dimensiones de las matrices no son compatibles para realizar la suma"
#define ERROR_MATRIZ_DIMENSIONES_RESTA "6 Las dimensiones de las matrices no son compatibles para realizar la resta"
#define ERROR_MATRIZ_DIMENSIONES_MULTIPLICACION "7 Las dimensiones de las matrices no son compatibles para realizar la multiplicación"

// Librerías requeridas.
#include <string> // Para el manejo de cadenas de caracteres.

/**
 * Excepción Matriz
 * Clase para el manejo de excepciones en las operaciones con matrices.
 */
class ExcepcionMatriz
{
public:
  ExcepcionMatriz(std::string mensaje = ERROR_MATRIZ_DESCONOCIDO); // Constructor.

  inline std::string mensaje() const { return mensaje_error; } // Obtiene el mensaje.
  inline int id() const { return id_error; }                   // Obtiene el id del error.

private:
  std::string mensaje_error; // El mensaje de la excepción.
  int id_error;              // El número de error.
};

#endif // EXCEPCION_MATRIZ