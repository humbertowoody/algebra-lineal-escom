/**
 * Matriz.cpp
 * Implementación de la clase Matriz con operaciones básicas para trabajar con matrices así como control
 * de errores mediante excepciones con la clase ExcepcionMatriz.
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
 * Destructor
 * Función que se encarga de limpiar la memoria utilizada por la matriz.
 */
template <class P>
Matriz<P>::~Matriz()
{
  // Eliminamos todos los elementos en el vector.
  this->matriz_vector.clear();
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
 * Obtener diagonal principal
 * Obtiene un vector con los elementos presentes en la diagonal principal de la matriz.
 */
template <class P>
std::vector<P> Matriz<P>::obtenerDiagonalPrincipal()
{
  std::vector<P> resultado; // Vector con los elementos en la diagonal principal.

  // Iteramos sobre la diagonal principal.
  for (int pivote = 0; pivote < this->obtenerNumeroColumnas() && pivote < this->obtenerNumeroFilas(); pivote++)
  {
    // Añadimos el elemento en (pivote, pivote) al vector resultante.
    resultado.push_back(this->matriz_vector[pivote][pivote]);
  }

  // Regresamos el vector resultante.
  return resultado;
}

/**
 * Obtener diagonal secundaria
 * Obtiene un vector con los elementos presentes en la diagonal secundaria de la matriz.
 */
template <class P>
std::vector<P> Matriz<P>::obtenerDiagonalSecundaria()
{
  std::vector<P> resultado; // Vector con los elementos en la diagonal secundaria.

  // Iteramos sobre la diagonal secundaria.
  for (int fila = 0, columna = this->obtenerNumeroColumnas() - 1; fila < this->obtenerNumeroFilas() && columna >= 0; fila++, columna--)
  {
    // Añadimos el elemento en la coordenada actual a nuestro vector de resultados.
    resultado.push_back(this->obtenerElemento(fila, columna));
  }

  // Regresamos el vector resultante.
  return resultado;
}

/**
 * Obtener fila.
 * Obtiene una fila de la matriz.
 */
template <class P>
std::vector<P> Matriz<P>::obtenerFila(int indiceFila)
{
  // Verificamos el índice de la fila.
  if (!this->indiceFilaValido(indiceFila))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Regresamos la fila solicitada.
  return this->matriz_vector[indiceFila];
}

/**
 * Obtener columna.
 * Obtiene una columna de la matriz.
 */
template <class P>
std::vector<P> Matriz<P>::obtenerColumna(int indiceColumna)
{
  std::vector<P> columna; // El vector con los elementos para la columna solicitada.

  // Verificamos el índice de la columna.
  if (!this->indiceColumnaValido(indiceColumna))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_COLUMNA_INVALIDO);
  }

  // Iteramos en cada fila.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    columna.push_back(this->obtenerElemento(fila, indiceColumna));
  }

  // Regresamos el vector con el contenido de la columna.
  return columna;
}

/**
 * Asignar elemento
 * Asigna un valor al elemento en la posición i,j.
 */
template <class P>
Matriz<P> Matriz<P>::asignarElemento(int indiceFila, int indiceColumna, P elemento)
{
  // Verificamos el índice de la fila.
  if (!this->indiceFilaValido(indiceFila))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Verificamos el índice de la columna.
  if (!this->indiceColumnaValido(indiceColumna))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_COLUMNA_INVALIDO);
  }

  // Realizamos una copia del vector con la matriz.
  std::vector<std::vector<P>> matrizNueva = this->matriz_vector;

  // Asignamos el elemento.
  matrizNueva[indiceFila][indiceColumna] = elemento;

  // Regresamos la matriz nueva.
  return Matriz<P>(matrizNueva);
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
 * Eliminar Fila
 * Elimina una fila de nuestra matriz y regresa la matriz resultante.
 */
template <class P>
Matriz<P> Matriz<P>::eliminarFila(int indice_fila_a_eliminar)
{
  // Verificamos que el índice sea válido.
  if (!this->indiceFilaValido(indice_fila_a_eliminar))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Creamos el vector resultante.
  std::vector<std::vector<P>> matriz_sin_fila = this->matriz_vector;

  // Eliminamos la fila.
  matriz_sin_fila.erase(matriz_sin_fila.begin() + indice_fila_a_eliminar);

  // Regresamos la matriz resultante.
  return Matriz<P>(matriz_sin_fila);
}

/**
 * Insertar Columna
 * Función para insertar una columna en la matriz y regresar la matriz
 * resultante, si la columna en cuestión no es consistente se arrojará
 * una excepción.
 */
template <class P>
Matriz<P> Matriz<P>::insertarColumna(std::vector<P> nuevaColumna)
{
  // Verificamos que la columna sea consistente.
  if (!this->columnaConsistente(nuevaColumna))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_COLUMNA_INCONSISTENTE);
  }

  // Creamos la matriz resultante.
  std::vector<std::vector<P>> nueva_matriz = this->matriz_vector;

  // Verificamos si la matriz está vacía.
  if (this->obtenerNumeroFilas() > 0)
  {
    // La matriz no está vacía, insertamos cada elemento al final de cada fila.
    for (int fila = this->obtenerNumeroFilas() - 1; fila >= 0; fila--)
    {
      // Añadimos al final de la fila al último elemento en la nueva Columna.
      nueva_matriz[fila].push_back(nuevaColumna[fila]);
    }
  }
  else
  {
    // La matriz está vacía, insertamos cada elemento como una fila nueva.
    for (int indice = 0; indice < nuevaColumna.size(); indice++)
    {
      nueva_matriz.push_back({nuevaColumna[indice]});
    }
  }

  // Regresamos la matriz resultante.
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

  // Verificamos si quedaron filas vacías y las eliminamos de ser así.
  for (int fila = this->obtenerNumeroFilas() - 1; fila >= 0; fila--)
  {
    if (matriz_sin_columna[fila].empty())
    {
      matriz_sin_columna.pop_back();
    }
  }

  // Regresamos la matriz resultante.
  return Matriz<P>(matriz_sin_columna);
}

/**
 * Calcular traza de la matriz
 * La traza de la matriz es la suma de los elementos de la diagonal principal.
 */
template <class P>
P Matriz<P>::calcularTrazaDeLaMatriz()
{
  P resultado = 0; // Variable con el resultado.

  // Obtenemos y sumamos los elementos presentes en la diagonal principal.
  std::vector<P> diagonalPrincipal = this->obtenerDiagonalPrincipal();

  // Sumamos los elementos.
  for (int indice = 0; indice < diagonalPrincipal.size(); indice++)
  {
    resultado += diagonalPrincipal[indice];
  }

  // Regresamos la sumatoria.
  return resultado;
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
 * Diagonalización Inferior.
 * Realiza el proceso de diagonalización de una matriz para la parte inferior.
 */
template <class P>
Matriz<P> Matriz<P>::diagonalizacionInferior()
{
  // Variable para el resultado del proceso de diagonalización.
  Matriz<P> matriz_diagonalizada = Matriz<P>(this->matriz_vector);

  // Dado que la coordenada del pivote siempre será en diagonal, únicamente requerimos
  // una variable para manejar su posición y a partir de ahí realizamos las operaciones
  // para ir colocando ceros por debajo del mismo (cuando sea posible, si el pivote es 0
  // entonces tratamos de buscar una fila, por debajo del mismo, para intercambiar y
  // seguir con el algoritmo).
  for (int pivote = 0; pivote < this->obtenerNumeroFilas() && pivote < this->obtenerNumeroColumnas(); pivote++)
  {
    // Mostramos el proceso si la bandera debug está activada.
    if (DEBUG_MATRIZ)
    {
      std::cout << "Diagonalizando para el pivote en A_{" << pivote + 1 << "," << pivote + 1 << "}:" << std::endl;
      matriz_diagonalizada.imprimir();
      std::cout << std::endl;
    }

    // Hay que verificar que el pivote no sea 0 porque, bueno, ya sabemos ¿no?
    if (matriz_diagonalizada.obtenerElemento(pivote, pivote) == 0)
    {
      // Buscamos una fila en dónde, para la columna actual del pivote, el valor no
      // sea cero.
      for (int fila = pivote + 1; fila < matriz_diagonalizada.obtenerNumeroFilas(); fila++)
      {
        // Si encontramos una fila que no sea 0 y no hemos realizado el intercambio, intercambiamos.
        if (matriz_diagonalizada.obtenerElemento(fila, pivote) != 0 && matriz_diagonalizada.obtenerElemento(pivote, pivote) == 0)
        {
          // Realizamos el cambio de la fila.
          matriz_diagonalizada = matriz_diagonalizada.intercambiarFilas(pivote, fila);
        }
      }
    }

    // Si, a pesar de nuestro intento, no pudimos encontrar una fila con un valor distinto a 0
    // en la columna de nuestro pivote, omitimos el resto del proceso para este pivote. En otro
    // caso, procedemos con el algoritmo para hacer 1's la diagonal y 0's por debajo.
    if (matriz_diagonalizada.obtenerElemento(pivote, pivote) != 0)
    {
      // Para hacer 1 el pivote, dividimos cada elemento de la fila entre 1/pivote.
      P factor1 = 1 / matriz_diagonalizada.obtenerElemento(pivote, pivote);
      for (int columna = pivote; columna < matriz_diagonalizada.obtenerNumeroColumnas(); columna++)
      {
        matriz_diagonalizada = matriz_diagonalizada.asignarElemento(pivote, columna, (P)(factor1 * matriz_diagonalizada.obtenerElemento(pivote, columna)));
      }

      // Ahora tenemos que hacer ceros por debajo del pivote.
      for (int fila = pivote + 1; fila < matriz_diagonalizada.obtenerNumeroFilas(); fila++)
      {
        // Calculamos el factor de multiplicacion para que la columna pivote sea 0.
        P factor2 = matriz_diagonalizada.obtenerElemento(fila, pivote) * -1;

        // Realizamos la operación: factor(elemento de fila_1) + elemento de fila_2.
        for (int columna = pivote; columna < matriz_diagonalizada.obtenerNumeroColumnas(); columna++)
        {
          // Hacemos un casting porque si llega a realizarse una operación inválida, es preferible un valor "casteado" (forzado) a un NaN.
          matriz_diagonalizada = matriz_diagonalizada.asignarElemento(fila, columna, (P)(factor2 * matriz_diagonalizada.obtenerElemento(pivote, columna)) + matriz_diagonalizada.obtenerElemento(fila, columna));
        }
      }
    }
  }

  // Mostramos el resultado de la diagonalización si la bandera debug está activada.
  if (DEBUG_MATRIZ)
  {
    std::cout << "Diagonalización inferior:" << std::endl;
    matriz_diagonalizada.imprimir();
    std::cout << std::endl;
  }

  // Regresamos la matriz diagonalizada.
  return matriz_diagonalizada;
}

/**
 * Diagonalización superior
 * Realiza el proceso de diagonalización de una matriz para la parte superior.
 */
template <class P>
Matriz<P> Matriz<P>::diagonalizacionSuperior()
{
  Matriz<P> matriz_diagonalizada = Matriz<P>(this->matriz_vector); // Variable para el resultado de la diagonalización.

  // Ahora intentamos realizar la diagonalización superior, para esto, lo primero será encontrar el primer pivote
  // con valor válido (1).
  int pivoteInicial;
  for (pivoteInicial = 0; pivoteInicial < matriz_diagonalizada.obtenerNumeroFilas() && pivoteInicial < matriz_diagonalizada.obtenerNumeroColumnas() && matriz_diagonalizada.obtenerElemento(pivoteInicial, pivoteInicial) == 1; pivoteInicial++)
    ;
  pivoteInicial -= 1;

  // Mostramos la coordenada inicial de nuestro pivote si la bandera debug está activada.
  if (DEBUG_MATRIZ)
  {
    std::cout << "Pivote inicial de diagonalización superior: " << pivoteInicial << std::endl;
  }

  // Ciclo que recorre todos los pivotes a partir del pivote inicial calculado para ir haciendo
  // ceros por encima de la diagonal. Descartamos el elemento A_{1,1} porque no tiene elementos
  // encima.
  for (int pivote = pivoteInicial; pivote > 0; pivote--)
  {
    // Mostramos el proceso de diagonalización superior si la bandera debug está activada.
    if (DEBUG_MATRIZ)
    {
      std::cout << "Diagonalizando para el pivote en A*_{" << pivote + 1 << pivote + 1 << "}:" << std::endl;
      matriz_diagonalizada.imprimir();
      std::cout << std::endl;
    }

    // Tratamos de hacer todas las filas sobre el pivote 0.
    for (int fila = 0; fila < pivote; fila++)
    {
      // Calculamos el factor que se aplicará a toda la fila.
      P factor = matriz_diagonalizada.obtenerElemento(fila, pivote) * -1;

      // Aplicamos la operación a toda la fila.
      for (int columna = pivote; columna < matriz_diagonalizada.obtenerNumeroColumnas(); columna++)
      {
        matriz_diagonalizada = matriz_diagonalizada.asignarElemento(fila, columna, (P)(factor * matriz_diagonalizada.obtenerElemento(pivote, columna)) + matriz_diagonalizada.obtenerElemento(fila, columna));
      }
    }
  }

  // Mostramos la diagonalización completa de la matriz extendida.
  if (DEBUG_MATRIZ)
  {
    std::cout << "Diagonalización completa final:" << std::endl;
    matriz_diagonalizada.imprimir();
    std::cout << std::endl;
  }

  // Regresamos la matriz diagonalizada.
  return matriz_diagonalizada;
}

/**
 * Sumar
 * Realiza la suma de dos matrices, en caso de que las matrices no tengan las mismas dimensiones
 * se arrojará una excepción.
 */
template <class P>
Matriz<P> Matriz<P>::sumar(Matriz<P> sumando)
{
  // Verificamos las dimensiones.
  if ((this->obtenerNumeroColumnas() != sumando.obtenerNumeroColumnas()) || (this->obtenerNumeroFilas() != sumando.obtenerNumeroFilas()))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_DIMENSIONES_SUMA);
  }

  // Variable para el resultado de la suma.
  std::vector<std::vector<P>> resultado_suma = this->matriz_vector;

  // Iteramos las filas.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Iteramos las columnas.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Realizamos la operación.
      resultado_suma[fila][columna] = this->obtenerElemento(fila, columna) + sumando.obtenerElemento(fila, columna);
    }
  }

  // Regresamos la matriz con el resultado.
  return Matriz<P>(resultado_suma);
}

/**
 * Suma
 * Realiza la suma de la matriz actual con un escalar.
 */
template <class P>
Matriz<P> Matriz<P>::sumar(P escalar)
{
  // Variable para el resultado.
  std::vector<std::vector<P>> resultado_suma = this->matriz_vector;

  // Iteramos las filas.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Iteramos las columnas.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Realizamos la operación.
      resultado_suma[fila][columna] = this->obtenerElemento(fila, columna) + escalar;
    }
  }

  // Regresamos la matriz con el resultado.
  return Matriz<P>(resultado_suma);
}

/**
 * Restar
 * Realiza la resta de dos matrices, en caso de que las matrices no tengan las mismas dimensiones
 * se arrojará una excepción.
 */
template <class P>
Matriz<P> Matriz<P>::restar(Matriz<P> restando)
{
  // Verificamos las dimensiones.
  if ((this->obtenerNumeroColumnas() != restando.obtenerNumeroColumnas()) || (this->obtenerNumeroFilas() != restando.obtenerNumeroFilas()))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_DIMENSIONES_RESTA);
  }

  // Variable para el resultado de la resta.
  std::vector<std::vector<P>> resultado_resta = this->matriz_vector;

  // Iteramos las filas.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Iteramos las columnas.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Realizamos la operación.
      resultado_resta[fila][columna] = this->obtenerElemento(fila, columna) - restando.obtenerElemento(fila, columna);
    }
  }

  // Regresamos la matriz con el resultado.
  return Matriz<P>(resultado_resta);
}

/**
 * Resta
 * Realiza la resta de la matriz actual con un escalar.
 */
template <class P>
Matriz<P> Matriz<P>::restar(P escalar)
{
  // Variable para el resultado.
  std::vector<std::vector<P>> resultado_resta = this->matriz_vector;

  // Iteramos las filas.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Iteramos las columnas.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Realizamos la operación.
      resultado_resta[fila][columna] = this->obtenerElemento(fila, columna) - escalar;
    }
  }

  // Regresamos la matriz con el resultado.
  return Matriz<P>(resultado_resta);
}

// Matriz multiplicarFilaPorEscalar(int, P); // Multiplica una fila por un escalar.
/**
 * Multiplicar fila por escalar
 * Realiza la operación de multiplicación para cada elemento de una fila de la matriz
 * por un escalar.
 */
template <class P>
Matriz<P> Matriz<P>::multiplicarFilaPorEscalar(int indiceFila, P escalar)
{
  // Verificamos que el índice de la fila sea válido.
  if (!this->indiceFilaValido(indiceFila))
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_INDICE_FILA_INVALIDO);
  }

  // Variable para el resultado.
  std::vector<std::vector<P>> resultado = this->matriz_vector;

  // Iteramos sobre la fila y aplicamos la operación.
  for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
  {
    resultado[indiceFila][columna] *= escalar;
  }

  // Regresamos la matriz con el resultado.
  return Matriz<P>(resultado);
}

/**
 * Multiplicar
 * Realiza la operación de multiplicación entre matrices, en caso de que las
 * dimensiones de las matrices no sean compatibles para la operación, se arrojará
 * una excepción.
 */
template <class P>
Matriz<P> Matriz<P>::multiplicar(Matriz<P> matrizMultiplicando)
{
  // Verificamos que las dimensiones sean válidas.
  if (this->obtenerNumeroColumnas() != matrizMultiplicando.obtenerNumeroFilas())
  {
    throw ExcepcionMatriz(ERROR_MATRIZ_DIMENSIONES_MULTIPLICACION);
  }

  // Variable para el resultado.
  std::vector<std::vector<P>> resultado_multiplicacion;

  // Iteramos para cada fila de la matriz A.
  for (int filaMatrizA = 0; filaMatrizA < this->obtenerNumeroFilas(); filaMatrizA++)
  {
    // Añadimos un vector para los elementos resultado de la fila.
    resultado_multiplicacion.push_back({});

    // Iteramos sobre cada columna de la matriz B.
    for (int columnaMatrizB = 0; columnaMatrizB < matrizMultiplicando.obtenerNumeroColumnas(); columnaMatrizB++)
    {
      // Variable para almacenar la sumatoria.
      P resultado = 0;

      // Iteramos sobre cada elemento en la fila de la matriz A y cada elemento en la columna de la matriz B.
      for (int indiceElemento = 0; indiceElemento < this->obtenerNumeroColumnas(); indiceElemento++)
      {
        resultado += this->matriz_vector[filaMatrizA][indiceElemento] * matrizMultiplicando.obtenerElemento(indiceElemento, columnaMatrizB);
      }

      // Añadimos el resultado a nuestra fila actual.
      resultado_multiplicacion.back().push_back(resultado);
    }
  }

  // Regresamos la matriz resultante.
  return Matriz<P>(resultado_multiplicacion);
}

/**
 * Multiplicar
 * Realiza la operación de multiplicación de cada elemento de la matriz por
 * un escalar.
 */
template <class P>
Matriz<P> Matriz<P>::multiplicar(P escalar)
{
  // Variable para el resultado.
  std::vector<std::vector<P>> resultado = this->matriz_vector;

  // Iteramos sobre cada fila de la matriz.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Iteramos sobre cada columna de la fila.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      resultado[fila][columna] *= escalar;
    }
  }

  // Regresamos la matriz con el resultado.
  return Matriz<P>(resultado);
}

// Matriz transposicion();                   // Cálculo de la matriz transpuesta.

/**
 * Es Matriz Nula
 * Una matriz nula es aquella en la que todos sus elementos son cero.
 */
template <class P>
bool Matriz<P>::esMatrizNula()
{
  // Iteramos en los elementos de la matriz.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Si un elemento es distinto a cero, entonces no es matriz nula.
      if (this->matriz_vector[fila][columna] != 0)
      {
        return false;
      }
    }
  }

  // Si todos los elementos son cero, es una matriz nula.
  return true;
}

/**
 * Es Matriz Fila
 * Una matriz es llamada matriz fila si únicamente está conformada por una fila.
 */
template <class P>
bool Matriz<P>::esMatrizFila()
{
  // La matriz fila consta de una sola fila.
  return this->obtenerNumeroFilas() == 1;
}

/**
 * Es Matriz Columna
 * Una matriz es llamada matriz columna si únicamente está conformada por una columna.
 */
template <class P>
bool Matriz<P>::esMatrizColumna()
{
  // La matriz columna consta de una sola columna.
  return this->obtenerNumeroColumnas() == 1;
}

/**
 * Es Matriz Cuadrada
 * Una matriz es llamada matriz cuadrada si su número de filas es igual al número de columnas.
 */
template <class P>
bool Matriz<P>::esMatrizCuadrada()
{
  // La matriz cuadrada consta del mismo número de filas y columnas, además la matriz no debe estar vacía.
  return this->obtenerNumeroColumnas() == this->obtenerNumeroFilas() && this->obtenerNumeroFilas() != 0;
}

/**
 * Es Matriz Rectangular
 * Una matriz es llamada matriz rectangular si su número de filas y columnas es distinto.
 */
template <class P>
bool Matriz<P>::esMatrizRectangular()
{
  // Una matriz rectangular tiene un distinto número de filas y de columnas.
  return this->obtenerNumeroColumnas() != this->obtenerNumeroFilas();
}

/**
 * Es Matriz Triangular Superior
 * Una matriz es llamada matriz triangular superior si todos los elementos por debajo de
 * la diagonal principal son nulos.
 */
template <class P>
bool Matriz<P>::esMatrizTriangularSuperior()
{
  // Iteramos en la diagonal principal.
  for (int pivote = 0; pivote < this->obtenerNumeroFilas() && pivote < this->obtenerNumeroColumnas(); pivote++)
  {
    // Iteramos sobre los elementos por debajo del pivote.
    for (int fila = pivote + 1; fila < this->obtenerNumeroFilas(); fila++)
    {
      // Si algún elemento no es igual a 0 en la coordenada [fila][pivote], entonces no es triangular superior.
      if (this->matriz_vector[fila][pivote] != 0)
      {
        return false;
      }
    }
  }

  // Si todos los elementos por debajo del pivote fueron 0, entonces es matriz triangular superior.
  return true;
}

/**
 * Es Matriz Triangular Inferior
 * Una matriz es llamada matriz triangular inferior si todos los elementos por encima de
 * la diagonal principal son nulos.
 */
template <class P>
bool Matriz<P>::esMatrizTriangularInferior()
{
  // Iteramos en la diagonal principal.
  for (int pivote = 0; pivote < this->obtenerNumeroFilas() && pivote < this->obtenerNumeroColumnas(); pivote++)
  {
    // Iteramos sobre los elementos por encima del pivote.
    for (int fila = pivote - 1; fila >= 0; fila--)
    {
      // Si algún elemento no es igual a 0 en la coordenada [fila][pivote], entonces no es triangular inferior.
      if (this->matriz_vector[fila][pivote] != 0)
      {
        return false;
      }
    }
  }

  // Si todos los elementos por encima del pivote fueron 0, entonces es matriz triangular inferior.
  return true;
}

/**
 * Es Matriz Diagonal
 * Es una matriz que es, al mismo tiempo, triangular superior y triangular inferior.
 */
template <class P>
bool Matriz<P>::esMatrizDiagonal()
{
  // Si es diagonal superior e inferior, entonces es una matriz diagonal.
  return this->esMatrizTriangularInferior() && this->esMatrizTriangularSuperior();
}

/**
 * Es Matriz Identidad
 * Una matriz es llamada matriz identidad si es una matriz diagonal, y los elementos en su diagonal
 * principal solo son unos.
 */
template <class P>
bool Matriz<P>::esMatrizIdentidad()
{
  // Verificamos si es una matriz diagonal.
  if (!this->esMatrizDiagonal())
  {
    // Si no es matriz diagonal, no puede ser matriz identidad.
    return false;
  }

  // Iteramos sobre la diagonal principal.
  for (int pivote = 0; pivote < this->obtenerNumeroColumnas() && pivote < this->obtenerNumeroFilas(); pivote++)
  {
    // Verificamos si el elemento en el pivote es distinto a 1.
    if (this->matriz_vector[pivote][pivote] != 1)
    {
      return false;
    }
  }

  // Si todos los elementos en la diagonal principal fueron unos, es una matriz identidad.
  return true;
}

/**
 * Es Igual
 * Verifica si dos matrices son iguales.
 */
template <class P>
bool Matriz<P>::esIgual(Matriz<P> matrizAComparar)
{
  // Verificamos que las dimensiones de ambas matrices sean iguales.
  if ((this->obtenerNumeroColumnas() != matrizAComparar.obtenerNumeroColumnas()) || (this->obtenerNumeroFilas() != matrizAComparar.obtenerNumeroFilas()))
  {
    // Si alguna dimensión no es igual, no pueden ser iguales.
    return false;
  }

  // Iteramos sobre todas las filas.
  for (int fila = 0; fila < this->obtenerNumeroFilas(); fila++)
  {
    // Iteramos sobre todas las columnas.
    for (int columna = 0; columna < this->obtenerNumeroColumnas(); columna++)
    {
      // Verificamos que los elementos entre matrices coincidan en la coordenada actual.
      if (this->matriz_vector[fila][columna] != matrizAComparar.obtenerElemento(fila, columna))
      {
        // Si los elementos en la coordenada actual no son iguales, las matrices no son iguales.
        return false;
      }
    }
  }

  // Si las dimensiones son iguales, y los elementos son iguales, las matrices son iguales.
  return true;
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
 * Columna consistente.
 * Verifica si una columna es consistente con la matriz actual.
 */
template <class P>
bool Matriz<P>::columnaConsistente(std::vector<P> columna_a_verificar)
{
  // Verificamos si la matriz contiene filas.
  if (this->obtenerNumeroFilas() > 0)
  {
    // Verificamos si el número de elementos presentes en la columna a verificar es igual
    // al número de filas presentes en la matriz.
    if (this->obtenerNumeroFilas() == columna_a_verificar.size())
    {
      // Son del mismo tamaño.
      return true;
    }
    else
    {
      // Son de tamaños distintos.
      return false;
    }
  }

  // No hay filas, por lo que es irrelevante el tamaño de la columna.
  return true;
}

/**
 * Funciones del namespace.
 * En esta sección se incluyen las implementaciones de las funciones que se tienen en
 * el namespace "Matrices", ajenas a la clase "Matriz".
 */

// Especificamos los tipos de datos válidos.
template class Matriz<int>;    // Enteros.
template class Matriz<float>;  // Números de punto flotante.
template class Matriz<double>; // Números de punto flotante con más precisión.
