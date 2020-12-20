/**
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 *
 * Programa que calcula las bases del espacio imagen y del espacio nulo a partir
 * de una matriz inicial.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 5
 * 20 de Diciembre del 2020
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-5
 */
#include "./Librerias/Matriz.hpp"               // Para modelar matrices.
#include "./Librerias/GaussJordan.hpp"          // Para resolver sistemas de ecuaciones lineales.
#include "./Librerias/AlgebraLineal.hpp"        // Funciones de Álgebra Lineal (espacio de nombres "algebralineal")
#include "./Librerias/UtileriasMatriz.hpp"      // Utilerías generales.
#include "./Librerias/ExcepcionGaussJordan.hpp" // Para las excepciones de GaussJordan.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  Matriz<float> matrizOriginal; // Para almacenar la matriz original.

  // Mensajes iniciales.
  std::cout << "Generador de bases del espacio nulo e imagen a partir de una matriz inicial" << std::endl
            << "Escuela Superior de Cómputo - Instituto Politécnico Nacional" << std::endl
            << "Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal" << std::endl
            << std::endl
            << "Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>" << std::endl
            << "Programa: 5" << std::endl
            << std::endl;

  // Leemos la matriz de forma interactiva.
  matrizOriginal = leerMatrizInteractiva<float>();

  // Procedimiento con control de errores.
  try
  {
    // Calculamos una base en el espacio nulo.
    algebralineal::vectoresReales baseEspacioNulo = algebralineal::obtenerBaseEspacioNulo(matrizOriginal);

    // Verificamos si hubo base para el espacio nulo.
    if (baseEspacioNulo.size())
    {
      // Mostramos la base.
      std::cout << "Una base del espacio nulo es:" << std::endl
                << "Nu(A) = ";
      algebralineal::imprimirVectoresReales(baseEspacioNulo);
      std::cout << std::endl;
    }
    else
    {
      // No hubo base.
      std::cout << "No existe una base para el espacio nulo." << std::endl;
    }

    // Calculamos una base para el espacio imagen.
    algebralineal::vectoresReales baseEspacioImagen = algebralineal::obtenerBaseEspacioImagen(matrizOriginal);

    // Verificamos si hubo base para el espacio imagen.
    if (baseEspacioImagen.size())
    {
      // Mostramos la base.
      std::cout << std::endl
                << "Una base del espacio imagen es:" << std::endl
                << "Im(A) = ";
      algebralineal::imprimirVectoresReales(baseEspacioImagen);
      std::cout << std::endl;
    }
    else
    {
      // No hubo base.
      std::cout << "No existe una base para el espacio imagen." << std::endl;
    }
  }
  catch (const ExcepcionMatriz &excepcionMatriz)
  {
    std::cout << "Hubo un error manipulando una matriz: " << excepcionMatriz.id() << " ~ " << excepcionMatriz.mensaje() << std::endl;
  }
  catch (const ExcepcionGaussJordan &excepcionGaussJordan)
  {
    std::cout << "Hubo en error en el procedimiento Gauss-Jordan: " << excepcionGaussJordan.id() << " ~ " << excepcionGaussJordan.mensaje() << std::endl;
  }

  // En este punto la ejecución fue exitosa.
  return 0;
}