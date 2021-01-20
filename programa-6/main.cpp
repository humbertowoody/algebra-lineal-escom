/**
 * Escuela Superior de Cómputo - Instituto Politécnico Nacional
 * Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
 *
 * Programa que realiza transformaciones lineales sobre un polígono y las grafica.
 *
 * Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Programa 6
 * 23 de Enero del 2021
 *
 * Link de repositorio: https://github.com/humbertowoody/algebra-lineal-escom/tree/main/programa-6
 */
#include "./Librerias/AlgebraLineal.hpp" // Para las transformaciones lineales.
#include "./Librerias/Graficacion.hpp"   // Para operaciones de graficación.
#include <iostream>                      // Para operaciones de entrada y salida estándar.
#include <sstream>                       // Para generar objetos de flujo de entrada y salida.

// Constantes de operación.
#define MENU_REFLEXION_EJE_X 1  // Opción de menú para transformación de reflexión en el eje x.
#define MENU_REFLEXION_EJE_Y 2  // Opción de menú para transformación de reflexión en el eje y.
#define MENU_CORTE_EJE_X 3      // Opción de menú para transformación de corte en el eje x.
#define MENU_CORTE_EJE_Y 4      // Opción de menú para transformación de corte en el eje y.
#define MENU_EXPANSION_EJE_X 5  // Opción de menú para transformación de expansión en el eje x.
#define MENU_EXPANSION_EJE_Y 6  // Opción de menú para transformación de expansión en el eje y.
#define MENU_COMPRESION_EJE_X 7 // Opción de menú para transformación de compresión en el eje x.
#define MENU_COMPRESION_EJE_Y 8 // Opción de menú para transformación de compresión en el eje y.
#define MENU_ROTACION 9         // Opción de menú para transformación de rotación.
#define MENU_CONTINUAR 10       // Opción de menú para continuar y mostrar las gráficas finales.

// Función principal.
int main()
{
  // Variables locales.
  int numeroCoordenadas;                                                           // El número de coordenadas en el polígono.
  algebralineal::coordenada coordenadaTemporal;                                    // Para operaciones temporales.
  std::vector<algebralineal::coordenada> vecCoordenadas,                           // Para realizar operaciones con un polígono.
      vecCoordenadasTodasLasTransformaciones;                                      // Un vector de coordenadas con todas las transformaciones aplicadas.
  std::vector<std::vector<algebralineal::coordenada>> coordenadasTransformaciones; // Para almacenar todas las coordenadas de cada transformación aplicada al polígono inicial.
  std::string linea;                                                               // Para la lectura de las coordenadas de forma eficiente.
  int opcionMenu;                                                                  // Para almacenar la opción seleccionada en el menú principal.
  float temporal;                                                                  // Para operaciones temporales.
  std::vector<std::string> titulosTransformaciones;                                // Un vector con los títulos de las transformaciones aplicadas.
  std::stringstream ss;                                                            // Para formar los títulos de las transformaciones.

  // Mensaje inicial.
  std::cout << "Graficador de Transformaciones Lineales sobre un polígono" << std::endl
            << "Escuela Superior de Cómputo - Instituto Politécnico Nacional" << std::endl
            << "Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal" << std::endl
            << std::endl
            << "Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>" << std::endl
            << "Programa: 6" << std::endl
            << std::endl;

  // Leemos el número de coordenadas en el polígono.
  std::cout << "Ingrese el número de puntos en el polígono:" << std::endl
            << "> ";
  std::cin >> numeroCoordenadas;

  // Hack para getline.
  std::getline(std::cin, linea);

  // Leemos cada coordenada del polígono.
  std::cout << std::endl
            << "A continuación, ingrese cada coordenada del polígono separando x de y por un espacio:" << std::endl
            << std::endl
            << "\t\t     Ejemplo: -12.3 34.3" << std::endl;
  for (int coordenadaActual = 0; coordenadaActual < numeroCoordenadas; coordenadaActual++)
  {
    // Indicamos la coordenada que será leída.
    std::cout << "\tCoordenadas punto #" << (coordenadaActual + 1) << ": ";

    // Leemos la línea.
    std::getline(std::cin, linea);

    // Convertimos la linea en un stream de lectura.
    std::istringstream bufferDeEntrada(linea);

    // Obtenemos las coordenadas.
    bufferDeEntrada >> coordenadaTemporal.x >> coordenadaTemporal.y;

    // Añadimos la coordenada a nuestro vector de coordenadas.
    vecCoordenadas.push_back(coordenadaTemporal);
  }

  // Añadimos de nuevo la última coordenada para trazar correctamente el polígono.
  vecCoordenadas.push_back(vecCoordenadas[0]);

  // Inicializamos el vector con las coordenadas finales aplicando todas las transformaciones.
  vecCoordenadasTodasLasTransformaciones = vecCoordenadas;

  // Añadimos este primer vector como nuestro polígono inicial a las coordenadas de las transformaciones.
  coordenadasTransformaciones.push_back(vecCoordenadas);

  // Leemos las transformaciones a realizar.
  do
  {
    std::cout << std::endl
              << "Transformaciones disponibles:" << std::endl
              << std::endl
              << "\t" << MENU_REFLEXION_EJE_X << ") Reflexión en eje x." << std::endl
              << "\t" << MENU_REFLEXION_EJE_Y << ") Reflexión en eje y." << std::endl
              << "\t" << MENU_CORTE_EJE_X << ") Corte en eje x." << std::endl
              << "\t" << MENU_CORTE_EJE_Y << ") Corte en eje y." << std::endl
              << "\t" << MENU_EXPANSION_EJE_X << ") Expansión en eje x." << std::endl
              << "\t" << MENU_EXPANSION_EJE_Y << ") Expansión en eje y." << std::endl
              << "\t" << MENU_COMPRESION_EJE_X << ") Compresión en eje x." << std::endl
              << "\t" << MENU_COMPRESION_EJE_Y << ") Compresión en eje y." << std::endl
              << "\t" << MENU_ROTACION << ") Rotación." << std::endl
              << "\t-" << std::endl
              << "\t" << MENU_CONTINUAR << ") Continuar con las transformaciones seleccionadas." << std::endl
              << std::endl
              << "Ingrese la opción para aplicar la transformación, o " << MENU_CONTINUAR << " para continuar:" << std::endl;

    // Leer la opción.
    do
    {
      std::cout << "[1-10]> ";
      std::cin >> opcionMenu;
    } while (opcionMenu < 1 || opcionMenu > 10); // Sanitizar entrada.

    // Determinamos la transformación seleccionada.
    switch (opcionMenu)
    {
    case MENU_REFLEXION_EJE_X:
      // Generamos el título de la transformación.
      linea = "Reflexión en el eje x.";
      titulosTransformaciones.push_back(linea);

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::reflexionRespectoAEjeX(coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::reflexionRespectoAEjeX(vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_REFLEXION_EJE_Y:
      // Generamos el título de la transformación.
      linea = "Reflexión en el eje y.";
      titulosTransformaciones.push_back(linea);

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::reflexionRespectoAEjeY(coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::reflexionRespectoAEjeY(vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_CORTE_EJE_X:
      // Leemos el valor de c.
      std::cout << "Ingrese el valor para c: ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Corte en el eje x con c=" << std::fixed << std::setprecision(2) << temporal << ".";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::corteEjeX(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::corteEjeX(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_CORTE_EJE_Y:
      // Leemos el valor de c.
      std::cout << "Ingrese el valor para c: ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Corte en el eje y con c=" << std::fixed << std::setprecision(2) << temporal << ".";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::corteEjeY(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::corteEjeY(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_EXPANSION_EJE_X:
      // Leemos el valor de c.
      std::cout << "Ingrese el valor para c: ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Expansión en el eje x con c=" << std::fixed << std::setprecision(2) << temporal << ".";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::expansionEjeX(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::expansionEjeX(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_EXPANSION_EJE_Y:
      // Leemos el valor de c.
      std::cout << "Ingrese el valor para c: ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Expansión en el eje y con c=" << std::fixed << std::setprecision(2) << temporal << ".";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::expansionEjeY(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::expansionEjeY(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_COMPRESION_EJE_X:
      // Leemos el valor de c.
      std::cout << "Ingrese el valor para c: ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Compresión en el eje x con c=" << std::fixed << std::setprecision(2) << temporal << ".";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::compresionEjeX(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::compresionEjeX(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_COMPRESION_EJE_Y:
      // Leemos el valor de c.
      std::cout << "Ingrese el valor para c: ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Compresión en el eje y con c=" << std::fixed << std::setprecision(2) << temporal << ".";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::compresionEjeY(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::compresionEjeY(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_ROTACION:
      // Leemos el número de grados para la rotación.
      std::cout << "¿En cuántos grados desea realizar la rotación?" << std::endl
                << "> ";
      std::cin >> temporal;

      // Generamos el título de la transformación.
      ss << "Rotación " << std::fixed << std::setprecision(2) << temporal << "º.";
      titulosTransformaciones.push_back(ss.str());
      ss.str(std::string());
      ss.clear();

      // Aplicamos la transformación y la añadimos a la lista de graficaciones.
      for (int i = 0; i <= numeroCoordenadas; i++)
      {
        vecCoordenadas[i] = algebralineal::rotacion(temporal, coordenadasTransformaciones[0][i]);
        vecCoordenadasTodasLasTransformaciones[i] = algebralineal::rotacion(temporal, vecCoordenadasTodasLasTransformaciones[i]);
      }
      coordenadasTransformaciones.push_back(vecCoordenadas);
      break;
    case MENU_CONTINUAR:
      // Mostramos un mensaje.
      std::cout << "Se aplicarán las transformaciones seleccionadas y serán graficadas en el orden que fueron seleccionadas." << std::endl;
      break;
    }
  } while (opcionMenu != MENU_CONTINUAR);

  // Añadimos el vector con las coordenadas resultantes de todas las transformaciones al final.
  coordenadasTransformaciones.push_back(vecCoordenadasTodasLasTransformaciones);

  // Hack para getline, de nuevo para la gráfica.
  std::getline(std::cin, linea);

  // Graficamos el polígono + las transformaciones aplicadas.
  std::cout << std::endl
            << "Se mostrará una gráfica en una ventana emergente." << std::endl
            << std::endl;
  graficacion::graficarMatrizCoordenadas(coordenadasTransformaciones, titulosTransformaciones);

  // Mensaje final.
  std::cout << std::endl
            << "¡Gracias por utilizar este programa!" << std::endl
            << std::endl;

  // En este punto la ejecución del programa fue exitosa, exit status = 0.
  return 0;
}
