/**
 * Matriz.hpp
 * Definición de la clase Matriz para realizar operaciones con matrices de distintos tipos
 * así como tamaños.
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

// Bandera para controlar si queremos imprimir mensajes de debug.
#ifndef DEBUG_MATRIZ
#define DEBUG_MATRIZ false // Por default será falso.
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
  ~Matriz();                           // Destructor.

  // Funciones públicas.

  // Getters.
  P obtenerElemento(int, int);                // Obtiene el valor en una posición de la matriz.
  int obtenerNumeroColumnas();                // Obtiene el número de columnas actual en la matriz.
  int obtenerNumeroFilas();                   // Obtiene el número de filas presentes en la matriz.
  int obtenerRango();                         // Obtiene el rango de la matriz.
  std::vector<P> obtenerDiagonalPrincipal();  // Obtiene un vector<P> con los elementos presentes en la diagonal principal.
  std::vector<P> obtenerDiagonalSecundaria(); // Obtiene un vector<P> con los elementos presentes en la diagonal secundaria.
  std::vector<P> obtenerFila(int);            // Obtiene un vector<P> con los elementos presentes en la fila solicitada.
  std::vector<P> obtenerColumna(int);         // Obtiene un vector<P> con los elementos presentes en la columna solicitada.

  // Setters.
  Matriz asignarElemento(int, int, P);    // Asigna un valor a una posición en la matriz existente.
  Matriz insertarFila(std::vector<P>);    // Inserta una nueva fila en la Matriz.
  Matriz eliminarFila(int);               // Elimina una fila dentro de la matriz.
  Matriz insertarColumna(std::vector<P>); // Inserta una nueva columna la Matriz.
  Matriz eliminarColumna(int);            // Elimina una columna de la matriz.

  // Operaciones con Matrices.
  P calcularTrazaDeLaMatriz();              // Realiza el cálculo de la traza de la matriz.
  Matriz intercambiarFilas(int, int);       // Intercambia dos filas de una Matriz.
  Matriz diagonalizacionInferior();         // Proceso de diagonalización inferior.
  Matriz diagonalizacionSuperior();         // Proceso de diagonalización superior.
  Matriz sumar(Matriz);                     // Suma de matrices.
  Matriz sumar(P);                          // Suma de matriz + escalar.
  Matriz restar(Matriz);                    // Resta de matrices.
  Matriz restar(P);                         // Resta de matriz - escalar.
  Matriz multiplicarFilaPorEscalar(int, P); // Multiplica una fila por un escalar.
  Matriz multiplicar(Matriz);               // Multiplicación de matrices.
  Matriz multiplicar(P);                    // Multiplicación de matriz * escalar.
  Matriz transposicion();                   // Cálculo de la matriz transpuesta.

  // Para determinar el tipo de una matriz.
  bool esMatrizNula();               // Verifica si la matriz es una matriz nula.
  bool esMatrizFila();               // Verifica si la matriz es una matriz fila.
  bool esMatrizColumna();            // Verifica si la matriz es una matriz columna.
  bool esMatrizCuadrada();           // Verifica si la matriz es una matriz cuadrada.
  bool esMatrizRectangular();        // Verifia si la matriz es una matriz rectangular.
  bool esMatrizTriangularSuperior(); // Verifica si la matriz es una matriz triangular inferior.
  bool esMatrizTriangularInferior(); // Verifica si la matriz es una matriz triangular superior.
  bool esMatrizDiagonal();           // Verifica si la matriz es una matriz diagonal.
  bool esMatrizIdentidad();          // Verifica si la matriz es una matriz identidad.
  bool esMatrizSimetrica();          // Verifica si la matriz es simétrica.
  bool esIgual(Matriz);              // Verifica si dos matrices son iguales.

  // Operaciones de entrada y salida.
  void imprimir();              // Imprime la matriz.
  int maximoNumeroCaracteres(); // Calcula el máximo número de caracteres empleado por un elemento de la matriz.

private:
  // Funciones privadas.
  bool indiceFilaValido(int);              // Verifica si el índice de la fila proporcionado es válido para la matriz.
  bool indiceColumnaValido(int);           // Verifica si el índice de la columna proporcionado es válido para la matriz.
  void imprimirEnRango(int, int);          // Imprime la matriz en un rango determinado.
  bool filaConsistente(std::vector<P>);    // Verifica si una fila es consistente con la matriz actual.
  bool columnaConsistente(std::vector<P>); // Verifica si una columna es consistente con la matriz actual.

  // Variables privadas.
  std::vector<std::vector<P>> matriz_vector; // La matriz dinámica.
};

#endif // MATRIZ_HPP