/**
 * UtileriasMatriz.hpp
 * Conjunto de funciones para operaciones genéricas de
 * matrices.
 */
#include <iostream>
#include <iomanip>
#include "./Matriz.hpp"
#include "./GaussJordan.hpp"

/**
 * Leer Sistema de Ecuaciones Interactivo
 * Realiza la lectura desde la terminal de un sistema de ecuaciones de forma
 * interactiva preguntando cada variable y las dimensiones.
 */
template <class P>
Matriz<P> leerSistemaDeEcuacionesInteractivo()
{
  // Variables locales.
  std::vector<P> fila_temp;
  P dato_temp;
  int numero_variables,
      numero_ecuaciones;
  Matriz<P> matriz_extendida;

  // Leer el número de variables.
  do
  {
    // Mostramos mensaje.
    std::cout << "¿Cuántas variables tiene el sistema de ecuaciones?" << std::endl
              << "[" << MIN_VARIABLES << " - " << MAX_VARIABLES << "]> ";

    // Leemos el dato.
    std::cin >> numero_variables;
  } while (numero_variables < MIN_VARIABLES || numero_variables > MAX_VARIABLES); // Validación de entradas.

  // Leer el número de ecuaciones.
  do
  {
    // Mostramos mensaje.
    std::cout << "¿Cuántas ecuaciones tiene el sistema de ecuaciones?" << std::endl
              << "[" << MIN_ECUACIONES << " - " << MAX_ECUACIONES << "]> ";

    // Leemos el dato.
    std::cin >> numero_ecuaciones;
  } while (numero_ecuaciones < MIN_ECUACIONES || numero_ecuaciones > MAX_ECUACIONES); // Validación de entradas.

  // Leer los coeficientes y los términos independientes.
  for (int ecuacion = 1; ecuacion <= numero_ecuaciones; ecuacion++)
  {
    // Mensaje para la fila.
    std::cout << "Se leerán los datos para la ecuación #" << ecuacion << "." << std::endl;

    // Limpiamos el vector para introducir datos nuevos.
    fila_temp.clear();

    // Leemos los datos necesarios.
    for (int columna = 0; columna <= numero_variables; columna++)
    {
      // Modificamos el mensaje dependiendo si es una variable x_{} o el término independiente.
      if (columna < numero_variables)
      {
        std::cout << "Introduce el valor para la variable x_{" << (columna + 1) << "}" << std::endl
                  << "> ";
      }
      else
      {
        std::cout << "Introduce el valor del término independiente b_{" << ecuacion << "}" << std::endl
                  << "> ";
      }

      // La lectura es idéntica en ambos casos.
      std::cin >> dato_temp;

      // Añadimos a la fila.
      fila_temp.push_back(dato_temp);
    }

    try
    {
      // Insertamos la fila en la matriz.
      matriz_extendida = matriz_extendida.insertarFila(fila_temp);
    }
    catch (ExcepcionMatriz &e)
    {
      // La operación arrojó alguna excepción, la delegamos al iniciador de la llamada.
      throw e;
    }
  }

  // Mostramos el sistema de ecuaciones.
  std::cout << "El sistema de ecuaciones ingresado es:" << std::endl;

  // Iteramos en los elementos de la matriz extendida.
  for (int fila = 0; fila < numero_ecuaciones; fila++)
  {
    for (int columna = 0; columna <= numero_variables; columna++)
    {
      // Revisamos el tipo de variable.
      if (columna < numero_variables)
      {
        // Es alguna x_{columna}
        std::cout << (matriz_extendida.obtenerElemento(fila, columna) < 0 ? " " : " +") << matriz_extendida.obtenerElemento(fila, columna) << "x_{" << columna + 1 << "}";
      }
      else
      {
        // Es el término independiente b_{fila}
        std::cout << " = " << matriz_extendida.obtenerElemento(fila, columna) << "b_{" << fila + 1 << "}";
      }
    }
    // Salto de línea.
    std::cout << std::endl;
  }

  // Mostramos la matriz leída.
  std::cout << "Se ha leído la matriz extendida (A*) de " << matriz_extendida.obtenerNumeroColumnas()
            << " columnas y " << matriz_extendida.obtenerNumeroFilas()
            << " filas siguiente:" << std::endl;
  matriz_extendida.imprimir();

  // Salto de línea.
  std::cout << std::endl;

  // Regresamos la matriz extendida leída.
  return matriz_extendida;
}
