#include "../Librerias/Matriz.hpp"
#include "../Librerias/UtileriasMatriz.hpp"
#include "../Librerias/GaussJordan.hpp"

int main(int argc, char *argv[])
{
  std::string parametroLeerMatriz = "--leerMatriz",
              parametroAyuda = "--ayuda";
  Matriz<float> matrizOriginal;

  // Verificamos si hay argumentos.
  if (argc > 1)
  {
    // Iteramos sobre los argumentos buscando alguno que conozcamos.
    for (int argumentoActual = 1; argumentoActual < argc; argumentoActual++)
    {
      if (parametroAyuda.compare(argv[argumentoActual]) == 0)
      {
        // Mensaje de ayuda.
        std::cout << "Resolución de Sistemas de Ecuaciones mediante Gauss-Jordan." << std::endl
                  << std::endl
                  << "Argumentos:" << std::endl
                  << "\t--ayuda       Muestra este menú con información para usar el programa." << std::endl
                  << "\t--leerMatriz  En lugar de leer el sistema de ecuaciones variable por variable, permite leer filas enteras de la matriz a a la vez." << std::endl
                  << std::endl
                  << "Créditos: Humberto Alejandro Ortega Alcocer - 2020" << std::endl
                  << std::endl;

        // Fin de ejecución de programa.
        return 0;
      }
      else if (parametroLeerMatriz.compare(argv[argumentoActual]) == 0)
      {
        // Leemos la matriz de forma interactiva.
        matrizOriginal = leerMatrizInteractiva<float>();
      }
    }

    // Verificamos si se utilizó algún parámetro para definir el modelo de lectura de la matriz.
    if (matrizOriginal.obtenerNumeroFilas() == 0)
    {
      matrizOriginal = leerSistemaDeEcuacionesInteractivo<float>();
    }
  }
  else
  {
    // Leemos la matriz en forma de sistema de ecuaciones.
    matrizOriginal = leerSistemaDeEcuacionesInteractivo<float>();
  }

  // Solucionamos el sistema de ecuaciones planteado mediante la matriz.
  GaussJordan<float> solucion(matrizOriginal);

  // Mostramos la conclusión de la solucion.
  solucion.mostrarConclusion();

  // Fin de la ejecución.
  std::cout << "Fin de ejecución." << std::endl
            << std::endl;

  // Exit status = 0.
  return 0;
}