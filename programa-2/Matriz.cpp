/**
 * Matriz.cpp
 * Implementación de la clase Matriz con operaciones básicas para trabajar con matrices así como control
 * de errores mediante excepciones con la clase ExcepcionMatriz.
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
#include <iomanip>
#include <cmath>
#include "Matriz.hpp"
#include "ExcepcionMatriz.hpp"

/**
 * Funciones elementales.
 * En esta sección se incluyen las implementaciones de las funciones elementales para
 * la clase Matriz, es decir, constructores y desctructores.
 */

/**
 * Constructor base.
 * Permite crear Matrices sin ningún parámetro.
 */
template <class P>
Matriz<P>::Matriz()
{
  // Limpiamos la matriz.
  this->matriz_vector.clear();
}

/**
 * Constructor de copia.
 * Realiza la copia de un objeto Matriz.
 */
template <class P>
Matriz<P>::Matriz(const Matriz<P> &matriz_nueva)
{
  this->matriz_vector = matriz_nueva.matriz_vector;
}

/**
 * Constructor a partir de un vector de vectores.
 * Permite crear Matrices a partir de un vector con vectores pre-existente.
 * Para mantener la consistencia de la matriz, únicamente se insertarán las
 * filas que tengan el mismo número de elementos que la primer fila.
 */
template <class P>
Matriz<P>::Matriz(std::vector<std::vector<P>> nueva_matriz_vectores)
{
  // Limpiamos la matriz.
  this->matriz_vector.clear();

  // Revisamos si la nueva matriz tiene filas.
  if (nueva_matriz_vectores.size() > 0)
  {
    // Añadimos la primer fila "tal cual".
    this->matriz_vector.push_back(nueva_matriz_vectores[0]);

    // Añadimos las filas subsecuentes que sean "consistentes" con la primer fila,
    // es decir, las que tengan el mismo tamaño.
    for (int fila_actual = 1; fila_actual < nueva_matriz_vectores.size(); fila_actual++)
    {
      if (this->filaConsistente(nueva_matriz_vectores[fila_actual]))
      {
        this->matriz_vector.push_back(nueva_matriz_vectores[fila_actual]);
      }
    }
  }
}

/**
 * Funciones públicas.
 * A partir de este punto, se incluye la implementación de las funciones públicas
 * de la clase Matriz.
 */

/**
 * Obtener Elemento
 * Regresa el elemento en la posición {i,j} para la matriz actual.
 */
template <class P>
P Matriz<P>::obtenerElemento(int indiceFila, int indiceColumna)
{
  // Validar el índice de la fila.
  if (!this->indiceFilaValido(indiceFila))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Validar el índice de la columna.
  if (!this->indiceColumnaValido(indiceColumna))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_COLUMNA_INVALIDO);
  }

  // Regresar el elemento.
  return this->matriz_vector[indiceFila][indiceColumna];
}

/**
 * Obtener Numero de Filas
 * Esta función devuelve un entero con el número de filas disponibles en
 * la matriz actual.
 */
template <class P>
int Matriz<P>::obtenerNumeroFilas()
{
  // El tamaño del primer vector es el número de filas.
  return this->matriz_vector.size();
}

/**
 * Obtener Numero de Columnas
 * Esta función devuelve un entero con el número de columnas disponibles
 * en la matriz actual.
 */
template <class P>
int Matriz<P>::obtenerNumeroColumnas()
{
  // Verificamos que exista, al menos, una fila.
  if (this->obtenerNumeroFilas() > 0)
  {
    // Asumimos que todas las filas tendrán el mismo número de elementos.
    return this->matriz_vector[0].size();
  }

  // Si el número de filas fue 0, regresamos 0.
  return 0;
}

/**
 * Obtener Rango
 * Calcula el rango de la matriz en cuestión.
 * El rango se define como: El número de filas tales que existe un valor distinto
 * a cero posteriormente a la diagonalización.
 * La verificación de que la matriz sea una diagonalizada queda a criterio de la implementación.
 */
template <class P>
int Matriz<P>::obtenerRango()
{
  // Variables locales de la función.
  int rango = 0;                   // Asumimos que el rango es 0.
  bool filaConValorDiferenteACero; // Para llevar el control de lo que vayamos encontrado.

  // Recorremos la matriz.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Asumimos que la fila no tiene valores distintos a 0.
    filaConValorDiferenteACero = false;

    // Recorremos los elementos de la fila para verificar si hay algún valor distinto a 0.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Revisamos si el valor es distinto a 0.
      if (this->matriz_vector[fila][columna] != 0)
      {
        // ¡Encontramos un valor distinto a 0!
        filaConValorDiferenteACero = true; // Marcamos la bandera.
        break;                             // No necesitamos seguir iterando para esta fila.
      }
    }

    // Verificamos si nuestra bandera cambió de estado.
    if (filaConValorDiferenteACero)
    {
      rango += 1; // Encontramos una fila con valor distinto a 0, sumamos 1 a nuestro contador.
    }
  }

  // Regresamos el rango que se haya calculado.
  return rango;
}

/**
 * Insertar Fila
 * Función que permite insertar una nueva fila en la matriz, si la fila
 * no es consistente con las filas ya existentes en la matriz, es decir,
 * que la fila no tiene el mismo número de elementos, se arrojará una
 * excepción.
 */
template <class P>
Matriz<P> Matriz<P>::insertarFila(std::vector<P> nueva_fila)
{
  // Validar la fila.
  if (!this->filaConsistente(nueva_fila))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_FILA_INCONSISTENTE);
  }

  // Copiamos nuestra matriz actual.
  std::vector<std::vector<P>> nueva_matriz = this->matriz_vector;

  // Insertamos la fila en la nueva matriz.
  nueva_matriz.push_back(nueva_fila);

  // Regresamos la nueva matriz con la fila.
  return Matriz<P>(nueva_matriz);
}

/**
 * Eliminar Columna
 * Elimina una columna de nuestra matriz y regresa la matriz resultante.
 */
template <class P>
Matriz<P> Matriz<P>::eliminarColumna(int indice_columna_a_eliminar)
{
  // Verificamos que el índice sea válido.
  if (!this->indiceColumnaValido(indice_columna_a_eliminar))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_COLUMNA_INVALIDO);
  }

  // Creamos el vector resultante.
  std::vector<std::vector<P>> matriz_sin_columna = this->matriz_vector;

  // El número de filas no ha cambiado, iteramos sobre todas y eliminamos el
  // elemento en el índice proporcionado.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Eliminamos el elemento en el índice.
    matriz_sin_columna[fila].erase(matriz_sin_columna[fila].begin() + indice_columna_a_eliminar);
  }

  // Regresamos la matriz resultante.
  return Matriz<P>(matriz_sin_columna);
}

/**
 * Intercambiar Filas.
 * Función que realiza el intercambio de dos filas dentro de la matriz.
 */
template <class P>
Matriz<P> Matriz<P>::intercambiarFilas(int fila_a, int fila_b)
{
  // Verificar el índice para las filas.
  if (!this->indiceFilaValido(fila_a) || !this->indiceFilaValido(fila_b))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Verificar que fila_a <> fila_b
  if (fila_a == fila_b)
  {
    return *this;
  }

  // Creamos una copia de nuestro vector de vectores.
  std::vector<std::vector<P>> nueva_matriz = this->matriz_vector;

  // Realizamos el intercambio de las filas.
  nueva_matriz[fila_a].swap(nueva_matriz[fila_b]);

  // Regresamos una nueva matriz con las filas intercambiadas.
  return Matriz<P>(nueva_matriz);
}

/**
 * Diagonalización Inferior
 * Realiza la diagonalización inferior de la matriz.
 */
template <class P>
Matriz<P> Matriz<P>::diagonalizacionInferior()
{
  // Creamos el vector de vectores con los resultados.
  std::vector<std::vector<P>> matriz_diagonalizada = this->matriz_vector;

  // Dado que la coordenada del pivote siempre será en diagonal, únicamente requerimos
  // una variable para manejar su posición y a partir de ahí realizamos las operaciones
  // para ir colocando ceros por debajo del mismo (cuando sea posible, si el pivote es 0
  // entonces tratamos de buscar una fila, por debajo del mismo, para intercambiar y
  // seguir con el algoritmo).
  for (int pivote = 0; pivote < this->obtenerNumeroFilas(); pivote++)
  {
    // Mostramos el proceso.
    std::cout << "Diagonalizando para el pivote en a_{" << pivote + 1 << "," << pivote + 1 << "}:" << std::endl;
    Matriz<P> temp = Matriz<P>(matriz_diagonalizada);
    temp.imprimir();

    // Hay que verificar que el pivote no sea 0 porque, bueno, ya sabemos ¿no?
    if (matriz_diagonalizada[pivote][pivote] == 0)
    {
      // Buscamos una fila en dónde, para la columna actual del pivote, el valor no
      // sea cero.
      for (int fila = pivote + 1; fila < this->obtenerNumeroFilas(); fila++)
      {
        // Si encontramos una fila que no sea 0 y no hemos realizado el intercambio, intercambiamos.
        if (matriz_diagonalizada[fila][pivote] != 0 && matriz_diagonalizada[pivote][pivote] == 0)
        {
          // La clase std::vector incluye un cómodo swap.
          matriz_diagonalizada[pivote].swap(matriz_diagonalizada[fila]);
        }
      }
    }

    // Si, a pesar de nuestro intento, no pudimos encontrar una fila con un valor distinto a 0
    // en la columna de nuestro pivote, omitimos el resto del proceso para este pivote. En otro
    // caso, procedemos con el algoritmo para hacer 1's la diagonal y 0's por debajo.
    if (matriz_diagonalizada[pivote][pivote] != 0)
    {
      // Para hacer 1 el pivote, dividimos cada elemento de la fila entre 1/pivote.
      P factor = 1 / matriz_diagonalizada[pivote][pivote];
      for (int columna = pivote; columna < this->obtenerNumeroColumnas(); columna++)
      {
        matriz_diagonalizada[pivote][columna] = factor * matriz_diagonalizada[pivote][columna];
      }

      // Ahora tenemos que hacer ceros por debajo del pivote.
      for (int fila = pivote + 1; fila < this->obtenerNumeroFilas(); fila++)
      {
        // Calculamos el factor de multiplicacion para que la columna pivote sea 0.
        P factor = matriz_diagonalizada[fila][pivote] * -1;

        // Realizamos la operación: factor(elemento de fila_1) + elemento de fila_2.
        for (int columna = pivote; columna < this->obtenerNumeroColumnas(); columna++)
        {
          // Hacemos un casting porque si llega a realizarse una operación inválida, es preferible un valor "casteado" (forzado) a un NaN.
          matriz_diagonalizada[fila][columna] = (P)(factor * matriz_diagonalizada[pivote][columna]) + matriz_diagonalizada[fila][columna];
        }
      }
    }
  }

  // Regresamos una nueva matriz con los valores obtenidos.
  return Matriz<P>(matriz_diagonalizada);
}

/**
 * Imprimir
 * Función que imprime una matriz en su totalidad.
 */
template <class P>
void Matriz<P>::imprimir()
{
  // Imprimimos la matriz en su totalidad.
  this->imprimirEnRango(this->obtenerNumeroFilas(), this->obtenerNumeroColumnas());
}

/**
 * Funciones privadas.
 * En esta sección se incluye la implementación de las funciones privadas
 * de la clase Matriz.
 */

/**
 * Fila Válida
 * Determina si el índice proporcionado para una fila es válido en el contexto
 * de la matriz actual.
 */
template <class P>
bool Matriz<P>::indiceFilaValido(int indice_fila)
{
  // Entre 0 y el máximo número de filas.
  return indice_fila >= 0 && indice_fila < this->obtenerNumeroFilas();
}

/**
 * Columna Válida
 * Determina si el índice proporcionado para una columna es válido en el contexto
 * de la matriz actual.
 */
template <class P>
bool Matriz<P>::indiceColumnaValido(int indice_columna)
{
  // Entre 0 y el máximo número de columnas.
  return indice_columna >= 0 && indice_columna < this->obtenerNumeroColumnas();
}

/**
 * Imprimir en Rango
 * Permite imprimir un número variables de filas y columnas para una matriz.
 */
template <class P>
void Matriz<P>::imprimirEnRango(int fila_final, int columna_final)
{
  // Validamos la fila_final.
  if (fila_final != 0 && !this->indiceFilaValido(fila_final - 1))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Validamos la columna final.
  if (columna_final != 0 && !this->indiceColumnaValido(columna_final - 1))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_COLUMNA_INVALIDO);
  }

  // Recorremos todas las filas.
  for (int fila_actual = 0; fila_actual < fila_final; fila_actual++)
  {
    // Caracter inicial para cada fila.
    std::cout << "[ ";

    // Recorremos todas las columnas de la fila.
    for (int columna_actual = 0; columna_actual < columna_final; columna_actual++)
    {
      // Imprimimos el valor.
      std::cout << std::setw(CARACTERES_RESERVADOS_MATRIZ) << this->matriz_vector[fila_actual][columna_actual] << std::setw(1);

      // Revisamos si es la última columna.
      if ((columna_actual + 1) < columna_final)
      {
        std::cout << " ";
      }
    }

    // Caracter final y salto de linea.
    std::cout << " ]" << std::endl;
  }
}

/**
 * Fila Consistente
 * Función que verifica si una fila es consistente con la matriz en cuestión.
 */
template <class P>
bool Matriz<P>::filaConsistente(std::vector<P> fila_a_verificar)
{
  // Verificamos si la matriz contiene filas.
  if (this->obtenerNumeroFilas() > 0)
  {
    // Asumimos que el tamaño de todas las filas será igual.
    if (this->matriz_vector[0].size() != fila_a_verificar.size())
    {
      // No son del mismo tamaño.
      return false;
    }
    else
    {
      // Tienen el mismo tamaño.
      return true;
    }
  }

  // No hay filas, por lo que es irrelevante el tamaño de la fila.
  return true;
}

/**
 * Funciones del namespace.
 * En esta sección se incluyen las implementaciones de las funciones que se tienen en
 * el namespace "Matrices", ajenas a la clase "Matriz".
 */

// Especificamos los tipos de datos válidos.
template class Matriz<int>;   // Enteros.
template class Matriz<float>; // Números de punto flotante.