/**
 * PruebaGaussJordan.cpp
 *
 * En este archivo se realizan varias pruebas de la clase GaussJordan<P> a fin
 * de verificar su correcto funcionamiento.
 */
#include <iostream>                    // Para imprimir mensajes.
#include <chrono>                      // Para medir el tiempo de ejecución de las pruebas.
#include <vector>                      // Para probar algunas respuestas de tipo vector.
#include "../Matriz.hpp"               // Para probar algunas respuestas de tipo Matriz<P>
#include "../GaussJordan.hpp"          // Para la clase GaussJordan.
#include "../ExcepcionGaussJordan.hpp" // Para las excepciones de la clase GaussJordan.

#define MENSAJE_CORRECTO "correcto"
#define MENSAJE_ERROR "<----------ERROR"

// Constantes pre-definidas para pruebas con matrices que representan sistemas de ecuaciones lineales.
Matriz<float> solucionUnica3x3({{3, -2, 3, 4},
                                {6, -1, 4, 1},
                                {1, -1, 1, 8}}),
    infinidadDeSoluciones4x2({{1, -1, -1, 1, 4},
                              {2, 1, 1, -1, 5}}),
    solucionUnica4x4({{1, -1, 0, 1, 1},
                      {1, 0, -1, 1, 6},
                      {1, 1, 1, 0, -3},
                      {-1, 1, -1, -1, 7}}),
    sinSolucion2x4({{1, -1, 3},
                    {1, 1, 4},
                    {-1, -1, 5},
                    {2, 1, 4}});

std::vector<float> resultadosSolucionUnica3x3{14.5, -20, -26.5},
    resultadosSolucionUnica4x4{8, -3, -8, -10};

// Prototipos de funciones para las pruebas.
bool pruebaObtenerTipoDeSolucion();
bool pruebaObtenerMatrizExtendidaOriginal();
bool pruebaObtenerMatrizDeCoeficientesOriginal();
bool pruebaObtenerMatrizExtendidaDiagonalizada();
bool pruebaObtenerMatrizDeCoeficientesDiagonalizada();
bool pruebaObtenerNumeroVariables();
bool pruebaObtenerNumeroEcuaciones();
bool pruebaObtenerSolucionesUnicas();
bool pruebaMostrarConclusion();

// Función de prueba.
void realizarPruebas()
{
  // Todas las pruebas se ejecutan en un try/catch.
  try
  {
    std::cout << "Prueba obtenerTipoDeSolucion: " << (pruebaObtenerTipoDeSolucion() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerMatrizExtendidaOriginal: " << (pruebaObtenerMatrizExtendidaOriginal() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerMatrizDeCoeficientesOriginal: " << (pruebaObtenerMatrizDeCoeficientesOriginal() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerMatrizExtendidaDiagonalizada: " << (pruebaObtenerMatrizExtendidaDiagonalizada() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerMatrizDeCoeficientesDiagonalizada: " << (pruebaObtenerMatrizDeCoeficientesDiagonalizada() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerNumeroVariables: " << (pruebaObtenerNumeroVariables() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerNumeroEcuaciones: " << (pruebaObtenerNumeroEcuaciones() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerSolucionesUnicas: " << (pruebaObtenerSolucionesUnicas() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba mostrarConclusión: " << (pruebaMostrarConclusion() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
  }
  catch (const ExcepcionGaussJordan &e)
  {
    std::cout << e.id() << " - " << e.mensaje() << std::endl;
  }
}

// Función principal.
int main(void)
{
  std::cout << "Suite de pruebas para la clase GaussJordan" << std::endl;
  auto inicio = std::chrono::high_resolution_clock::now();
  realizarPruebas();
  auto fin = std::chrono::high_resolution_clock::now();
  auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
  std::cout << "Ejecución correcta. Duración: " << duracion.count() << "ms." << std::endl
            << std::endl;
  return 0;
}

/**
 * Definiciones de los tests unitarios.
 */

bool pruebaObtenerTipoDeSolucion()
{
  GaussJordan<float> gauss1(infinidadDeSoluciones4x2),
      gauss2(sinSolucion2x4),
      gauss3(solucionUnica3x3);

  return gauss1.obtenerTipoDeSolucion() == INFINIDAD_SOLUCIONES && gauss2.obtenerTipoDeSolucion() == SIN_SOLUCION && gauss3.obtenerTipoDeSolucion() == SOLUCION_UNICA;
}

bool pruebaObtenerMatrizExtendidaOriginal()
{
  GaussJordan<float> gauss1(infinidadDeSoluciones4x2),
      gauss2(sinSolucion2x4),
      gauss3(solucionUnica3x3);

  return infinidadDeSoluciones4x2.esIgual(gauss1.obtenerMatrizExtendidaOriginal()) && sinSolucion2x4.esIgual(gauss2.obtenerMatrizExtendidaOriginal()) && solucionUnica3x3.esIgual(gauss3.obtenerMatrizExtendidaOriginal());
}

bool pruebaObtenerMatrizDeCoeficientesOriginal()
{
  GaussJordan<float> gauss1(infinidadDeSoluciones4x2),
      gauss2(sinSolucion2x4),
      gauss3(solucionUnica3x3);

  return infinidadDeSoluciones4x2.eliminarColumna(infinidadDeSoluciones4x2.obtenerNumeroColumnas() - 1).esIgual(gauss1.obtenerMatrizDeCoeficientesOriginal()) && sinSolucion2x4.eliminarColumna(sinSolucion2x4.obtenerNumeroColumnas() - 1).esIgual(gauss2.obtenerMatrizDeCoeficientesOriginal()) && solucionUnica3x3.eliminarColumna(solucionUnica3x3.obtenerNumeroColumnas() - 1).esIgual(gauss3.obtenerMatrizDeCoeficientesOriginal());
}

bool pruebaObtenerMatrizExtendidaDiagonalizada()
{
  return true;
}

bool pruebaObtenerMatrizDeCoeficientesDiagonalizada()
{
  return true;
}

bool pruebaObtenerNumeroVariables()
{
  GaussJordan<float> gauss1(infinidadDeSoluciones4x2),
      gauss2(sinSolucion2x4),
      gauss3(solucionUnica3x3);

  return gauss1.obtenerNumeroVariables() == 4 && gauss2.obtenerNumeroVariables() == 2 && gauss3.obtenerNumeroVariables() == 3;
}

bool pruebaObtenerNumeroEcuaciones()
{
  GaussJordan<float> gauss1(infinidadDeSoluciones4x2),
      gauss2(sinSolucion2x4),
      gauss3(solucionUnica3x3);

  return gauss1.obtenerNumeroEcuaciones() == 2 && gauss2.obtenerNumeroEcuaciones() == 4 && gauss3.obtenerNumeroEcuaciones() == 3;
}

bool pruebaObtenerSolucionesUnicas()
{
  GaussJordan<float> gauss1(solucionUnica3x3), gauss2(solucionUnica4x4);

  std::vector<float> soluciones1 = gauss1.obtenerSolucionesUnicas(),
                     soluciones2 = gauss2.obtenerSolucionesUnicas();

  std::cout << "Resta: " << (int)(soluciones1[0] - resultadosSolucionUnica3x3[0]) << std::endl;

  return soluciones1.size() == resultadosSolucionUnica3x3.size() && soluciones1[0] == resultadosSolucionUnica3x3[0]; // && soluciones2.size() == resultadosSolucionUnica4x4.size() && soluciones2[0] == resultadosSolucionUnica4x4[0];
}
bool pruebaMostrarConclusion()
{
  GaussJordan<float> gauss1(infinidadDeSoluciones4x2),
      gauss2(sinSolucion2x4),
      gauss3(solucionUnica3x3);

  std::cout << std::endl
            << "Infinidad de soluciones 4x2:" << std::endl;
  gauss1.mostrarConclusion();

  std::cout << std::endl
            << "Sin Solución 2x4:" << std::endl;
  gauss2.mostrarConclusion();

  std::cout << std::endl
            << "Solución Única 3x3:" << std::endl;
  gauss3.mostrarConclusion();

  // Se puede comprobar mediante el output.
  return true;
}
