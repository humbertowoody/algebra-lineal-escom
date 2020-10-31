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
 * Programa 3
 * 31 de Octubre de 2020.
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-2
 *
 */
#include <iostream>
#include "GaussJordan.hpp"
#include "ExcepcionGaussJordan.hpp"

/**
 * Constructor Gauss Jordan base.
 * Realiza las tareas de inicialización de variables miembro y establece
 * el estado inicial de nuestro solucionador.
 */
template <class P>
GaussJordan<P>::GaussJordan()
{
  this->matriz_extendida = NULL;                  // La matriz extendida inicia vacía.
  this->matriz_diagonalizada = NULL;              // La matriz diagonalizada inicia vacía.
  this->numero_ecuaciones = 0;                    // Número de ecuaciones 0.
  this->numero_variables = 0;                     // Número de variables 0.
  this->bandera_solucion = SOLUCION_NO_CALCULADA; // Bandera de solución -1.
}

/**
 * Destructor de la clase Gauss Jordan.
 * Limpia la memoria para todos los objetos y variables instanciadas.
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

  // Verificamos que los datos no hayan sido leídos previamente.
  if (this->matriz_extendida != NULL)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_MATRIZ_EXISTENTE);
  }

  // Inicializamos la matriz extendida vacía.
  this->matriz_extendida = new Matriz<P>();

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
  std::cout << "Se ha leído la matriz extendida (A*) de " << this->matriz_extendida->obtenerNumeroColumnas()
            << " columnas y " << this->matriz_extendida->obtenerNumeroFilas()
            << " filas siguiente:" << std::endl;
  this->matriz_extendida->imprimir();
}

/**
 * Diagonalizacion
 * Realiza el proceso de diagonalización de la matriz extendida.
 */
template <class P>
void GaussJordan<P>::diagonalizarMatriz()
{
  // Verificamos que la matriz exista.
  if (this->matriz_extendida == NULL)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_MATRIZ_INEXISTENTE_PARA_DIAGONALIZACION);
  }

  // Proceso de diagonalización.
  this->matriz_diagonalizada = new Matriz<P>(*this->matriz_extendida);

  // Dado que la coordenada del pivote siempre será en diagonal, únicamente requerimos
  // una variable para manejar su posición y a partir de ahí realizamos las operaciones
  // para ir colocando ceros por debajo del mismo (cuando sea posible, si el pivote es 0
  // entonces tratamos de buscar una fila, por debajo del mismo, para intercambiar y
  // seguir con el algoritmo).
  for (int pivote = 0; pivote < this->matriz_extendida->obtenerNumeroFilas() && pivote < this->matriz_extendida->obtenerNumeroColumnas(); pivote++)
  {
    // Mostramos el proceso.
    std::cout << "Diagonalizando para el pivote en a_{" << pivote + 1 << "," << pivote + 1 << "}:" << std::endl;
    this->matriz_diagonalizada->imprimir();
    std::cout << std::endl;

    // Hay que verificar que el pivote no sea 0 porque, bueno, ya sabemos ¿no?
    if (this->matriz_diagonalizada->obtenerElemento(pivote, pivote) == 0)
    {
      // Buscamos una fila en dónde, para la columna actual del pivote, el valor no
      // sea cero.
      for (int fila = pivote + 1; fila < this->matriz_diagonalizada->obtenerNumeroFilas(); fila++)
      {
        // Si encontramos una fila que no sea 0 y no hemos realizado el intercambio, intercambiamos.
        if (this->matriz_diagonalizada->obtenerElemento(fila, pivote) != 0 && this->matriz_diagonalizada->obtenerElemento(pivote, pivote) == 0)
        {
          // Realizamos el cambio de la fila.
          this->matriz_diagonalizada = new Matriz<P>(this->matriz_diagonalizada->intercambiarFilas(pivote, fila));
        }
      }
    }

    // Si, a pesar de nuestro intento, no pudimos encontrar una fila con un valor distinto a 0
    // en la columna de nuestro pivote, omitimos el resto del proceso para este pivote. En otro
    // caso, procedemos con el algoritmo para hacer 1's la diagonal y 0's por debajo.
    if (this->matriz_diagonalizada->obtenerElemento(pivote, pivote) != 0)
    {
      // Para hacer 1 el pivote, dividimos cada elemento de la fila entre 1/pivote.
      P factor = 1 / this->matriz_diagonalizada->obtenerElemento(pivote, pivote);
      for (int columna = pivote; columna < this->matriz_diagonalizada->obtenerNumeroColumnas(); columna++)
      {
        this->matriz_diagonalizada = new Matriz<P>(this->matriz_diagonalizada->asignarElemento(pivote, columna, factor * this->matriz_diagonalizada->obtenerElemento(pivote, columna)));
      }

      // Ahora tenemos que hacer ceros por debajo del pivote.
      for (int fila = pivote + 1; fila < this->matriz_diagonalizada->obtenerNumeroFilas(); fila++)
      {
        // Calculamos el factor de multiplicacion para que la columna pivote sea 0.
        P factor = this->matriz_diagonalizada->obtenerElemento(fila, pivote) * -1;

        // Realizamos la operación: factor(elemento de fila_1) + elemento de fila_2.
        for (int columna = pivote; columna < this->matriz_diagonalizada->obtenerNumeroColumnas(); columna++)
        {
          // Hacemos un casting porque si llega a realizarse una operación inválida, es preferible un valor "casteado" (forzado) a un NaN.
          this->matriz_diagonalizada = new Matriz<P>(this->matriz_diagonalizada->asignarElemento(fila, columna, (P)(factor * this->matriz_diagonalizada->obtenerElemento(pivote, columna)) + this->matriz_diagonalizada->obtenerElemento(fila, columna)));
        }
      }
    }
  }

  // Mostramos el resultado de la diagonalización inferior.
  std::cout << "Diagonalización inferior final:" << std::endl;
  this->matriz_diagonalizada->imprimir();
  std::cout << std::endl;

  // Ahora intentamos realizar la diagonalización superior, para esto, lo primero será encontrar el primer pivote
  // con valor válido (1).
  int pivoteInicial;
  for (pivoteInicial = 0; pivoteInicial < this->matriz_diagonalizada->obtenerNumeroFilas() && pivoteInicial < this->matriz_diagonalizada->obtenerNumeroColumnas() && this->matriz_diagonalizada->obtenerElemento(pivoteInicial, pivoteInicial) == 1; pivoteInicial++)
    ;
  pivoteInicial -= 1;

  std::cout << "Pivote inicial de diagonalización superior: " << pivoteInicial << std::endl;

  // Ciclo que recorre todos los pivotes a partir del pivote inicial calculado para ir haciendo
  // ceros por encima de la diagonal. Descartamos el elemento A_{1,1} porque no tiene elementos
  // encima.
  for (int pivote = pivoteInicial; pivote > 0; pivote--)
  {
    // Mostramos el proceso de diagonalización superior.
    std::cout << "Diagonalizando para el pivote en A*_{" << pivote + 1 << pivote + 1 << "}:" << std::endl;
    this->matriz_diagonalizada->imprimir();
    std::cout << std::endl;

    // Tratamos de hacer todas las filas sobre el pivote 0.
    for (int fila = 0; fila < pivote; fila++)
    {
      // Calculamos el factor que se aplicará a toda la fila.
      P factor = this->matriz_diagonalizada->obtenerElemento(fila, pivote) * -1;

      // Aplicamos la operación a toda la fila.
      for (int columna = pivote; columna < this->matriz_diagonalizada->obtenerNumeroColumnas(); columna++)
      {
        this->matriz_diagonalizada = new Matriz<P>(this->matriz_diagonalizada->asignarElemento(fila, columna, (P)(factor * this->matriz_diagonalizada->obtenerElemento(pivote, columna)) + this->matriz_diagonalizada->obtenerElemento(fila, columna)));
      }
    }
  }

  // Mostramos la diagonalización completa de la matriz extendida.
  std::cout << "Diagonalización completa final:" << std::endl;
  this->matriz_diagonalizada->imprimir();
  std::cout << std::endl;
}

/**
 * Verificar tipo de Solucion
 * En esta función realizamos la verificación del tipo de solución en función
 * del rango de la matriz diagonalizada por el teorema de Rouché-Fröbenius.
 */
template <class P>
void GaussJordan<P>::verificarTipoSolucion()
{
  // Verificamos que la matriz diagonalizada exista.
  if (this->matriz_diagonalizada == NULL)
  {
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_MATRIZ_DIAGONALIZADA_INEXISTENTE_PARA_VERIFICAR_SOLUCION);
  }

  // La matriz de coeficientes diagonalizada es la matriz extendida diagonalizada sin la última columna.
  Matriz<P> matriz_coeficientes_diagonalizada = this->matriz_diagonalizada->eliminarColumna(this->matriz_diagonalizada->obtenerNumeroColumnas() - 1);

  // Mostramos la matriz extendida diagonalizada.
  std::cout << "Matriz extendida (A*) diagonalizada:" << std::endl;
  this->matriz_diagonalizada->imprimir();
  std::cout << std::endl;

  // Mostramos la matriz de coeficientes diagonalizada.
  std::cout << "Matriz coeficientes (A) diagonalizada:" << std::endl;
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

/**
 * Calcular solución.
 * Realiza el cálculo de la solución final en función de la matriz diagonalizada e imprime la conclusión.
 */
template <class P>
void GaussJordan<P>::calcularSolucionFinal()
{
  // Depende la bandera lo que realizamos.
  switch (this->bandera_solucion)
  {
  case SOLUCION_NO_CALCULADA:
    // Arrojamos una excepción.
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_SOLUCION_NO_VERIFICADA);
    break;
  case SOLUCION_UNICA:
    // Mostramos mensaje.
    std::cout << "El sistema tiene solución única, a continuación se muestran los resultados:" << std::endl;

    // Iteramos sobre cada fila en la que el pivote fue 1 y guardamos el resultado.
    for (int pivote = 0; pivote < this->matriz_diagonalizada->obtenerNumeroColumnas() && pivote < this->matriz_diagonalizada->obtenerNumeroFilas() && this->matriz_diagonalizada->obtenerElemento(pivote, pivote) == 1; pivote++)
    {
      // El resultado se encuentra en la última columna de la matriz diagonalizada.
      std::cout << "~ x_{" << pivote + 1 << "} = " << this->matriz_diagonalizada->obtenerElemento(pivote, this->matriz_diagonalizada->obtenerNumeroColumnas() - 1) << std::endl;
    }

    break;
  case INFINIDAD_SOLUCIONES:
    std::cout << "El sistema tiene una infinidad de soluciones." << std::endl;

    // Imprimimos la información.
    std::cout << "El número de parámetros libres para nuestro sistema es: " << this->numero_variables - this->matriz_diagonalizada->obtenerRango() << std::endl;

    // Recorremos la matriz pivote a pivote.
    int pivote;
    for (pivote = 0; pivote < this->matriz_diagonalizada->obtenerNumeroColumnas() && pivote < this->matriz_diagonalizada->obtenerNumeroFilas() && this->matriz_diagonalizada->obtenerElemento(pivote, pivote) == 1; pivote++)
    {
      std::cout << "~ x_{" << pivote + 1 << "} = ";
      for (int columna = pivote + 1; columna < this->matriz_diagonalizada->obtenerNumeroColumnas(); columna++)
      {
        // Extraemos el coeficiente actual.
        P coeficienteActual = this->matriz_diagonalizada->obtenerElemento(pivote, columna);

        // Si no es término independiente, mostramos la x_{} correspondiente, en otro caso, solo el valor ya que es el término independiente.
        if (coeficienteActual != 0 && columna < (this->matriz_diagonalizada->obtenerNumeroColumnas() - 1))
        {
          std::cout << (((coeficienteActual * -1) < 0) ? "" : "+ ") << (coeficienteActual * -1) << "x_{" << (columna + 1) << "} ";
        }
        else if (coeficienteActual != 0 && columna == (this->matriz_diagonalizada->obtenerNumeroColumnas() - 1))
        {
          std::cout << (coeficienteActual < 0 ? "" : "+ ") << coeficienteActual;
        }
      }
      // Saldo de línea.
      std::cout << std::endl;
    }

    // Mostramos los términos en función de Δ
    for (int delta = 1; pivote < this->numero_variables; pivote++, delta++)
    {
      std::cout << "~ x_{" << pivote + 1 << "} = " << SIMBOLO_DELTA << "_{" << delta << "}" << std::endl;
    }

    // Imprimimos mensaje informativo sobre la utilidad del nuevo sistema mostrado.
    std::cout << std::endl
              << "Puede sustituir cualquier valor perteneciente a los números reales para cada Δ y obtendrá una solución válida."
              << std::endl;
    break;
  case SIN_SOLUCION:
    std::cout << "El sistema no tiene solución. No es posible realizar un cálculo o aproximación." << std::endl;
    break;
  default:
    // Arrojamos una excepción.
    throw ExcepcionGaussJordan(ERROR_GAUSS_JORDAN_BANDERA_SOLUCION_IRRECONOCIBLE);
    break;
  }
}

// Especificamos los tipos de datos válidos.
template class GaussJordan<int>;    // Enteros.
template class GaussJordan<float>;  // Números con punto flotante.
template class GaussJordan<double>; // Números con punto flotante con más precisión.
