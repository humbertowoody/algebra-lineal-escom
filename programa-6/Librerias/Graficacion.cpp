/**
 * Graficacion.cpp
 * En este archivo se incluye la implementación de las funciones para la librería Graficacion.hpp.
 */
#include "Graficacion.hpp"
#include <matplot/matplot.h> // Librería de graficación.

/**
 * Graficar Matriz de Coordenadas
 * Realiza la graficación de una matriz de coordenadas en dónde cada fila representa un polígono a graficar.
 * @param coordenadas La matriz de coordenadas.
 * @param titulos Un vector con los títulos a utilizar para la graficación.
 */
void graficacion::graficarMatrizCoordenadas(std::vector<std::vector<algebralineal::coordenada>> coordenadas, std::vector<std::string> titulos)
{
  // Variables locales.
  std::vector<float> x, y; // Vectores para almacenar las coordenadas.

  // Añadimos cada coordenada a su vector correspondiente.
  for (int i = 0; i < coordenadas.size(); i++)
  {
    // Limpiamos los vectores de coordenadas temporales.
    x.clear();
    y.clear();

    for (int j = 0; j < coordenadas[i].size(); j++)
    {
      // Extraemos las coordenadas.
      x.push_back(coordenadas[i][j].x);
      y.push_back(coordenadas[i][j].y);
    }

    // Las añadimos a la gráfica.
    auto p = matplot::plot(x, y);

    // Definimos las etiquetas de cada gráfica.
    if (i == 0)
    {
      p->display_name("Polígono original.");
      p->line_width(2);
    }
    else if (i + 1 == coordenadas.size())
    {
      p->display_name("Polígono final con todas las transformaciones aplicadas.");
      p->line_width(2);
    }
    else
    {
      p->display_name(titulos[i - 1]);
    }

    // Esperamos al resto de las gráficas.
    matplot::hold(matplot::on);
  }

  // Ya podemos plottear los datos.
  matplot::hold(matplot::off);

  // Configuración de visualización de la gráfica.
  matplot::title("Transformaciones Lineales a un Polígono");
  matplot::xlabel("Eje X");
  matplot::ylabel("Eje Y");
  matplot::axis(matplot::equal);
  matplot::grid(matplot::on);
  matplot::legend(matplot::on);

  // Mostramos la gráfica.
  matplot::show();
}