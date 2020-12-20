/**
 * AlgebraLineal.cpp
 * Este archivo contiene la implementación de las funciones presentes en el espacio
 * de nombres "algebralineal".
 */
#include "AlgebraLineal.hpp"
#include <algorithm>
#include <iterator>

/**
 * Vectores Linealmente Dependientes
 * Función que verifica si un grupo de vectores son linealmente dependientes (L.D.) entre sí.
 * @param vectores Un vector con los vectores a verificar
 * @return Un valor booleano indicando el resultado.
 */
bool algebralineal::vectoresLinealmenteDependientes(algebralineal::vectoresReales vectores)
{
  // Variables locales.
  Matriz<float> matrizSistemaDeEcuaciones; // Para almacenar nuestra matriz de nuestro sistema de ecuaciones.
  std::vector<float> vectorTemporal;       // Vector para operaciones temporales.

  // Metemos cada vector como una columna en nuestra matriz extendida.
  for (int vectorActual = 0; vectorActual < vectores.size(); vectorActual++)
  {
    matrizSistemaDeEcuaciones = matrizSistemaDeEcuaciones.insertarColumna(vectores[vectorActual]);
  }

  // LLenamos nuestro vector temporal con ceros.
  for (int filaActual = 0; filaActual < matrizSistemaDeEcuaciones.obtenerNumeroFilas(); filaActual++)
  {
    vectorTemporal.push_back(0);
  }

  // Metemos el vector temporal como una columna, los términos independientes.
  matrizSistemaDeEcuaciones = matrizSistemaDeEcuaciones.insertarColumna(vectorTemporal);

  // Resolvemos mediante GaussJordan.
  GaussJordan<float> sistemaDeEcuacionesLD(matrizSistemaDeEcuaciones);

  // Verificamos el tipo de solución.
  if (sistemaDeEcuacionesLD.obtenerTipoDeSolucion() == SIN_SOLUCION)
  {
    return false; // L.I.
  }
  else if (sistemaDeEcuacionesLD.obtenerTipoDeSolucion() == SOLUCION_UNICA)
  {
    // Obtenemos las soluciones.
    std::vector<float> soluciones = sistemaDeEcuacionesLD.obtenerSolucionesUnicas();

    // Verificamos si existe, al menos, un elemento distinto a 0.
    bool todosCero = true; // Asumimos que todos son 0 de entrada.

    // Iteramos por las soluciones.
    for (int solucionActual = 0; solucionActual < soluciones.size(); solucionActual++)
    {
      if (soluciones[solucionActual] != 0)
      {
        todosCero = false; // Ajustamos la bandera apropiadamente.
        break;             // Salimos del ciclo.
      }
    }

    // Si todos son cero, NO es linealmente dependiente.
    // Si NO todos son cero, es linealmente dependiente.
    return !todosCero;
  }
  else
  {
    return true; // L.D. porque tiene múltiples soluciones.
  }
}

/**
 * Vectores Linealmente Independientes
 * Función para verificar si un grupo de vectores dados son linealmente independientes.
 * @param vectores Un vector con los vectores a verificar.
 * @return Un valor booleano con el resultado de la verificación.
 */
bool algebralineal::vectoresLinealmenteIndependientes(algebralineal::vectoresReales vectores)
{
  // Si no es linealmente dependiente, es linealmente independiente.
  return !algebralineal::vectoresLinealmenteDependientes(vectores);
}

/**
 * Obtener Base Espacio Nulo
 * Realiza el cálculo de la base en el espacio nulo para la matriz proporcionada.
 * @param matrizOriginal Una matriz A
 * @return Un conjunto de vectores con la base del espacio nulo, o un vector vacío si no hay base.
 */
algebralineal::vectoresReales algebralineal::obtenerBaseEspacioNulo(Matriz<float> matrizOriginal)
{
  // Variables locales.
  vectorReal vectorTemporal; // Un vector para operaciones temporales.
  vectoresReales resultados; // Un conjunto de vectores para el resultado.

  // Insertamos ceros en el vector temporal en función de las filas en la matriz.
  for (int filaActual = 0; filaActual < matrizOriginal.obtenerNumeroFilas(); filaActual++)
  {
    vectorTemporal.push_back(0);
  }

  // Insertamos el vector temporal como nuestro determinante en la matriz.
  matrizOriginal = matrizOriginal.insertarColumna(vectorTemporal);

  // Resolvemos mediante Gauss-Jordan.
  GaussJordan<float> solucionSistemaDeEcuaciones(matrizOriginal);

  // Verificamos si hay infinidad de soluciones.
  if (solucionSistemaDeEcuaciones.obtenerTipoDeSolucion() == INFINIDAD_SOLUCIONES)
  {
    // Obtenemos la matriz final diagonalizada.
    Matriz<float> matrizDiagonalizada = solucionSistemaDeEcuaciones.obtenerMatrizDeCoeficientesDiagonalizada();

    // Con la matriz diagonalizada, procedemos a descomponer nuestros parámetros libres.
    for (int i = 0; i < solucionSistemaDeEcuaciones.obtenerNumeroParametrosLibresInfinidadDeSoluciones(); i++)
    {
      // Vaciamos nuestro vector temporal.
      vectorTemporal.clear();

      // Iteramos por las filas.
      for (int filaActual = 0; filaActual < matrizDiagonalizada.obtenerNumeroFilas(); filaActual++)
      {
        if (filaActual == (matrizDiagonalizada.obtenerNumeroColumnas() - i - 1))
        {
          vectorTemporal.push_back(1);
        }
        else
        {
          vectorTemporal.push_back(-1 * matrizDiagonalizada.obtenerElemento(filaActual, matrizDiagonalizada.obtenerNumeroColumnas() - i - 1));
        }
      }

      // Añadimos los elementos faltantes.
      for (int j = vectorTemporal.size(); j < solucionSistemaDeEcuaciones.obtenerNumeroVariables(); j++)
      {
        if (j == (matrizDiagonalizada.obtenerNumeroColumnas() - i - 1))
        {
          vectorTemporal.push_back(1);
        }
        else
        {
          vectorTemporal.push_back(0);
        }
      }

      // Insertamos el vector temporal en resultados.
      resultados.push_back(vectorTemporal);
    }

    // Verificamos que los vectores sean L.I.
    if (algebralineal::vectoresLinealmenteIndependientes(resultados))
    {
      // Si son L.I. son nuestra base.
      return resultados;
    }
    else
    {
      // Si son L.D. no son una base.
      return {};
    }
  }
  else
  {
    // Si hay solución única o sin solución, no son una base.
    return {};
  }
}

/**
 * Búsqueda Combinación Linealmente Independiente.
 * Realiza todas las permutaciones posibles de un conjunto de vectores reales y devuelve la primera cuyos
 * vectores sean linealmente independientes, en caso de que no encuentre ninguna, regresará un vector vacío.
 * @param profundidad La profundidad actual de la búsqueda (inicial 0)
 * @param elementosPorCombinacion El número de elementos para cada combinación.
 * @param offset Un offset de inicio para recorrer los vectores.
 * @param combinaciones Un conjunto de vectores reales con las combinaciones calculadas.
 * @param vectoresIniciales Un conjunto de vectores reales iniciales.
 * @return Un conjunto de vectores reales con los elementos L.I. o vacío si no hubo elementos L.I.
 */
algebralineal::vectoresReales algebralineal::busquedaCombinacionLinealmenteIndependiente(int profundidad, int elementosPorCombinacion, int offset, algebralineal::vectoresReales &combinaciones, const algebralineal::vectoresReales &vectoresIniciales)
{
  // Verificamos si la profundidad de la recursividad ha alcanzado al número de elementos que buscamos por combinación.
  if (profundidad == elementosPorCombinacion)
  {
    // Iteramos sobre las distintas permutaciones de una combinación particular.
    do
    {
      // Verificamos si la permutación en cuestión es linealmente independiente.
      if (algebralineal::vectoresLinealmenteIndependientes(combinaciones))
      {
        // Si fue linealmente independiente, la regresamos.
        return combinaciones;
      }
    } while (std::next_permutation(combinaciones.begin(), combinaciones.end())); // Usamos esta función para permutar.

    // Si llegamos a este punto, quiere decir que ninguna permutación fue linealmente independiente.
    return {};
  }
  else
  {
    // En caso de que aún no sea la profundidad esperada, iteramos a partir del elemento siguiente al offset.
    for (int j = offset + 1; j < (int)vectoresIniciales.size(); ++j)
    {
      // Añadimos el elemento actual.
      combinaciones.push_back(vectoresIniciales[j]);

      // Paso recursivo.
      algebralineal::vectoresReales f = algebralineal::busquedaCombinacionLinealmenteIndependiente(profundidad + 1, elementosPorCombinacion, j, combinaciones, vectoresIniciales);

      // Verificamos si alguna permutación fue L.I.
      if (!f.empty())
      {
        // Si alguna permutación fue L.I. la regresamos.
        return f;
      }

      // En este punto no hubo una base, así que sacamos el elemento y continuamos con el proceso.
      combinaciones.pop_back();
    }

    // En este punto, ninguna permutación fue L.I. por lo que se termina la ejecución.
    return {};
  }
}

/**
 * Obtener Base Espacio Imagen
 * Realiza el cálculo de una base para el espacio imagen de una matriz dada.
 * @param matrizOriginal La matriz original
 * @return Un conjunto de vectores que conforman la base, o un vector vacío si no es posible calcular la base.
 */
algebralineal::vectoresReales algebralineal::obtenerBaseEspacioImagen(Matriz<float> matrizOriginal)
{
  // Variables locales.
  algebralineal::vectoresReales resultados, // Un conjunto de vectores para la base encontrada.
      temporal,                             // Una variable para operaciones intermedias.
      columnas,                             // Para almacenar nuestros vectores columna.
      baseEspacioNulo;                      // Par almacenar la base del espacio nulo.

  // Calculamos una base en el espacio nulo.
  baseEspacioNulo = algebralineal::obtenerBaseEspacioNulo(matrizOriginal);

  // Calculamos la dimensión esperada.
  int dimensionEsperada = matrizOriginal.obtenerNumeroColumnas() - baseEspacioNulo.size();

  // Creamos nuestros vectores columnas a partir de la matriz.
  for (int columnaActual = 0; columnaActual < matrizOriginal.obtenerNumeroColumnas(); columnaActual++)
  {
    columnas.push_back(matrizOriginal.obtenerColumna(columnaActual));
  }

  // Ordenamos las columnas.
  std::sort(columnas.begin(), columnas.end());

  // Borramos duplicados.
  columnas.erase(std::unique(columnas.begin(), columnas.end()), columnas.end());

  // Búsqueda de una combinación de nuestros vectores columnas que sean L.I.
  return algebralineal::busquedaCombinacionLinealmenteIndependiente(0, dimensionEsperada, -1, temporal, columnas);
}

/**
 * Imprimir Vector Real
 * Esta función toma un vector real y lo muestra en la terminal con formato.
 * @param vectorAImprimir Un vector real a imprimir.
 */
void algebralineal::imprimirVectorReal(algebralineal::vectorReal vectorAImprimir)
{
  // Paréntesis inicial.
  std::cout << "( ";

  // n-1 elementos.
  for (int posicionEnVector = 0; posicionEnVector < vectorAImprimir.size(); posicionEnVector++)
  {
    // Imprimirmos el elemento en la coordenada.
    std::cout << vectorAImprimir.at(posicionEnVector);

    // Decidimos si es el último elemento para imprimir, o no, una coma.
    if (posicionEnVector != (vectorAImprimir.size() - 1))
    {
      std::cout << ", ";
    }
  }

  // Paréntesis final.
  std::cout << " )";
}

/**
 * Imprimir Vectores Reales
 * Esta función toma un conjunto de vectores reales y los imprime con notación de conjunto.
 * @param vectoresAImprimir Un conjunto de vectores reales a imprimir.
 */
void algebralineal::imprimirVectoresReales(algebralineal::vectoresReales vectoresAImprimir)
{
  std::cout << "{ ";

  for (int vectorActual = 0; vectorActual < vectoresAImprimir.size(); vectorActual++)
  {
    // Imprimimos el vector.
    algebralineal::imprimirVectorReal(vectoresAImprimir.at(vectorActual));

    // Imprimimos una coma si no es el último elemento.
    if (vectorActual != (vectoresAImprimir.size() - 1))
    {
      std::cout << ", ";
    }
  }

  // Llave final.
  std::cout << " }";
}
