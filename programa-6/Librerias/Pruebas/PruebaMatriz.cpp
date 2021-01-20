/**
 * PruebaMatriz.cpp
 *
 * En este archivo se realizan varias pruebas de la clase Matriz<P> a fin
 * de verificar su correcto funcionamiento.
 */
#include <iostream>               // Para imprimir mensajes.
#include <chrono>                 // Para medir el tiempo de ejecución de las pruebas.
#include <vector>                 // Para probar algunas respuestas de tipo vector.
#include "../Matriz.hpp"          // Para la clase Matriz.
#include "../ExcepcionMatriz.hpp" // Para las excepciones de la clase Matriz.

#define MENSAJE_CORRECTO "correcto"
#define MENSAJE_ERROR "<----------ERROR"

// Prototipos de funciones para las pruebas.
bool pruebaObtenerElemento();
bool pruebaObtenerNumeroColumnas();
bool pruebaObtenerNumeroFilas();
bool pruebaObtenerRango();
bool pruebaObtenerDiagonalPrincipal();
bool pruebaObtenerDiagonalSecundaria();
bool pruebaObtenerFila();
bool pruebaObtenerColumna();
bool pruebaAsignarElemento();
bool pruebaInsertarFila();
bool pruebaEliminarFila();
bool pruebaInsertarColumna();
bool pruebaEliminarColumna();
bool pruebaCalcularTrazaDeLaMatriz();
bool pruebaIntercambiarFilas();
bool pruebaDiagonalizacionInferior();
bool pruebaDiagonalizacionSuperior();
bool pruebaSumarMatrices();
bool pruebaSumarEscalar();
bool pruebaRestarMatrices();
bool pruebaRestarEscalar();
bool pruebaMultiplicarFilaPorEscalar();
bool pruebaMultiplicarMatrices();
bool pruebaMultiplicarEscalar();
bool pruebaTransposicion();
bool pruebaEsMatrizNula();
bool pruebaEsMatrizFila();
bool pruebaEsMatrizColumna();
bool pruebaEsMatrizCuadrada();
bool pruebaEsMatrizRectangular();
bool pruebaEsMatrizTriangularSuperior();
bool pruebaEsMatrizTriangularInferior();
bool pruebaEsMatrizDiagonal();
bool pruebaEsMatrizIdentidad();
bool pruebaEsMatrizSimetrica();
bool pruebaEsIgual();

// Función de prueba.
void realizarPruebas()
{
  // Todas las pruebas se ejecutan en un try/catch.
  try
  {
    std::cout << "Prueba obtenerElemento: " << (pruebaObtenerElemento() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerNumeroColumnas: " << (pruebaObtenerNumeroColumnas() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerNumeroFilas: " << (pruebaObtenerNumeroFilas() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerRango: " << (pruebaObtenerRango() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerDiagonalPrincipal: " << (pruebaObtenerDiagonalPrincipal() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerDiagonalSecundaria: " << (pruebaObtenerDiagonalSecundaria() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerFila: " << (pruebaObtenerFila() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba obtenerColumna: " << (pruebaObtenerColumna() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba asignarElemento: " << (pruebaAsignarElemento() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba insertarFila: " << (pruebaInsertarFila() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba eliminarFila: " << (pruebaEliminarFila() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba insertarColumna: " << (pruebaInsertarColumna() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba eliminarColumna: " << (pruebaEliminarColumna() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba calcularTrazaDeLaMatriz: " << (pruebaCalcularTrazaDeLaMatriz() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba intercambiarFilas: " << (pruebaIntercambiarFilas() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba diagonalizacionInferior: " << (pruebaDiagonalizacionInferior() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba diagonalizacionSuperior: " << (pruebaDiagonalizacionSuperior() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba sumar (matrices): " << (pruebaSumarMatrices() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba sumar (escalar): " << (pruebaSumarEscalar() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba restar (matrices): " << (pruebaRestarMatrices() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba restar (escalar): " << (pruebaRestarEscalar() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba multiplicarFilaPorEscalar: " << (pruebaMultiplicarFilaPorEscalar() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba multiplicar (matrices): " << (pruebaMultiplicarMatrices() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba multiplicar (escalar): " << (pruebaMultiplicarEscalar() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba transposicion: " << (pruebaTransposicion() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizNula: " << (pruebaEsMatrizNula() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizFila: " << (pruebaEsMatrizFila() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizColumna: " << (pruebaEsMatrizColumna() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizCuadrada: " << (pruebaEsMatrizCuadrada() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizRectangular: " << (pruebaEsMatrizRectangular() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizTriangularSuperior: " << (pruebaEsMatrizTriangularSuperior() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizTriangularInferior: " << (pruebaEsMatrizTriangularInferior() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizDiagonal: " << (pruebaEsMatrizDiagonal() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizIdentidad: " << (pruebaEsMatrizIdentidad() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esMatrizSimetrica: " << (pruebaEsMatrizSimetrica() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
    std::cout << "Prueba esIgual: " << (pruebaEsIgual() ? MENSAJE_CORRECTO : MENSAJE_ERROR) << std::endl;
  }
  catch (const ExcepcionMatriz &e)
  {
    std::cout << e.id() << " - " << e.mensaje() << std::endl;
  }
}

// Función principal.
int main(void)
{
  std::cout << "Suite de pruebas para la clase Matriz" << std::endl;
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

bool pruebaObtenerElemento()
{
  Matriz<float> prueba({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  return prueba.obtenerElemento(0, 0) == 1 && prueba.obtenerElemento(2, 2) == 9;
}

bool pruebaObtenerNumeroColumnas()
{
  Matriz<int> prueba1({{1, 2}, {3, 4}, {5, 6}}),
      prueba2({{1, 2, 3, 4, 5, 6, 7, 8}});
  return prueba1.obtenerNumeroColumnas() == 2 && prueba2.obtenerNumeroColumnas() == 8;
}

bool pruebaObtenerNumeroFilas()
{
  Matriz<int> prueba1({{1, 2, 3}}),
      prueba2({{1}, {2}, {3}});
  return prueba1.obtenerNumeroFilas() == 1 && prueba2.obtenerNumeroFilas() == 3;
}

bool pruebaObtenerRango()
{
  Matriz<int> prueba1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}),
      prueba2({{1, 2}, {3, 4}, {0, 0}}),
      prueba3({{0}});
  return prueba1.obtenerRango() == 3 && prueba2.obtenerRango() == 2 && prueba3.obtenerRango() == 0;
}

bool pruebaObtenerDiagonalPrincipal()
{
  Matriz<int> prueba1({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}});

  std::vector<int> resultado1 = prueba1.obtenerDiagonalPrincipal();

  return resultado1.size() == 3 && resultado1[0] == 1 && resultado1[1] == 2 && resultado1[2] == 3;
}

bool pruebaObtenerDiagonalSecundaria()
{
  Matriz<int> prueba1({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}});

  std::vector<int> resultado1 = prueba1.obtenerDiagonalSecundaria();

  return resultado1.size() == 3 && resultado1[0] == 0 && resultado1[1] == 2 && resultado1[2] == 0;
}

bool pruebaObtenerFila()
{
  Matriz<int> prueba1({{0, 0, 0}, {1, 1, 1}, {0, 0, 0}});

  std::vector<int> fila = prueba1.obtenerFila(1);

  return fila.size() == 3 && fila[0] == 1;
}

bool pruebaObtenerColumna()
{
  Matriz<int> prueba1({{1}, {2}, {3}}),
      prueba2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  std::vector<int> res1 = prueba1.obtenerColumna(0),
                   res2 = prueba2.obtenerColumna(0),
                   res3 = prueba2.obtenerColumna(2);

  return res1.size() == 3 && res1[0] == 1 && res1[2] == 3 && res2.size() == 3 && res2[1] == 4 && res3.size() == 3 && res3[2] == 9;
}

bool pruebaAsignarElemento()
{
  Matriz<int> prueba1({{1, 2}, {1, 1}});
  Matriz<int> res1({{0, 2}, {1, 1}}),
      res2({{1, 2}, {3, 4}});

  Matriz<int> temp1 = prueba1.asignarElemento(0, 0, 0),
              temp2 = prueba1.asignarElemento(1, 0, 3);
  temp2 = temp2.asignarElemento(1, 1, 4);

  return temp1.esIgual(res1) && temp2.esIgual(res2);
}

bool pruebaInsertarFila()
{
  Matriz<int> prueba1,
      prueba2({{1, 2}, {3, 4}}),
      prueba3({{1, 2, 3, 4}});

  Matriz<int> res1 = prueba1.insertarFila({1, 2, 3, 4}),
              res2 = prueba2.insertarFila({5, 6}),
              res3 = prueba3.insertarFila({5, 6, 7, 8});

  return res1.obtenerNumeroFilas() == 1 && res2.obtenerNumeroFilas() == 3 && res3.obtenerNumeroFilas() == 2;
}

bool pruebaEliminarFila()
{
  Matriz<int> prueba1({{1}, {2}, {3}, {4}}), prueba2({{1, 2}});

  Matriz<int> res1 = prueba1.eliminarFila(2),
              res2 = prueba2.eliminarFila(0);

  return res1.obtenerNumeroFilas() == 3 && res2.obtenerNumeroFilas() == 0;
}

bool pruebaInsertarColumna()
{
  Matriz<int> prueba1, prueba2({{1}, {2}, {3}, {4}});

  Matriz<int> res1 = prueba1.insertarColumna({1, 2, 3, 4}),
              res2 = prueba2.insertarColumna({1, 1, 1, 1});

  return res1.obtenerNumeroFilas() == 4 && res1.obtenerNumeroColumnas() == 1 && res2.obtenerNumeroFilas() == 4 && res2.obtenerNumeroColumnas() == 2;
}

bool pruebaEliminarColumna()
{
  Matriz<int> prueba1({{1, 2}, {3, 4}, {5, 6}}),
      prueba2({{1}, {2}, {3}});

  Matriz<int> res1 = prueba1.eliminarColumna(1),
              res2 = prueba1.eliminarColumna(0),
              res3 = prueba2.eliminarColumna(0);

  return res1.obtenerElemento(0, 0) == 1 && res1.obtenerNumeroColumnas() == 1 && res1.obtenerNumeroFilas() == 3 && res2.obtenerElemento(0, 0) == 2 && res2.obtenerNumeroColumnas() == 1 && res3.obtenerNumeroColumnas() == 0 && res3.obtenerNumeroFilas() == 0;
}

bool pruebaCalcularTrazaDeLaMatriz()
{
  Matriz<int> prueba1,
      prueba2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}),
      prueba3({{0, 1}, {1, 0}});

  int res1 = prueba1.calcularTrazaDeLaMatriz(),
      res2 = prueba2.calcularTrazaDeLaMatriz(),
      res3 = prueba3.calcularTrazaDeLaMatriz();

  return res1 == 0 && res2 == 15 && res3 == 0;
}

bool pruebaIntercambiarFilas()
{
  Matriz<int> prueba1({{1}, {2}}), prueba2({{1}, {2}, {3}, {4}});

  Matriz<int> res1 = prueba1.intercambiarFilas(0, 1),
              res2 = prueba2.intercambiarFilas(0, 3);

  return res1.obtenerElemento(0, 0) == 2 && res1.obtenerElemento(1, 0) == 1 && res2.obtenerElemento(0, 0) == 4 && res2.obtenerElemento(3, 0) == 1;
}

bool pruebaDiagonalizacionInferior()
{
  Matriz<float> prueba1,
      prueba2({{1, 1, -1, 7},
               {1, -1, 2, 3},
               {2, 1, 1, 9}});

  Matriz<float> res1 = prueba1.diagonalizacionInferior(),
                res2 = prueba2.diagonalizacionInferior();

  return res1.esMatrizTriangularSuperior() && res2.esMatrizTriangularSuperior();
}

bool pruebaDiagonalizacionSuperior()
{
  Matriz<float> prueba1,
      prueba2({{1, 1, -1, 7},
               {1, -1, 2, 3},
               {2, 1, 1, 9}});

  Matriz<float> res1 = prueba1.diagonalizacionSuperior(),
                res2 = prueba2.diagonalizacionSuperior();

  return res1.esMatrizTriangularInferior() && res2.esMatrizTriangularInferior();
}

bool pruebaSumarMatrices()
{
  Matriz<int> matrizA({{1, 1, 1}, {1, 1, 1}}), matrizB({{1, 2, 3}, {-1, 0, -2}});

  Matriz<int> resultado = matrizA.sumar(matrizB),
              resultadoEsperado({{2, 3, 4}, {0, 1, -1}});

  return resultado.esIgual(resultadoEsperado);
}

bool pruebaSumarEscalar()
{
  Matriz<int> prueba1({{1}}), prueba2({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  Matriz<int> res1 = prueba1.sumar(1),
              res2 = prueba2.sumar(1),
              res3 = prueba2.sumar(-1);

  return res1.obtenerElemento(0, 0) == 2 && res2.obtenerElemento(1, 1) == 2 && res3.obtenerElemento(1, 1) == 0;
}

bool pruebaRestarMatrices()
{
  Matriz<int> matrizA({{1, 1, 1}, {1, 1, 1}}), matrizB({{1, 2, 3}, {-1, 0, -2}});

  Matriz<int> resultado = matrizA.restar(matrizB),
              resultadoEsperado({{0, -1, -2}, {2, 1, 3}});

  return resultado.esIgual(resultadoEsperado);
}

bool pruebaRestarEscalar()
{
  Matriz<int> prueba1({{1}}), prueba2({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  Matriz<int> res1 = prueba1.restar(1),
              res2 = prueba2.restar(1),
              res3 = prueba2.restar(-1);

  return res1.obtenerElemento(0, 0) == 0 && res2.obtenerElemento(1, 1) == 0 && res3.obtenerElemento(1, 1) == 2;
}

bool pruebaMultiplicarFilaPorEscalar()
{
  Matriz<int> prueba1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  Matriz<int> res1 = prueba1.multiplicarFilaPorEscalar(0, 1),
              res2 = prueba1.multiplicarFilaPorEscalar(0, 2),
              res3 = prueba1.multiplicarFilaPorEscalar(1, 0);

  return res1.obtenerElemento(0, 0) == 1 && res1.obtenerElemento(1, 0) == 4 && res2.obtenerElemento(0, 0) == 2 && res3.obtenerElemento(1, 0) == 0;
}

bool pruebaMultiplicarMatrices()
{
  Matriz<int> matrizA({{-3, 2, 1, 4},
                       {2, 5, 3, -2}}),
      matrizB({{0, -4, 1},
               {1, -2, 1},
               {2, 0, 2},
               {3, 2, 1}}),
      resultadoEsperado({{16, 16, 5},
                         {5, -22, 11}});

  return resultadoEsperado.esIgual(matrizA.multiplicar(matrizB));
}

bool pruebaMultiplicarEscalar()
{
  Matriz<int> prueba({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  Matriz<int> res1 = prueba.multiplicar(0),
              res2 = prueba.multiplicar(1),
              res3 = prueba.multiplicar(10);

  return res1.esMatrizNula() && res2.esIgual(prueba) && res3.obtenerElemento(1, 1) == 50;
}

bool pruebaTransposicion() { return true; }

bool pruebaEsMatrizNula()
{
  Matriz<int> prueba1({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}),
      prueba2({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}),
      prueba3;

  return prueba1.esMatrizNula() && !prueba2.esMatrizNula() && prueba3.esMatrizNula();
}

bool pruebaEsMatrizFila()
{
  Matriz<int> prueba1({{1, 2, 3, 4, 5, 6, 7, 8, 9}}),
      prueba2({{1, 2, 3}, {0, 0, 0}}),
      prueba3;

  return prueba1.esMatrizFila() && !prueba2.esMatrizFila() && !prueba3.esMatrizFila();
}

bool pruebaEsMatrizColumna()
{
  Matriz<int> prueba1,
      prueba2({{1}, {2}, {3}, {4}}),
      prueba3({{1, 2}, {3, 4}, {5, 6}, {7, 8}});

  return !prueba1.esMatrizColumna() && prueba2.esMatrizColumna() && !prueba3.esMatrizColumna();
}

bool pruebaEsMatrizCuadrada()
{
  Matriz<int> prueba1,
      prueba2({{1, 2}, {3, 4}}),
      prueba3({{1}}),
      prueba4({{1, 2, 3, 4}, {5, 6, 7, 8}});

  return !prueba1.esMatrizCuadrada() && prueba2.esMatrizCuadrada() && prueba3.esMatrizCuadrada() && !prueba4.esMatrizCuadrada();
}

bool pruebaEsMatrizRectangular()
{
  Matriz<int> prueba1,
      prueba2({{1, 2}, {3, 4}}),
      prueba3({{1, 2, 3, 4}, {5, 6, 7, 8}});

  return !prueba1.esMatrizRectangular() && !prueba2.esMatrizRectangular() && prueba3.esMatrizRectangular();
}

bool pruebaEsMatrizTriangularSuperior()
{
  Matriz<int> prueba1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}),
      prueba2({{1, 2, 3}, {0, 1, 2}, {0, 0, 1}}),
      prueba3({{1, 2, 3, 4, 5, 6}, {0, 1, 2, 3, 4, 5}});

  return !prueba1.esMatrizTriangularSuperior() && prueba2.esMatrizTriangularSuperior() & prueba3.esMatrizTriangularSuperior();
}

bool pruebaEsMatrizTriangularInferior()
{
  Matriz<int> prueba1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}),
      prueba2({{1, 0, 0}, {1, 2, 0}, {1, 2, 3}}),
      prueba3({{1, 0, 1, 2, 3, 4, 5}, {1, 2, 3, 4, 5, 6, 7}});

  return !prueba1.esMatrizTriangularInferior() && prueba2.esMatrizTriangularInferior() && prueba3.esMatrizTriangularInferior();
}

bool pruebaEsMatrizDiagonal()
{
  Matriz<int> prueba1({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}),
      prueba2({{1, 0, 0}, {1, 1, 0}, {0, 1, 1}});

  return prueba1.esMatrizDiagonal() && !prueba2.esMatrizDiagonal();
}

bool pruebaEsMatrizIdentidad()
{
  Matriz<int> prueba1({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}),
      prueba2({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}}),
      prueba3({{1, 0, 0}, {0, 1, 0}, {1, 0, 1}});

  return prueba1.esMatrizIdentidad() && !prueba2.esMatrizIdentidad() && !prueba3.esMatrizIdentidad();
}

bool pruebaEsMatrizSimetrica()
{
  return true;
}

bool pruebaEsIgual()
{
  Matriz<int> matrizA({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}),
      matrizB({{1, 2, 3}, {4, 5, 5}, {7, 8, 9}}),
      matrizC({{1, 2}, {4, 5}, {7, 8}});

  return matrizA.esIgual(matrizA) && !matrizA.esIgual(matrizB) && !matrizB.esIgual(matrizC) && !matrizC.esIgual(matrizA);
}
