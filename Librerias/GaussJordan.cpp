/**
 * GaussJordan.cpp
 * Implementación de la clase GaussJordan para resolver sistemas de ecuaciones lineales utilizando
 * matrices.
 */
#include <iostream>
#include "GaussJordan.hpp"
#include "ExcepcionGaussJordan.hpp"

/**
 * Constructor Gauss Jordan base.
 * Recibe la matriz extendida original y realiza el procedimiento Gauss-Jordan
 * para solucionar el sistema de ecuaciones.
 */
template <class P>
GaussJordan<P>::GaussJordan(Matriz<P> matriz_extendida_inicial)
{
  // Verificamos que la matriz extendida inicial cumpla con las dimensiones mínimas de
  // un sistema de ecuaciones lineales válido.
  if (matriz_extendida_inicial.obtenerNumeroColumnas() < MIN_VARIABLES || matriz_extendida_inicial.obtenerNumeroFilas() < MIN_ECUACIONES)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_DIMENSIONES_MATRIZ);
  }

  // Asignamos las variables iniciales.
  this->matriz_extendida = matriz_extendida_inicial;

  // Realizamos el procedimiento Gauss-Jordan.
  this->resolver();
}

/**
 * Destructor de la clase Gauss Jordan.
 * Limpia la memoria para todos los objetos y variables instanciadas.
 */
template <class P>
GaussJordan<P>::~GaussJordan()
{
  // Limpiamos cualquier dato que pueda permanecer en memoria.
  this->bandera_solucion = SOLUCION_NO_CALCULADA;
}

/**
 * Funciones públicas.
 */

/**
 * Obtener Tipo De Solución
 * Regresa un entero representando las siguientes constantes:
 * - SIN_SOLUCION
 * - SOLUCION_UNICA
 * - INFINIDAD_SOLUCIONES
 */
template <class P>
int GaussJordan<P>::obtenerTipoDeSolucion()
{
  return this->bandera_solucion;
}

/**
 * Obtener Matriz Extendida Original
 * Regresa la matriz extendida original que fue proporcionada al instanciar
 * la clase.
 */
template <class P>
Matriz<P> GaussJordan<P>::obtenerMatrizExtendidaOriginal()
{
  return this->matriz_extendida;
}

/**
 * Obtener Matriz Extendida Diagonalizada
 * Regresa la matriz extendida diagonalizada.
 */
template <class P>
Matriz<P> GaussJordan<P>::obtenerMatrizExtendidaDiagonalizada()
{
  return this->matriz_extendida_diagonalizada;
}

/**
 * Obtener Matriz de Coeficientes Original
 * Regresa la matriz de coeficientes original que fue proporcionada al instanciar
 * la clase.
 */
template <class P>
Matriz<P> GaussJordan<P>::obtenerMatrizDeCoeficientesOriginal()
{
  return this->matriz_extendida.eliminarColumna(this->matriz_extendida.obtenerNumeroColumnas() - 1);
}

/**
 * Obtener Matriz de Coeficientes Diagonalizada
 * Regresa la matriz de coeficientes diagonalizada.
 */
template <class P>
Matriz<P> GaussJordan<P>::obtenerMatrizDeCoeficientesDiagonalizada()
{
  return this->matriz_extendida_diagonalizada.eliminarColumna(this->matriz_extendida_diagonalizada.obtenerNumeroColumnas() - 1);
}

/**
 * Obtener Número de Variables
 * Regresa el número de variables para la matriz proporcionada.
 */
template <class P>
int GaussJordan<P>::obtenerNumeroVariables()
{
  return (this->matriz_extendida.obtenerNumeroColumnas() - 1);
}

/**
 * Obtener Número de Ecuaciones
 * Regresa el número de ecuaciones para la matriz extendida proporcionada
 * al instanciar la clase que representa un sistema de ecuaciones lineales.
 */
template <class P>
int GaussJordan<P>::obtenerNumeroEcuaciones()
{
  return this->matriz_extendida.obtenerNumeroFilas();
}

/**
 * Obtener Soluciones Únicas
 * Regrea un vector con las soluciones para cada variable correspondiente
 * al sistema de ecuaciones lineales planteado. En caso de que el sistema
 * no tenga solución única, se arrojará una excepción.
 */
template <class P>
std::vector<P> GaussJordan<P>::obtenerSolucionesUnicas()
{
  // Verificamos que el sistema tenga solución única.
  if (this->bandera_solucion != SOLUCION_UNICA)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_SOLUCION_UNICA_INEXISTENTE);
  }

  // Creamos el vector con las soluciones.
  std::vector<P> soluciones;

  // Iteramos sobre cada fila en la que el pivote fue 1 y guardamos el resultado.
  for (int pivote = 0; pivote < (this->matriz_extendida_diagonalizada.obtenerNumeroColumnas() - 1) && pivote < this->matriz_extendida_diagonalizada.obtenerNumeroFilas() && this->matriz_extendida_diagonalizada.obtenerElemento(pivote, pivote) == 1; pivote++)
  {
    // El resultado se encuentra en la última columna de la matriz diagonalizada.
    soluciones.push_back((P)this->matriz_extendida_diagonalizada.obtenerElemento(pivote, this->matriz_extendida_diagonalizada.obtenerNumeroColumnas() - 1));
  }

  // Regresamos el vector resultante.
  return soluciones;
}

template <class P>
void GaussJordan<P>::mostrarInfinidadDeSoluciones()
{
  // Verificamos que el sistema tenga infinidad de soluciones.
  if (this->bandera_solucion != INFINIDAD_SOLUCIONES)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_INFINIDAD_DE_SOLUCIONES_INEXISTENTES);
  }

  // Imprimimos la información.
  std::cout << "El número de parámetros libres para nuestro sistema es: " << this->obtenerNumeroVariables() - this->matriz_extendida_diagonalizada.obtenerRango() << std::endl;

  // Recorremos la matriz pivote a pivote.
  int pivote;
  for (pivote = 0; pivote < this->matriz_extendida_diagonalizada.obtenerNumeroColumnas() && pivote < this->matriz_extendida_diagonalizada.obtenerNumeroFilas() && this->matriz_extendida_diagonalizada.obtenerElemento(pivote, pivote) == 1; pivote++)
  {
    std::cout << "~ x_{" << pivote + 1 << "} = ";
    for (int columna = pivote + 1; columna < this->matriz_extendida_diagonalizada.obtenerNumeroColumnas(); columna++)
    {
      // Extraemos el coeficiente actual.
      P coeficienteActual = this->matriz_extendida_diagonalizada.obtenerElemento(pivote, columna);

      // Si no es término independiente, mostramos la x_{} correspondiente, en otro caso, solo el valor ya que es el término independiente.
      if (coeficienteActual != 0 && columna < (this->matriz_extendida_diagonalizada.obtenerNumeroColumnas() - 1))
      {
        std::cout << (((coeficienteActual * -1) < 0) ? "" : "+ ") << (coeficienteActual * -1) << "x_{" << (columna + 1) << "} ";
      }
      else if (coeficienteActual != 0 && columna == (this->matriz_extendida_diagonalizada.obtenerNumeroColumnas() - 1))
      {
        std::cout << (coeficienteActual < 0 ? "" : "+ ") << coeficienteActual;
      }
    }
    // Saldo de línea.
    std::cout << std::endl;
  }

  // Mostramos los términos en función de Δ
  for (int delta = 1; pivote < this->obtenerNumeroVariables(); pivote++, delta++)
  {
    std::cout << "~ x_{" << pivote + 1 << "} = " << SIMBOLO_DELTA << "_{" << delta << "}" << std::endl;
  }

  // Imprimimos mensaje informativo sobre la utilidad del nuevo sistema mostrado.
  std::cout << std::endl
            << "Puede sustituir cualquier valor perteneciente a los números reales para cada Δ y obtendrá una solución válida."
            << std::endl;
}

/**
 * Mostrar Conclusión.
 * Imprime en pantalla el análisis sobre el sistema planteado y muestra
 * una aproximación en caso de ser posible.
 */
template <class P>
void GaussJordan<P>::mostrarConclusion()
{
  // Obtenemos la matriz de coeficientes diagonalizada.
  Matriz<P> matriz_coeficientes_diagonalizada = this->obtenerMatrizDeCoeficientesDiagonalizada();

  // Vector para los resultados si tenemos solución única.
  std::vector<P> resultados;

  // Mostramos la matriz extendida original.
  std::cout << "Matriz extendida (A*) original:" << std::endl;
  this->matriz_extendida.imprimir();
  std::cout << std::endl;

  // Mostramos la matriz extendida diagonalizada.
  std::cout << "Matriz extendida (A*) diagonalizada:" << std::endl;
  this->matriz_extendida_diagonalizada.imprimir();
  std::cout << std::endl;

  // Mostramos la matriz de coeficientes diagonalizada.
  std::cout << "Matriz coeficientes (A) diagonalizada:" << std::endl;
  matriz_coeficientes_diagonalizada.imprimir();
  std::cout << std::endl;

  // Obtenemos el rango de la matriz extendida diagonalizada.
  int rangoMatrizExtendidaDiagonalizada = this->matriz_extendida_diagonalizada.obtenerRango();
  int rangoMatrizCoeficientesDiagonalizada = matriz_coeficientes_diagonalizada.obtenerRango();

  // Mostramos el rango ajustamos nuestra bandera de solución.
  std::cout << "El rango de la matriz extendida diagonalizada (R(A*)) es: " << rangoMatrizExtendidaDiagonalizada << std::endl;
  std::cout << "El rango de la matriz de coeficientes diagonalizada (R(A)) es: " << rangoMatrizCoeficientesDiagonalizada << std::endl;

  // Depende la bandera lo que realizamos.
  switch (this->bandera_solucion)
  {
  case SOLUCION_UNICA:
    // Mostramos mensaje.
    std::cout << "Conclusión: El sistema tiene solución única (los rangos son iguales al número de incógnitas: R(A)=" << rangoMatrizCoeficientesDiagonalizada << " igual a R(A*)=" << rangoMatrizExtendidaDiagonalizada << " igual al número de incógnitas (" << this->obtenerNumeroVariables() << "))." << std::endl
              << "Los resultados son:" << std::endl
              << std::endl;

    // Obtenemos los resultados.
    resultados = this->obtenerSolucionesUnicas();

    // Imprimimos los resultados.
    for (int variable = 0; variable < resultados.size(); variable++)
    {
      std::cout << "\t~ x_{" << (variable + 1) << "} = " << resultados[variable] << std::endl;
    }
    break;
  case INFINIDAD_SOLUCIONES:
    // Mostramos mensaje.
    std::cout << "Conclusión: El sistema tiene una infinidad de soluciones (los rangos son iguales entre sí, pero distintos al número de incógnitas: R(A)=" << rangoMatrizCoeficientesDiagonalizada << " igual a R(A*)=" << rangoMatrizExtendidaDiagonalizada << ", pero distintos del número de incógnitas (" << this->obtenerNumeroVariables() << "))." << std::endl;

    // Imprimimos el análisis correspondiente.
    this->mostrarInfinidadDeSoluciones();
    break;
  case SIN_SOLUCION:
    // Mostramos mensaje.
    std::cout << "Conclusión: El sistema no tiene solución (los rangos son distintos: R(A)=" << rangoMatrizCoeficientesDiagonalizada << " diferente de R(A*)=" << rangoMatrizExtendidaDiagonalizada << ")." << std::endl;
    break;
  default:
    // Arrojamos una excepción.
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_BANDERA_SOLUCION_IRRECONOCIBLE);
    break;
  }
}

/**
 * Obtener Numero de Parametros Libres Infinidad de Soluciones.
 * Función que permite calcular el número de parámetros libres en un sistema de ecuaciones
 * dado que haya tenido como solución Infinidad de Soluciones, en caso de tener otro tipo de
 * solución, arrojará una excepción.
 * @return Un entero con el número de parámetros libres.
 */
template <class P>
int GaussJordan<P>::obtenerNumeroParametrosLibresInfinidadDeSoluciones()
{
  // Verificamos que el tipo de solución sea infinidad de soluciones.
  if (this->obtenerTipoDeSolucion() != INFINIDAD_SOLUCIONES)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_INFINIDAD_DE_SOLUCIONES_INEXISTENTES);
  }

  // Realizamos la operación.
  return this->obtenerNumeroVariables() - this->matriz_extendida_diagonalizada.obtenerRango();
}

/**
 * Funciones Privadas.
 */

/**
 * Resolver
 * Realiza el procedimiento de resolución Gauss-Jordan:
 * 1. Diagonaliza la matriz extendida.
 * 2. Verifica el tipo de solución mediante el rango.
 */
template <class P>
void GaussJordan<P>::resolver()
{
  // El primer paso es diagonalizar la matriz.
  this->diagonalizarMatriz();

  // El segundo paso es verificar el tipo de solución.
  this->verificarTipoSolucion();
}

/**
 * Diagonalizar Matriz
 * Realiza el procedimiento de diagonalización inferior y superior de la matriz
 * extendida.
 */
template <class P>
void GaussJordan<P>::diagonalizarMatriz()
{
  this->matriz_extendida_diagonalizada = this->matriz_extendida.diagonalizacionInferior();
  this->matriz_extendida_diagonalizada = this->matriz_extendida_diagonalizada.diagonalizacionSuperior();
}

/**
 * Verificar tipo de Solucion
 * En esta función realizamos la verificación del tipo de solución en función
 * del rango de la matriz diagonalizada por el teorema de Rouché-Fröbenius.
 */
template <class P>
void GaussJordan<P>::verificarTipoSolucion()
{
  // Obtenemos la matriz de coeficientes diagonalizada para realizar la comparación de rangos.
  Matriz<P> matriz_coeficientes_diagonalizada = this->obtenerMatrizDeCoeficientesDiagonalizada();

  // Obtenemos el rango de las matrices.
  int rangoMatrizExtendidaDiagonalizada = this->matriz_extendida_diagonalizada.obtenerRango();
  int rangoMatrizCoeficientesDiagonalizada = matriz_coeficientes_diagonalizada.obtenerRango();

  // Ajustamos nuestra bandera en función de los rangos calculados.
  if (rangoMatrizExtendidaDiagonalizada != rangoMatrizCoeficientesDiagonalizada)
  {
    // El sistema no tiene solución.
    this->bandera_solucion = SIN_SOLUCION;
  }
  else
  {
    if (rangoMatrizExtendidaDiagonalizada == this->obtenerNumeroVariables())
    {
      // El sistema tiene solución única.
      this->bandera_solucion = SOLUCION_UNICA;
    }
    else
    {
      // El sistema tiene una infinidad de soluciones.
      this->bandera_solucion = INFINIDAD_SOLUCIONES;
    }
  }
}

// Especificamos los tipos de datos válidos.
template class GaussJordan<int>;    // Enteros.
template class GaussJordan<float>;  // Números con punto flotante.
template class GaussJordan<double>; // Números con punto flotante con más precisión.
