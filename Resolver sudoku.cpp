#include <iostream>
#include <locale>
#include <conio.h>
#include <random>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <limits>
#include <algorithm>

using namespace std;

const int N = 9;

random_device rd;  // Semilla para el generador de números aleatorios
mt19937 gen(rd()); // Generador de números aleatorios
uniform_int_distribution<> distrib(1, 9);  // Distribución para números entre 1 y 9
uniform_int_distribution<> distribPos(0, N - 1);  // Distribución para posiciones entre 0 y N-1

// Función para verificar si es válido colocar un número en una posición
bool esValido(const vector<vector<int>>& tablero, int fila, int col, int num) {
	// Verificar fila
	for (int x = 0; x < N; x++) {
		if (tablero[fila][x] == num) {
			return false;
		}
	}
	
	// Verificar columna
	for (int x = 0; x < N; x++) {
		if (tablero[x][col] == num) {
			return false;
		}
	}
	
	// Verificar subcuadro 3x3
	int inicioFila = fila - fila % 3;
	int inicioCol = col - col % 3;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tablero[i + inicioFila][j + inicioCol] == num) {
				return false;
			}
		}
	}
	
	return true;
}

// Generador de Sudoku con backtracking, pero más dinámico con aleatorización
bool resolverSudoku(vector<vector<int>>& tablero) {
	// Intentar colocar números en todas las celdas vacías, aleatoriamente.
	for (int fila = 0; fila < N; fila++) {
		for (int col = 0; col < N; col++) {
			if (tablero[fila][col] == 0) {  // Si la celda está vacía
				vector<int> posibles;
				for (int num = 1; num <= 9; num++) {
					if (esValido(tablero, fila, col, num)) {
						posibles.push_back(num);
					}
				}
				
				shuffle(posibles.begin(), posibles.end(), gen);  // Mezclar las opciones aleatorias
				
				for (int num : posibles) {
					tablero[fila][col] = num;
					if (resolverSudoku(tablero)) {
						return true;
					}
					tablero[fila][col] = 0;  // Si no es posible, backtrack
				}
				return false;  // Si no es posible colocar ningún número
			}
		}
	}
	return true;  // Sudoku resuelto
}

// Función para imprimir el Sudoku
void imprimirSudoku(const vector<vector<int>>& tablero) {
	for (const auto& fila : tablero) {
		for (int num : fila) {
			cout << num << " ";
		}
		cout << endl;
	}
}

//Función generar un sudoku fácil
void generarSudokuFacil(vector<vector<int>>& tablero) {
	// Inicializar el tablero vacío
	tablero.assign(N, vector<int>(N, 0));
	
	// Resolver el Sudoku (llenarlo completamente con un backtracking)
	if (!resolverSudoku(tablero)) {
		throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
	}
	
	// Eliminar algunos números para hacerlo más desafiante
	int eliminados = 40;  // Eliminamos 40 celdas
	vector<pair<int, int>> celdas;
	
	// Añadir todas las celdas al vector
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			celdas.push_back({i, j});
		}
	}
	
	// Mezclar las celdas aleatoriamente
	shuffle(celdas.begin(), celdas.end(), gen);
	
	// Eliminar números en celdas aleatorias usando el generador de números aleatorios
	for (int i = 0; i < eliminados; ++i) {
		int fila = celdas[i].first;
		int col = celdas[i].second;
		tablero[fila][col] = 0;  // Eliminar el número en la celda
	}
}

//Función para generar un sudoku nivel medio
void generarSudokuMedio(vector<vector<int>>& tablero) {
	// Inicializar el tablero vacío
	tablero.assign(N, vector<int>(N, 0));
	
	// Resolver el Sudoku (llenarlo completamente con un backtracking)
	if (!resolverSudoku(tablero)) {
		throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
	}
	
	// Eliminar algunos números para hacerlo más desafiante
	int eliminados = 50;  // Eliminamos 50 celdas
	vector<pair<int, int>> celdas;
	
	// Añadir todas las celdas al vector
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			celdas.push_back({i, j});
		}
	}
	
	// Mezclar las celdas aleatoriamente
	shuffle(celdas.begin(), celdas.end(), gen);
	
	// Eliminar números en celdas aleatorias usando el generador de números aleatorios
	for (int i = 0; i < eliminados; ++i) {
		int fila = celdas[i].first;
		int col = celdas[i].second;
		tablero[fila][col] = 0;  // Eliminar el número en la celda
	}
}

//Función para generar un sudoku dificil
void generarSudokuDificil(vector<vector<int>>& tablero) {
	// Inicializar el tablero vacío
	tablero.assign(N, vector<int>(N, 0));
	
	// Resolver el Sudoku (llenarlo completamente con un backtracking)
	if (!resolverSudoku(tablero)) {
		throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
	}
	
	// Eliminar algunos números para hacerlo más desafiante
	int eliminados = 57;  // Eliminamos 57 celdas
	vector<pair<int, int>> celdas;
	
	// Añadir todas las celdas al vector
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			celdas.push_back({i, j});
		}
	}
	
	// Mezclar las celdas aleatoriamente
	shuffle(celdas.begin(), celdas.end(), gen);
	
	// Eliminar números en celdas aleatorias usando el generador de números aleatorios
	for (int i = 0; i < eliminados; ++i) {
		int fila = celdas[i].first;
		int col = celdas[i].second;
		tablero[fila][col] = 0;  // Eliminar el número en la celda
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "spanish");
	vector<vector<int>> sudoku(N, vector<int>(N));
	int opc = 0;
	char exit = 'S', error = 'S';
	
	cout << "-------------------- Generador y resolutor de sudokus --------------------" << endl;
	
	while (exit != 'N' && exit != 'n') {
		cout << "Selecciona una opción" << endl;
		cout << "1.- Generar sudoku" << endl;
		cout << "2.- Resolver sudoku" << endl;
		
		try {
			cout << "Tu elección: ";
			cin >> opc;
			
			// Verificar si la entrada fue válida
			if (cin.fail()) {
				throw invalid_argument("Error: debes ingresar un número válido.");
			}
			
		} catch (const invalid_argument& e) {
			cout << e.what() << endl;
			cin.clear();  // Limpiar el estado de error
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar el resto de la entrada
			continue;  // Repetir el bucle
		}
		
		switch (opc) {
		case 1:
			cout << "¿Qué dificultad quieres para el sudoku?" << endl;
			cout << "1.- Fácil" << endl;
			cout << "2.- Medio" << endl;
			cout << "3.- Díficil" << endl;
			try {
				cout << "Tu elección: ";
				cin >> opc;
				
				// Verificar si la entrada fue válida
				if (cin.fail()) {
					throw invalid_argument("Error: debes ingresar un número válido.");
				}
				
			} catch (const invalid_argument& e) {
				cout << e.what() << endl;
				cin.clear();  // Limpiar el estado de error
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar el resto de la entrada
				continue;  // Repetir el bucle
			}
			
			switch(opc){
				case 1:
					// Imprimir el Sudoku generado
					cout << "Sudoku generado: " << endl;
					generarSudokuFacil(sudoku);
					imprimirSudoku(sudoku);
					break;
				
				case 2:
					// Imprimir el Sudoku generado
					cout << "Sudoku generado: " << endl;
					generarSudokuMedio(sudoku);
					imprimirSudoku(sudoku);
					break;
				
				case 3:
					// Imprimir el Sudoku generado
					cout << "Sudoku generado: " << endl;
					generarSudokuDificil(sudoku);
					imprimirSudoku(sudoku);
					break;
				
				default:
					cout << "La opción " << opc << " no existe, por favor verifícala" << endl;
					break;
			}
			break;
			
		case 2:
			cout << "Inserción de números en el sudoku" << endl;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					int num = 0;
					bool input_correct = false;
					while (!input_correct) {
						cout << "Inserta el elemento " << i + 1 << "," << j + 1 << ": ";
						cin >> num;
						
						try {
							// Verificar si la entrada es un número válido
							if (cin.fail()) {
								throw invalid_argument("Error: debes insertar un número válido.");
							}
							
							// Asignar el número al sudoku
							sudoku[i][j] = num;
							
							// Verificar si el número fue insertado correctamente
							cout << "¿El número es correcto? S/N: ";
							cin >> error;
							
							if (error == 'S' || error == 's') {
								input_correct = true;  // Salir del bucle si el número es correcto
							} else {
								throw invalid_argument("El número no es correcto, vuelve a intentarlo.");
							}
						} catch (const invalid_argument& e) {
							cout << e.what() << endl;
							cin.clear();  // Limpiar el estado de error
							cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar la entrada inválida
						}
					}
				}
			}
			break;
			
		default:
			cout << "La opción " << opc << " no existe, por favor verifícala" << endl;
			break;
		}
		
		cout << "¿Quieres seguir? S/N" << endl;
		cout << "Tu elección: ";
		cin >> exit;
		
		// Si la entrada para 'exit' no es válida, terminamos el programa
		if (cin.fail() || (exit != 'S' && exit != 's' && exit != 'N' && exit != 'n')) {
			cout << "Entrada inválida. Terminando el programa." << endl;
			break;
		}
	}
	
	cout << "Presiona una tecla para continuar..." << endl;
	_getch();
	
	return 0;
}

// Función para generar un Sudoku aleatorio, con eliminación de celdas
/*void generarSudoku(vector<vector<int>>& tablero) {
// Inicializar el tablero vacío
tablero.assign(N, vector<int>(N, 0));

// Resolver el Sudoku (llenarlo completamente con un backtracking)
if (!resolverSudoku(tablero)) {
throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
}

// Eliminar algunos números para hacerlo más desafiante
int eliminados = 40 + distrib(gen) % 11;  // Eliminamos entre 40 y 50 celdas
vector<pair<int, int>> celdas;

// Añadir todas las celdas al vector
for (int i = 0; i < N; ++i) {
for (int j = 0; j < N; ++j) {
celdas.push_back({i, j});
}
}

// Mezclar las celdas aleatoriamente
shuffle(celdas.begin(), celdas.end(), gen);

// Eliminar números en celdas aleatorias usando el generador de números aleatorios
for (int i = 0; i < eliminados; ++i) {
int fila = celdas[i].first;
int col = celdas[i].second;
tablero[fila][col] = 0;  // Eliminar el número en la celda
}
}*/
