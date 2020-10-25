/**
 * GaussJordan.cpp
 * Implementación de la clase GaussJordan para resolver sistemas de ecuaciones lineales utilizando
 * matrices.
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
#include <iostream>
#include "GaussJordan.hpp"

/**
 * Constructor Gauss Jordan base.
 * Realiza las tareas de inicialización de variables miembro y establece
 * el estado inicial de nuestro solucionador.
 */
template <class P>
GaussJordan<P>::GaussJordan()
{
  this->matriz_extendida = new Matriz<P>();       // Matriz vacía.
  this->matriz_diagonalizada = NULL;              // La matriz diagonalizada inicia vacía.
  this->numero_ecuaciones = 0;                    // Número de ecuaciones 0.
  this->numero_variables = 0;                     // Número de variables 0.
  this->bandera_solucion = SOLUCION_NO_CALCULADA; // Bandera de solución -1.
}

/**
 * Destructor de la clase Gauss Jordan.
 * TODO: Asegurarse que la clase Matriz si limpie sus chivas.
 */
template <class P>
GaussJordan<P>::~GaussJordan()
{
  // Limpiamos cualquier dato que pueda permanecer en memoria.
  numero_ecuaciones = numero_variables = bandera_solucion = (int)NULL;
  this->matriz_diagonalizada = NULL;
  this->matriz_extendida = NULL;
}

/**
 * Leer Datos
 * Esta función realiza la lectura interactiva de todos los datos que se requieren para
 * la ejecución del programa.
 */
template <class P>
void GaussJordan<P>::leerDatos()
{
  // Variables locales de la función.
  std::vector<P> fila_temp; // Fila temporal para insertar en la matriz.
  P dato_temp;              // Dato temporal para leer.

  // Leer el número de variables.
  do
  {
    // Mostramos mensaje.
    std::cout << "¿Cuántas variables tiene el sistema de ecuaciones?" << std::endl
              << "[" << MIN_VARIABLES << " - " << MAX_VARIABLES << "]> ";

    // Leemos el dato.
    std::cin >> this->numero_variables;
  } while (this->numero_variables < MIN_VARIABLES || this->numero_variables > MAX_VARIABLES); // Validación de entradas.

  // Leer el número de ecuaciones.
  do
  {
    // Mostramos mensaje.
    std::cout << "¿Cuántas ecuaciones tiene el sistema de ecuaciones?" << std::endl
              << "[" << MIN_ECUACIONES << " - " << MAX_ECUACIONES << "]> ";

    // Leemos el dato.
    std::cin >> this->numero_ecuaciones;
  } while (this->numero_ecuaciones < MIN_ECUACIONES || this->numero_ecuaciones > MAX_ECUACIONES); // Validación de entradas.

  // Leer los coeficientes y los términos independientes.
  for (int ecuacion = 1; ecuacion <= this->numero_ecuaciones; ecuacion++)
  {
    // Mensaje para la fila.
    std::cout << "Se leerán los datos para la ecuación #" << ecuacion << "." << std::endl;

    // Limpiamos el vector para introducir datos nuevos.
    fila_temp.clear();

    // Leemos los datos necesarios.
    for (int columna = 0; columna <= this->numero_variables; columna++)
    {
      // Modificamos el mensaje dependiendo si es una variable x_{} o el término independiente.
      if (columna < this->numero_variables)
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
      this->matriz_extendida = new Matriz<P>(this->matriz_extendida->insertarFila(fila_temp));
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
  for (int fila = 0; fila < this->numero_ecuaciones; fila++)
  {
    for (int columna = 0; columna <= this->numero_variables; columna++)
    {
      // Revisamos el tipo de variable.
      if (columna < this->numero_variables)
      {
        // Es alguna x_{columna}
        std::cout << (this->matriz_extendida->obtenerElemento(fila, columna) < 0 ? " " : " +") << this->matriz_extendida->obtenerElemento(fila, columna) << "x_{" << columna + 1 << "}";
      }
      else
      {
        // Es el término independiente b_{fila}
        std::cout << " = " << this->matriz_extendida->obtenerElemento(fila, columna) << "b_{" << fila + 1 << "}";
      }
    }
    // Salto de línea.
    std::cout << std::endl;
  }

  // Mostramos la matriz leída.
  std::cout << "Se ha leído la matriz de " << this->matriz_extendida->obtenerNumeroColumnas()
            << " columnas y " << this->matriz_extendida->obtenerNumeroFilas()
            << " filas siguiente:" << std::endl;
  this->matriz_extendida->imprimir();
}

/**
 * Diagonalizacion Inferior
 * Realiza el proceso de diagonalización inferior de la matriz extendida.
 */
template <class P>
void GaussJordan<P>::diagonalizacionInferior()
{
  try
  {
    // Realizamos la diagonalización.
    this->matriz_diagonalizada = new Matriz<P>(this->matriz_extendida->diagonalizacionInferior());

    // Mostramos el resultado.
    std::cout << "La matriz extendida diagonalizada es: " << std::endl;
    this->matriz_diagonalizada->imprimir();
  }
  catch (ExcepcionMatriz &e)
  {
    std::cerr << "Ocurrió un error durante la diagonalización:" << std::endl
              << "Error: " << e.id() << " - " << e.mensaje() << std::endl;
  }
}

/**
 * Verificar tipo de Solucion
 * En esta función realizamos la verificación del tipo de solución en función
 * del rango de la matriz diagonalizada por el teorema de Rouché-Fröbenius.
 */
template <class P>
void GaussJordan<P>::verificarTipoSolucion()
{
  // Revisamos si ya se realizó previamente la diagonalización de la matriz.
  if (this->matriz_diagonalizada != NULL)
  {
    // La matriz de coeficientes diagonalizada es la matriz extendida diagonalizada sin la última columna.
    Matriz<P> matriz_coeficientes_diagonalizada = this->matriz_diagonalizada->eliminarColumna(this->matriz_diagonalizada->obtenerNumeroColumnas() - 1);

    // Mostramos la matriz de coeficientes diagonalizada.
    std::cout << "Matriz coeficientes diagonalizada:" << std::endl;
    matriz_coeficientes_diagonalizada.imprimir();
    std::cout << std::endl;

    // Obtenemos el rango de la matriz extendida diagonalizada.
    int rangoMatrizExtendidaDiagonalizada = this->matriz_diagonalizada->obtenerRango();
    int rangoMatrizCoeficientesDiagonalizada = matriz_coeficientes_diagonalizada.obtenerRango();

    // Mostramos el rango ajustamos nuestra bandera de solución.
    std::cout << "El rango de la matriz extendida diagonalizada (R(A*)) es: " << rangoMatrizExtendidaDiagonalizada << std::endl;
    std::cout << "El rango de la matriz de coeficientes diagonalizada (R(A)) es: " << rangoMatrizCoeficientesDiagonalizada << std::endl;

    // Ajustamos nuestra bandera en función de los rangos calculados.
    if (rangoMatrizExtendidaDiagonalizada != rangoMatrizCoeficientesDiagonalizada)
    {
      // El sistema no tiene solución.
      this->bandera_solucion = SIN_SOLUCION;

      // Imprimimos la razón.
      std::cout << "Conclusión: El sistema no tiene solución (los rangos son distintos: R(A)=" << rangoMatrizCoeficientesDiagonalizada << " diferente de R(A*)=" << rangoMatrizExtendidaDiagonalizada << ")." << std::endl;
    }
    else
    {
      if (rangoMatrizExtendidaDiagonalizada == this->numero_variables)
      {
        // El sistema tiene solución única.
        this->bandera_solucion = SOLUCION_UNICA;

        // Imprimimos la conclusión.
        std::cout << "Conclusión: El sistema tiene solución única (los rangos son iguales al número de incógnitas: R(A)=" << rangoMatrizCoeficientesDiagonalizada << " igual a R(A*)=" << rangoMatrizExtendidaDiagonalizada << " igual al número de incógnitas (" << this->numero_variables << "))." << std::endl;
      }
      else
      {
        // El sistema tiene una infinidad de soluciones.
        this->bandera_solucion = INFINIDAD_SOLUCIONES;

        // Mostramos conclusión.
        std::cout << "Conclusión: El sistema tiene una infinidad de soluciones (los rangos son iguales entre sí, pero distintos al número de incógnitas: R(A)=" << rangoMatrizCoeficientesDiagonalizada << " igual a R(A*)=" << rangoMatrizExtendidaDiagonalizada << ", pero distintos del número de incógnitas (" << this->numero_variables << "))." << std::endl;
      }
    }
  }
  else
  {
    // Aquí deberíamos arrojar una excepción, pero por ahora un mensaje, en la siguiente versión implementaré las excepciones
    // para la clase GaussJordan.
    std::cout << "No es posible realizar la verificación del tipo de solución porque no se ha diagonalizado la matriz extendida." << std::endl;
  }
}

/**
 * Diagonalización Superior
 * Realiza la operación de diagonalizacion superior de la matriz extendida previamente diagonalizada
 * inferiormente con el fin de tener la matriz solución disponible para la solucion.
 */
// template <class P>
// void GaussJordan<P>::diagonalizacionSuperior()
// {
//   // Revisamos que exista previamente la matriz diagonalizada y que exista la bandera
//   // para solución única.
//   if (this->matriz_diagonalizada != NULL && this->bandera_solucion == SOLUCION_UNICA)
//   {
//     try
//     {
//       // Si esta operación se repite no afecta a la matriz.
//       this->matriz_diagonalizada = new Matriz<P>(this->matriz_diagonalizada->diagonalizacionSuperior());

//       // TODO: A partir de la matriz diagonalizada superiormente, calcular los resultados.
//     }
//     catch(const ExcepcionMatriz& e)
//     {
//       std::cerr << "Ocurrió un error realizando la diagonalización superior de la matriz:" << std::endl
//                 << e.id() << " - " << e.mensaje() << std::endl;
//     }
//   }
// }

/**
 * Imprimir solucion
 * Realiza el cálculo de la solución final en función de la matriz diagonalizada.
 */
// template <class P>
// void GaussJordan<P>::imprimirSolucion()
// {
//   // Depende la bandera lo que realizamos.
//   switch (this->bandera_solucion)
//   {
//   case SOLUCION_NO_CALCULADA:
//     std::cout << "No se ha realizado la verificación de la solución." << std::endl;
//     break;
//   case SOLUCION_UNICA:
//     std::cout << "El sistema tiene solución única, en la próxima versión se calculan los resultados." << std::endl;
//     // TODO: Pues, mostrar las soluciones, primero Dios.
//     break;
//   case INFINIDAD_SOLUCIONES:
//     std::cout << "El sistema tiene una infinidad de soluciones." << std::endl;
//     break;
//   case SIN_SOLUCION:
//     std::cout << "El sistema no tiene solución." << std::endl;
//     break;
//   default:
//     std::cout << "La bandera de solución no tiene un valor reconocible." << std::endl;
//     break;
//   }
// }

// Especificamos los tipos de datos válidos.
template class GaussJordan<int>;   // Enteros.
template class GaussJordan<float>; // Números con punto flotante.
