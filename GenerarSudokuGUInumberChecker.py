from tkinter import Entry, Tk, Button, END, messagebox
from random import shuffle
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas

N = 9  # Tamaño del Sudoku

# Función para verificar si es válido colocar un número en una posición
def es_valido(tablero, fila, col, num):
    for x in range(N):
        if tablero[fila][x] == num or tablero[x][col] == num:
            return False

    inicio_fila, inicio_col = fila - fila % 3, col - col % 3
    for i in range(3):
        for j in range(3):
            if tablero[i + inicio_fila][j + inicio_col] == num:
                return False
    return True

# Generador de Sudoku con backtracking
def resolver_sudoku(tablero):
    for fila in range(N):
        for col in range(N):
            if tablero[fila][col] == 0:
                numeros_posibles = [num for num in range(1, 10) if es_valido(tablero, fila, col, num)]
                shuffle(numeros_posibles)

                for num in numeros_posibles:
                    tablero[fila][col] = num
                    if resolver_sudoku(tablero):
                        return True
                    tablero[fila][col] = 0
                return False
    return True

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

# Función para cargar el Sudoku generado en la interfaz
def cargar_sudoku(tablero, entradas):
    for i in range(N):
        for j in range(N):
            if tablero[i][j] != 0:
                entradas[i][j].delete(0, END)
                entradas[i][j].insert(0, str(tablero[i][j]))
                entradas[i][j].config(state='disabled')  # Deshabilitar la celda si ya tiene un número
            else:
                entradas[i][j].config(state='normal')
                entradas[i][j].delete(0, END)

# Función para obtener el Sudoku desde la interfaz
def obtener_sudoku(entradas):
    tablero = []
    for i in range(N):
        fila = []
        for j in range(N):
            valor = entradas[i][j].get()
            if valor == "":
                fila.append(0)
            else:
                fila.append(int(valor))
        tablero.append(fila)
    return tablero

# Función para resolver el Sudoku y mostrar el resultado
def resolver_desde_interfaz(entradas):
    tablero = obtener_sudoku(entradas)
    if resolver_sudoku(tablero):
        cargar_sudoku(tablero, entradas)
    else:
        messagebox.showerror("Error", "No se puede resolver el Sudoku.")

# Función para verificar si la solución del usuario es correcta
def verificar_sudoku(entradas, tablero_original):
    tablero_usuario = obtener_sudoku(entradas)
    for i in range(N):
        for j in range(N):
            if tablero_usuario[i][j] != tablero_original[i][j] and tablero_original[i][j] != 0:
                messagebox.showerror("Error", "El Sudoku no es correcto.")
                return
    messagebox.showinfo("Éxito", "¡El Sudoku está correctamente resuelto!")

# Función para generar el PDF
def generar_pdf(tablero):
    c = canvas.Canvas("sudoku.pdf", pagesize=letter)
    width, height = letter

    # Títulos
    c.setFont("Helvetica-Bold", 24)  # Aumentar el tamaño de la fuente
    c.drawString(100, height - 50, "Sudoku Generado")

    # Tamaño de la celda y posiciones iniciales
    cell_size = 40  # Aumentar el tamaño de cada celda
    x_start = 100
    y_start = height - 100

    # Dibujar el Sudoku con cuadrículas
    for i in range(N):
        for j in range(N):
            # Dibujar el número en la celda
            if tablero[i][j] != 0:
                c.setFont("Helvetica", 18)  # Ajustar el tamaño de la fuente para los números
                c.drawString(x_start + j * cell_size + 10, y_start - i * cell_size - 30, str(tablero[i][j]))

            # Dibujar líneas de cuadrícula
            c.rect(x_start + j * cell_size, y_start - i * cell_size - cell_size, cell_size, cell_size)

    # Dibujar líneas más gruesas para separar las secciones 3x3
    for i in range(1, N):
        if i % 3 == 0:  # Cada 3 filas y columnas
            c.setLineWidth(2)
            c.line(x_start + i * cell_size, y_start, x_start + i * cell_size, y_start - N * cell_size)
            c.line(x_start, y_start - i * cell_size, x_start + N * cell_size, y_start - i * cell_size)
            c.setLineWidth(1)  # Restablecer el grosor de la línea

    c.save()
    messagebox.showinfo("PDF Generado", "El PDF del Sudoku ha sido creado con éxito.")

# Función para verificar el número ingresado en tiempo real
def verificar_numero(event, fila, col, entradas, tablero_original):
    valor = entradas[fila][col].get()
    if valor.isdigit() and int(valor) != tablero_original[fila][col]:
        entradas[fila][col].config(fg="red")
    else:
        entradas[fila][col].config(fg="black")

# Interfaz gráfica con Tkinter
def main():
    ventana = Tk()
    ventana.title("Sudoku Solver")
    ventana.configure(bg='black')  # Fondo negro para la ventana

    # Crear la cuadrícula de entradas de texto (9x9)
    entradas = []
    tablero = []
    for i in range(N):
        fila = []
        for j in range(N):
            entrada = Entry(ventana, width=3, justify='center', font=('Arial', 18), bd=2, relief="solid", bg='white', fg='black')
            entrada.grid(row=i, column=j, padx=1, pady=1)
            entrada.bind("<KeyRelease>", lambda event, fila=i, col=j: verificar_numero(event, fila, col, entradas, tablero))
            fila.append(entrada)
        entradas.append(fila)

    # Crear botones
    btn_generar_facil = Button(ventana, text="Generar Sudoku fácil", command=lambda: generar_sudoku_facil(tablero) or cargar_sudoku(tablero, entradas))
    btn_generar_facil.grid(row=N, column=0, columnspan=4, pady=10)
    btn_generar_medio = Button(ventana, text="Generar Sudoku medio", command=lambda: generar_sudoku_medio(tablero) or cargar_sudoku(tablero, entradas))
    btn_generar_medio.grid(row=N, column=3, columnspan=4, pady=10)
    btn_generar_dificil = Button(ventana, text="Generar Sudoku difícil", command=lambda: generar_sudoku_dificil(tablero) or cargar_sudoku(tablero, entradas))
    btn_generar_dificil.grid(row=N, column=7, columnspan=4, pady=10)

    btn_resolver = Button(ventana, text="Resolver Sudoku", command=lambda: resolver_desde_interfaz(entradas))
    btn_resolver.grid(row=N + 1, column=7, columnspan=4, pady=10)

    btn_verificar = Button(ventana, text="Verificar Sudoku", command=lambda: verificar_sudoku(entradas, tablero))
    btn_verificar.grid(row=N + 1, column=0, columnspan=4, pady=10)

    btn_generar_pdf = Button(ventana, text="Generar PDF", command=lambda: generar_pdf(tablero))
    btn_generar_pdf.grid(row=N + 1, column=4, columnspan=4, pady=10)

    ventana.mainloop()

if __name__ == "__main__":
    main()
