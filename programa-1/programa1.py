#
# Escuela Superior de Cómputo - Instituto Politécnico Nacional
# Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal
# Programa que resuelve un sistema de ecuaciones lineales por el método: Gauss-Jordan.
#
# Humberto Alejandro Ortega Alcocer
# Programa 1
# 19 de Octubre de 2020.
#

# Importamos para graficar.
import matplotlib.pyplot as plt
import numpy as np

# ---- Funciones del programa ----

def imprimir_matriz(matriz, max_filas, max_columnas):
	"""
	Función que imprime una matriz.
	"""
	for fila in range(0,max_filas):
		print("(", end='')
		for columna in range(0,max_columnas):
			print(matriz[fila][columna], end='')
			if (columna < (max_columnas-1)):
				print(',',end='')
			pass
		print(")")
		pass
	print("")
	pass


def rango_matriz(matriz, filas, columnas):
	"""
	Función que calcula el rango de una matriz.
	"""
	rango = 0 # Asumimos que el rango es 0.
	for fila_actual in range(filas):
		fila_con_valor_diferente_a_cero = False
		for columna_actual in range(columnas):
			# Revisamos si el valor es distinto a 0.
			if matriz[fila_actual][columna_actual] != 0:
				fila_con_valor_diferente_a_cero = True
				break

		# Si la fila tiene al menos un valor diferente a cero, contabilizamos.
		if fila_con_valor_diferente_a_cero:
			rango = rango + 1
	# Regresamos la contabilización de filas con valores distintos a cero.
	return rango

# ---- Ejecución Principal ----

# Mensaje incicial.
print("Sistemas de Ecuaciones Lineales de 2x2 por Gauss-Jordan")
print("Escuela Superior de Cómputo - Instituto Politécnico Nacional")
print("Dr. Dárwin Gutiérrez Mejía - Álgebra Lineal")
print()
print("Alumno: Humberto Alejandro Ortega Alcocer")
print("Programa: 1")
print()

# Mostramos instrucciones generales.
print("Este programa no puede leer fracciones, si desea introducir números racionales, porfavor introdúzcalos usando representación decimal, gracias.")
print()

# Leemos la primer ecuación.
print("Leyendo datos para la primer ecuación.")
x1 = float(input("Ingresa el valor para x1: "))
y1 = float(input("Ingresa el valor para y1: "))
b1 = float(input("Ingresa el valor para el término independiente 1: "))
print()

# Leemos la segunda ecuación.
print("Leyendo datos para la segunda ecuación.")
x2 = float(input("Ingresa el valor para x2: "))
y2 = float(input("Ingresa el valor para y2: "))
b2 = float(input("Ingresa el valor para el término independiente 2: "))
print()

# Generamos los labels para las ecuaciones.
label_ecuacion_1 = "(" + str(x1) + ")x + (" + str(y1) + ")y = " + str(b1)
label_ecuacion_1_para_y = "y = (" + str(b1) + " - (" + str(x1) +  ")x) / " + str(y1)
label_ecuacion_2 = "(" + str(x2) + ")x + (" + str(y2) + ")y = " + str(b2)
label_ecuacion_2_para_y = "y = (" + str(b2) + " - (" + str(x2) +  ")x) / " + str(y2)

# Mostramos las ecuaciones leídas.
print("Sistema de ecuaciones leído:")
print("Ecuación 1: " + label_ecuacion_1)
print("Ecuación 2: " + label_ecuacion_2)
print()

# Formamos la matriz extendida.
matriz_extendida = [
	[x1, y1, b1],
	[x2, y2, b2]
]

# La matriz de coeficientes es la matriz extendida sin la última columna.
print("Matriz de Coeficientes Original (A):")
imprimir_matriz(matriz_extendida, 2, 2)

print("Matriz Extendida Original (A*):")
imprimir_matriz(matriz_extendida, 2, 3)

# Copiamos la matriz extendida original.
matriz_diagonalizada = matriz_extendida

# Proceso de diagonalización fijo.

# Primero hacemos 1 el valor en A*_{11}
if matriz_extendida[0][0] != -1 and matriz_extendida[0][0] != 1:
	constante = 1 / matriz_extendida[0][0]

	matriz_diagonalizada[0][0] = constante * matriz_extendida[0][0]
	matriz_diagonalizada[0][1] = constante * matriz_extendida[0][1]
	matriz_diagonalizada[0][2] = constante * matriz_extendida[0][2]


# Ahora hacemos 0 el valor en A*_{21}
temporal = matriz_extendida[1][0] * -1

# En caso de que la primer suma no resulte en cero, es porque el valor temporal debe ser cambiado de signo.
if ((matriz_diagonalizada[0][0] * temporal) + matriz_extendida[1][0]) != 0:
	temporal = temporal * -1

# Operación en toda la fila.
matriz_diagonalizada[1][0] = (matriz_diagonalizada[0][0] * temporal) + matriz_extendida[1][0]
matriz_diagonalizada[1][1] = (matriz_diagonalizada[0][1] * temporal) + matriz_extendida[1][1]
matriz_diagonalizada[1][2] = (matriz_diagonalizada[0][2] * temporal) + matriz_extendida[1][2]

# Imprimir resultados.
print("Matriz Diagonalizada:")
imprimir_matriz(matriz_diagonalizada, 2, 3)

# Calculamos los rangos de las matrices.
rango_matriz_extendida  = rango_matriz(matriz_diagonalizada, 2, 3)
rango_matriz_coeficientes = rango_matriz(matriz_diagonalizada, 2, 2)

# Fijo.
numero_incognitas = 2; # :O 

# Imprimimos datos.
print("Datos relevantes:")
print("  ~ Rango matriz coeficientes R(A): " + str(rango_matriz_coeficientes))
print("  ~ Rango matriz extendida R(A*): " + str(rango_matriz_extendida))
print("  ~ Número de incógnitas: " + str(numero_incognitas))
print()

print("Conclusión final:")

# Concluyendo usando la variable A_{22}.

# Asumimos que no existen soluciones.
solucion_x = None
solucion_y = None

# El último valor de la diagonal en la matriz diagonalizada.
ultimo_valor_diagonal = matriz_diagonalizada[1][1]

# El útlimo término independiente de la matriz diagonalizada.
b2_diagonal = matriz_diagonalizada[1][2]

# Caso dónde no existe solución.
if ultimo_valor_diagonal == 0 and b2_diagonal != 0:
	print("  ~ El sistema no tiene solución (A_{22}=" + str(ultimo_valor_diagonal) + "; b_{2}=" + str(b2_diagonal) + "; A_{22} es cero y b2 es distinto a 0).")
	pass
# Caso dónde el sistema tiene una solución puntual.
elif ultimo_valor_diagonal != 0:
	print("  ~ El sistema tiene solución única (A_{22}=" + str(ultimo_valor_diagonal) + " no es igual a cero).")

	# Usamos coeficientes de matriz diagonalizada.
	solucion_y = b2_diagonal / ultimo_valor_diagonal

	# Sustituímos en la primer ecuación.
	solucion_x = ((solucion_y * y1) * -1) + b1
	
	# Mostrar solución.
	print("  ~ Solución para x: " + str(solucion_x))
	print("  ~ Solución para y: " + str(solucion_y))
	pass
# Caso dónde se tiene una infinidad de soluciones.
else:
	print("  ~ El sistema tiene infinidad de soluciones.")

# Concluyendo usando el teorema de Rouché-Fröbenius.
# if (rango_matriz_extendida != rango_matriz_coeficientes):
# 	print("  ~ El sistema no tiene solución (Los rangos son distintos: R(A)=" + str(rango_matriz_extendida) + " diferente de R(A*)=" + str(rango_matriz_coeficientes) + ").")
# 	pass
# else:
# 	if rango_matriz_extendida == numero_incognitas:
# 		print("  ~ El sistema tiene solución única (Los rangos son iguales al número de incógnitas: R(A)=" + str(rango_matriz_coeficientes) + " igual a R(A*)=" + str(rango_matriz_extendida) + " igual al número de incógnitas (" + str(numero_incognitas) + ")).")

# 		# TODO: Mostrar solución.
# 		print("  ~ Solución para x: ")
# 		print("  ~ Solución para y: ")
# 	else:
# 		print("  ~ El sistema tiene infinidad de soluciones (Los rangos son iguales, R(A)=" + str(rango_matriz_coeficientes) + " igual a R(A*)=" + str(rango_matriz_extendida) + ", pero menores al número de incógnitas (2)) .")

# Salto de línea al final del mensaje de conclusión.
print()

# Proceso para mostrar las gráficas.
input("Presione ENTER para mostrar las gráficas de las ecuaciones...")
print("¡Mostrando gráficas de las ecuaciones en la ventana emergente!")

# Asumimos un rango de x para graficar de [-5, 5] y profundidad de 100 (no utilizado).
x = np.linspace(-5,5,100)

# Si tuvimos solución puntual, calculamos el rango a x - 5 y x + 5.
if(not(solucion_x is None) and not(solucion_y is None)):
	x = np.linspace(solucion_x - 5, solucion_x + 5, 100)

# Añadimos las ecuaciones a nuestro "plot".
plt.plot(x, (b1 - (x1 * x)) / y1, '-r', label=label_ecuacion_1_para_y)
plt.plot(x, (b2 - (x2 * x)) / y2, '-b', label=label_ecuacion_2_para_y)

# Configuración final y mostrar gráfica.
plt.legend(loc='upper left')
plt.show()

# Mensaje final.
print ("¡Fin de ejecución!")
