/**
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 * Programa que determina si un conjunto de vectores son linealmente dependientes o independientes
 * y si otro vector es una combinación lineal de éstos.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 4
 * 29 de Noviembre de 2020
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-4
 */
#include <iostream> // Para operaciones de entrada y salida.
#include <vector>   // Para almacenar elementos en formato de vector.

// Librerías personales.
#include "./Librerias/Matriz.hpp"               // Para utilizar "matrices" y sus funcionalidades.
#include "./Librerias/GaussJordan.hpp"          // Para utilizar el procedimiento Gauss-Jordan para resolver sistemas de
                                                // ecuaciones lineales.
#include "./Librerias/ExcepcionGaussJordan.hpp" // Para las excepciones que pudieran surgir del uso de Gauss-Jordan.

// Constantes de operación.
#define MIN_ELEMENTOS_VECTOR 2           // El número mínimo de elementos en un vector.
#define MAX_ELEMENTOS_VECTOR 10          // El número máximo de elementos en un vector.
#define MIN_VECTORES_ESPACIO_GENERADO 2  // El número mínimo de vectores en nuestro espacio generado.
#define MAX_VECTORES_ESPACIO_GENERADO 10 // El número máximo de vectores en nuestro espacio generado.

// Prototipos de funciones.
void comprobarDependenciaLineal(std::vector<std::vector<float>>);
void comprobarSiEsCombinacionLineal(std::vector<float>, std::vector<std::vector<float>>);

// Función principal.
int main()
{
  // Variables locales.
  int numeroElementosVector,                               // Para almacenar el número de elementos que tendrá cada vector (R^n)
      numeroVectoresEspacioGenerado;                       // Para almacenar el número de vectores que tendrá nuestro espacio generado.
  float temporal;                                          // Un valor temporal para operaciones variadas.
  std::vector<std::vector<float>> vectoresEspacioGenerado; // Un vector de vectores para almacenar nuestros vectores del espacio generado.
  std::vector<float> vectorTemporal,                       // Un vector temporal para operaciones variadas.
      vectorU;                                             // El vector U para comprobar si es una combinación lineal de los vectores en el espacio generado.

  // Imprimimos mensaje inicial sobre el programa.
  std::cout << "Combinación, dependencia e independencia lineal" << std::endl
            << "Escuela Superior de Cómputo - Instituto Politécnico Nacional" << std::endl
            << "Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal" << std::endl
            << std::endl
            << "Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>" << std::endl
            << "Programa: 4" << std::endl
            << std::endl;

  // Leer el número de vectores que se introducirán.
  std::cout << "¿Cuántos vectores, además del vector u, deseas ingresar?" << std::endl;
  do
  {
    std::cout << "[" << MIN_VECTORES_ESPACIO_GENERADO << " - " << MAX_VECTORES_ESPACIO_GENERADO << "]> ";
    std::cin >> numeroVectoresEspacioGenerado;
  } while (numeroVectoresEspacioGenerado < MIN_VECTORES_ESPACIO_GENERADO || numeroVectoresEspacioGenerado > MAX_VECTORES_ESPACIO_GENERADO);

  // Leer el número de elementos que tendrán nuestros vectores.
  std::cout << "¿Cuántos elementos tendrán los vectores?" << std::endl;
  do
  {
    std::cout << "[" << MIN_ELEMENTOS_VECTOR << " - " << MAX_ELEMENTOS_VECTOR << "]> ";
    std::cin >> numeroElementosVector;
  } while (numeroElementosVector < MIN_ELEMENTOS_VECTOR || numeroElementosVector > MAX_ELEMENTOS_VECTOR); // Validación de entrada.

  // Mensaje de confirmación.
  std::cout << "A continuación, se realizará la lectura de los " << numeroVectoresEspacioGenerado << " vectores del esapcio generado." << std::endl;

  // Leemos los n vectores.
  for (int vectorActual = 0; vectorActual < numeroVectoresEspacioGenerado; vectorActual++)
  {
    // Mensaje de confirmación.
    std::cout << "Leyendo datos para el vector #" << (vectorActual + 1) << ":" << std::endl;

    // Borramos todos los elementos presentes en el vector temporal.
    vectorTemporal.clear();

    // Leemos cada elementos del vector.
    for (int elementoVector = 0; elementoVector < numeroElementosVector; elementoVector++)
    {
      // Leemos el elemento.
      std::cout << "Vector #" << (vectorActual + 1) << ", elemento #" << (elementoVector + 1) << ": ";
      std::cin >> temporal;

      // Lo almacenamos en nuestro vector temporal.
      vectorTemporal.push_back(temporal);
    }

    // Añadimos el vector a nuestro arreglo de vectores del espacio generado.
    vectoresEspacioGenerado.push_back(vectorTemporal);
  }

  // Mensaje informativo.
  std::cout << "Ahora se leerá el vector u." << std::endl;

  // Leemos los n elementos del vector U.
  for (int elementoVector = 0; elementoVector < numeroElementosVector; elementoVector++)
  {
    // Leemos el dato.
    std::cout << "Vector U, elemento #" << (elementoVector + 1) << ": ";
    std::cin >> temporal;

    // Guardamos el dato en el vector u.
    vectorU.push_back(temporal);
  }

  // Ahora realizaremos la comprobación de dependencia o independencia lineal entre los vectores.
  std::cout << std::endl
            << "¿Los vectores son linealmente dependientes?" << std::endl;
  comprobarDependenciaLineal(vectoresEspacioGenerado);

  // Ahora comprobamos si U es una combinación lineal de los vectores en el espacio generado.
  std::cout << std::endl
            << "¿U es una combinación lineal de <v1, v2,...,vn>?" << std::endl;
  comprobarSiEsCombinacionLineal(vectorU, vectoresEspacioGenerado);

  // Finalizamos la ejecución.
  std::cout << std::endl
            << "Fin de ejecución." << std::endl
            << std::endl;
  return 0;
}

/**
 * Comprobar Dependencia Lineal
 * Esta función realiza la comprobación de si un grupo de vectores son, o no,
 * linealmente dependientes o independientes.
 * @param vectores Un vector de vectores con los vectores a verificar.
 */
void comprobarDependenciaLineal(std::vector<std::vector<float>> vectores)
{
  // Variables locales.
  Matriz<float> matrizSistemaDeEcuaciones; // La matriz que representa nuestro sistema de ecuaciones lineales.
  std::vector<float> vecTemporal;          // Un vector temporal.

  // Cada vector representa una columna de la matriz, así que los añadimos de esa forma.
  for (int vectorActual = 0; vectorActual < vectores.size(); vectorActual++)
  {
    matrizSistemaDeEcuaciones = matrizSistemaDeEcuaciones.insertarColumna(vectores[vectorActual]);
  }

  // Para plantear el sistema apropiado, los términos independientes deberán ser ceros
  // por lo que añadimos una columna de n ceros.
  for (int fila = 0; fila < matrizSistemaDeEcuaciones.obtenerNumeroFilas(); fila++)
  {
    vecTemporal.push_back(0);
  }

  // Añadimos la columna con los términos independientes.
  matrizSistemaDeEcuaciones = matrizSistemaDeEcuaciones.insertarColumna(vecTemporal);

  // Utilizamos Gauss-Jordan para resolver el sistema de ecuaciones lineales planteado.
  GaussJordan<float> sistemaDependenciaLineal(matrizSistemaDeEcuaciones);

  // Verificamos el tipo de conclusión que imprimir.
  if (sistemaDependenciaLineal.obtenerTipoDeSolucion() == SIN_SOLUCION)
  {
    std::cout << "Conclusión: Los vectores son linealmente independientes (L.I.) ya que el sistema no tuvo solución." << std::endl;
  }
  else
  {
    if (sistemaDependenciaLineal.obtenerTipoDeSolucion() == SOLUCION_UNICA)
    {
      // Obtenemos las soluciones.
      std::vector<float> soluciones = sistemaDependenciaLineal.obtenerSolucionesUnicas();

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

      // Concluímos en función de si hubo o no un elemento distinto a 0.
      if (todosCero)
      {
        // Mostramos un mensaje.
        std::cout << "Conclusión: Los vectores son linealmente independientes (L.I.) ya que los escalares solución son todos cero." << std::endl;
      }
      else
      {
        // Mostramos un mensaje.
        std::cout << "Conclusión: Los vectores son linealmente dependientes (L.D.)" << std::endl
                  << std::endl
                  << "Los escalares que cumplen la solución son:" << std::endl
                  << std::endl;

        // Imprimimos las soluciones.
        for (int solucionActual = 0; solucionActual < soluciones.size(); solucionActual++)
        {
          std::cout << "\t· a_{" << (solucionActual + 1) << "}: " << soluciones[solucionActual] << std::endl;
        }
      }
    }
    else
    {
      // Mostramos un mensaje.
      std::cout << "Conclusión: Los vectores son linealmente dependientes (L.D.)" << std::endl
                << std::endl
                << "Dado que el sistema tuvo infinidad de soluciones, se presentan las ecuaciones para obtener soluciones válidas:" << std::endl
                << std::endl;

      // Imprimimos la conclusión del análisis Gauss-Jordan.
      sistemaDependenciaLineal.mostrarInfinidadDeSoluciones();
    }
  }
}

/**
 * Comprobar Si Es Combinación Lineal
 * Esta función realiza la comprobación, mediante Gauss-Jordan, de si un vector U es una combinación lineal
 * de un conjunto de vectores en un espacio generado.
 * @param vectorU El vector que queremos comprobar si es combinación lineal de un espacio generado.
 * @param vectoresEspacioGenerado Un conjunto de vectores dentro del espacio generado.
 */
void comprobarSiEsCombinacionLineal(std::vector<float> vectorU, std::vector<std::vector<float>> vectoresEspacioGenerado)
{
  // Variables locales.
  Matriz<float> matrizSistemaDeEcuaciones; // Nuestra matriz para representar nuestro sistema de ecuaciones lineales.

  // Cada uno de nuestros vectores del espacio generado representa una columna de nuestra matriz para el sistema de
  // ecuaciones lineales, así que los añadimos apropiadamente.
  for (int vectorActual = 0; vectorActual < vectoresEspacioGenerado.size(); vectorActual++)
  {
    matrizSistemaDeEcuaciones = matrizSistemaDeEcuaciones.insertarColumna(vectoresEspacioGenerado[vectorActual]);
  }

  // Añadimos a la matriz nuestros determinantes, que en este caso son los elementos del vector u.
  matrizSistemaDeEcuaciones = matrizSistemaDeEcuaciones.insertarColumna(vectorU);

  // Resolvemos mediante Gauss-Jordan.
  GaussJordan<float> sistemaCombinacionLineal(matrizSistemaDeEcuaciones);

  // Verificamos el tipo de conclusión a partir del tipo de solución del sistema de ecuaciones.
  if (sistemaCombinacionLineal.obtenerTipoDeSolucion() == SIN_SOLUCION)
  {
    std::cout << "Conclusión: U no es una combinación lineal de los vectores en el espacio generado. El sistema no tuvo solución." << std::endl;
  }
  else
  {
    if (sistemaCombinacionLineal.obtenerTipoDeSolucion() == SOLUCION_UNICA)
    {
      // Mostramos mensaje de conclusión.
      std::cout << "Conclusión: U si es combinación lineal de los vectores en el esapcio generado. El sistema tuvo solución única, por lo que existen escalares que satisfacen las condiciones." << std::endl
                << std::endl
                << "Los escalares que prueban que U es una combinación lineal de los vectores son:" << std::endl
                << std::endl;

      // Obtenemos los escalares de nuestro procedimiento Gauss-Jordan.
      std::vector<float> escalares = sistemaCombinacionLineal.obtenerSolucionesUnicas();

      // Imprimimos los escalares.
      for (int escalar = 0; escalar < escalares.size(); escalar++)
      {
        std::cout << "\t· a_{" << (escalar + 1) << "}: " << escalares[escalar] << std::endl;
      }
    }
    else
    {
      // Mostramos mensaje de conclusión.
      std::cout << "Conclusión: U si es combinación lineal de los vectores en el espacio generado. El sistema tuvo infinidad de soluciones, por lo que existen escalares que satisfacen las condiciones." << std::endl
                << std::endl
                << "Las ecuaciones dónde podemos sustituir valores reales para obtener soluciones válidas son:" << std::endl
                << std::endl;

      // Mostramos la conclusión del método GaussJordan.
      sistemaCombinacionLineal.mostrarInfinidadDeSoluciones();
    }
  }
}