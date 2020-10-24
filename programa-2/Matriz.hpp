/**
 * Matriz.hpp
 * Definición de la clase Matriz para realizar operaciones con matrices de distintos tipos
 * así como tamaños.
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
#ifndef MATRIZ_HPP
#define MATRIZ_HPP

// El número máximo de columnas para la matriz.
#ifndef MAX_COLUMNAS
#define MAX_COLUMNAS 20 // 20 es un valor razonable.
#endif

// El número máximo de filas en la matriz.
#ifndef MAX_FILAS
#define MAX_FILAS 20 // 20 es un valor razonable.
#endif

// El número de caracteres reservados para imprimir la matriz.
#ifndef CARACTERES_RESERVADOS_MATRIZ   // -82.73  Número contemplado estándar.
#define CARACTERES_RESERVADOS_MATRIZ 6 // 123456  Conteo de caracteres = 6.
#endif

// Librerías necesarias.
#include <vector>              // Para el manejo dinámico de la matriz.
#include "ExcepcionMatriz.hpp" // Para las excepciones asociadas a la clase Matriz.

/**
 * Matriz<P>
 * Una representación dinámica de una Matriz con tipo de dato variable.
 * A su vez, permite realizar múltiples operaciones matriciales elementales.
 */
template <class P>
class Matriz
{
public:
  // Funciones fundamentales.
  Matriz();                            // Constructor base.
  Matriz(const Matriz &);              // Constructor de copia.
  Matriz(std::vector<std::vector<P>>); // Constructor para vectores dinámicos.
  // ~Matriz();                           // Destructor.

  // Funciones públicas.

  // Getters.
  // P obtenerElemento(int, int); // Obtiene el valor en una posición de la matriz.
  int obtenerNumeroColumnas(); // Obtiene el número de columnas actual en la matriz.
  int obtenerNumeroFilas();    // Obtiene el número de filas presentes en la matriz.
  int obtenerRango();          // Obtener el rango de la matriz.

  // Setters.
  // Matriz asignarElemento(int, int, P); // Asigna un valor a una posición en la matriz existente.
  void insertarFila(std::vector<P>); // Inserta una nueva fila en la Matriz.
  // Matriz eliminarFila(int);            // Elimina una fila dentro de la matriz.
  // void insertarColumna(std::vector<P>); // Inserta una nueva columna la Matriz.
  Matriz eliminarColumna(int); // Elimina una columna de la matriz.

  // Operaciones elementales con Matrices.
  Matriz intercambiarFilas(int, int); // Intercambia dos filas de una Matriz.
  // Matriz multiplicarPorEscalar(P);          // Multiplica la matriz por un escalar.
  // Matriz multiplicarFilaPorEscalar(int, P); // Multiplica una fila por un escalar.

  // Operaciones con Matrices.
  Matriz diagonalizar(); // Diagonaliza una Matriz.

  // Operaciones de entrada y salida.
  void imprimir(); // Imprime la matriz.
  // void imprimir(int);      // Imprime N filas.
  // void imprimir(int, int); // Imprime N filas por M columnas.

private:
  // Funciones privadas.
  bool indiceFilaValido(int);           // Verifica si el índice de la fila proporcionado es válido para la matriz.
  bool indiceColumnaValido(int);        // Verifica si el índice de la columna proporcionado es válido para la matriz.
  void imprimirEnRango(int, int);       // Imprime la matriz en un rango determinado.
  bool filaConsistente(std::vector<P>); // Verifica si una fila es consistente con la matriz actual.

  // Variables privadas.
  std::vector<std::vector<P>> matriz_vector; // La matriz dinámica.
};

#endif // MATRIZ_HPP