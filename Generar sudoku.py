from random import shuffle

N = 9

# Función para verificar si es válido colocar un número en una posición
def es_valido(tablero, fila, col, num):
    # Verificar fila
    for x in range(N):
        if tablero[fila][x] == num:
            return False

    # Verificar columna
    for x in range(N):
        if tablero[x][col] == num:
            return False

    # Verificar subcuadro 3x3
    inicio_fila = fila - fila % 3
    inicio_col = col - col % 3

    for i in range(3):
        for j in range(3):
            if tablero[i + inicio_fila][j + inicio_col] == num:
                return False

    return True

# Generador de Sudoku con backtracking
def resolver_sudoku(tablero):
    for fila in range(N):
        for col in range(N):
            if tablero[fila][col] == 0:  # Si la celda está vacía
                numeros_posibles = []
                for num in range(1, 10):
                    if es_valido(tablero, fila, col, num):
                        numeros_posibles.append(num)

                shuffle(numeros_posibles)  # Mezclar las opciones aleatorias

                for num in numeros_posibles:
                    tablero[fila][col] = num
                    if resolver_sudoku(tablero):
                        return True
                    tablero[fila][col] = 0  # Si no es posible, backtrack
                return False  # Si no es posible colocar ningún número
    return True  # Sudoku resuelto


# Función para imprimir el Sudoku
def imprimir_sudoku(tablero):
    for fila in tablero:
        print(" ".join(str(num) for num in fila))

# Funciones para generar Sudoku de diferentes niveles (fácil, medio, difícil)
def generar_sudoku(tablero, eliminados):
    for i in range(N):
        tablero.append([0] * N)

    if not resolver_sudoku(tablero):
        raise RuntimeError("Error al generar el Sudoku")

    celdas = [(i, j) for i in range(N) for j in range(N)]
    shuffle(celdas)

    for i in range(eliminados):
        fila, col = celdas[i]
        tablero[fila][col] = 0

# Funciones específicas de dificultad
def generar_sudoku_facil(tablero):
    generar_sudoku(tablero, 40)

def generar_sudoku_medio(tablero):
    generar_sudoku(tablero, 50)

def generar_sudoku_dificil(tablero):
    generar_sudoku(tablero, 57)


# Función principal
def main():
    sudoku = []
    exit_program = 'S'

    print("-------------------- Generador y resolutor de sudokus --------------------")

    while exit_program.lower() != 'n':
        print("Selecciona una opción")
        print("1.- Generar sudoku")
        print("2.- Resolver sudoku")

        try:
            opcion = int(input("Tu elección: "))
        except ValueError:
            print("Error: debes ingresar un número válido.")
            continue

        if opcion == 1:
            print("¿Qué dificultad quieres para el sudoku?")
            print("1.- Fácil")
            print("2.- Medio")
            print("3.- Díficil")
            try:
                opcion = int(input("Tu elección: "))
            except ValueError:
                print("Error: debes ingresar un número válido.")
                continue

            if opcion == 1:
                # Generar Sudoku
                generar_sudoku_facil(sudoku)
                # Imprimir el Sudoku generado
                print("Sudoku generado: ")
                imprimir_sudoku(sudoku)
            elif opcion == 2:
                # Generar Sudoku
                generar_sudoku_medio(sudoku)
                # Imprimir el Sudoku generado
                print("Sudoku generado: ")
                imprimir_sudoku(sudoku)
            elif opcion == 3:
                # Generar Sudoku
                generar_sudoku_dificil(sudoku)
                # Imprimir el Sudoku generado
                print("Sudoku generado: ")
                imprimir_sudoku(sudoku)
            else:
                print(f"La opción {opcion} no existe")

        elif opcion == 2:
            print("Inserción de números en el sudoku")
            for i in range(N):
                for j in range(N):
                    input_correcto = False
                    while not input_correcto:
                        try:
                            num = int(input(f"Inserta el elemento {i + 1},{j + 1}: "))

                            if num < 1 or num > 9:
                                print("Error: El número debe estar entre 1 y 9.")
                                continue

                            sudoku[i][j] = num
                            error = input("¿El número es correcto? S/N: ").lower()
                            if error == 's':
                                input_correcto = True  # Salir del bucle si el número es correcto
                            else:
                                raise ValueError("El número no es correcto, vuelve a intentarlo.")
                        except ValueError as e:
                            print(e)

        else:
            print(f"La opción {opcion} no existe, por favor verifícala.")

        exit_program = input("¿Quieres seguir? S/N: ")

    print("Programa terminado.")

if __name__ == "__main__":
    main()
