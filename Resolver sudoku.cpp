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

random_device rd;  // Semilla para el generador de n�meros aleatorios
mt19937 gen(rd()); // Generador de n�meros aleatorios
uniform_int_distribution<> distrib(1, 9);  // Distribuci�n para n�meros entre 1 y 9
uniform_int_distribution<> distribPos(0, N - 1);  // Distribuci�n para posiciones entre 0 y N-1

// Funci�n para verificar si es v�lido colocar un n�mero en una posici�n
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

// Generador de Sudoku con backtracking, pero m�s din�mico con aleatorizaci�n
bool resolverSudoku(vector<vector<int>>& tablero) {
	// Intentar colocar n�meros en todas las celdas vac�as, aleatoriamente.
	for (int fila = 0; fila < N; fila++) {
		for (int col = 0; col < N; col++) {
			if (tablero[fila][col] == 0) {  // Si la celda est� vac�a
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
				return false;  // Si no es posible colocar ning�n n�mero
			}
		}
	}
	return true;  // Sudoku resuelto
}

// Funci�n para imprimir el Sudoku
void imprimirSudoku(const vector<vector<int>>& tablero) {
	for (const auto& fila : tablero) {
		for (int num : fila) {
			cout << num << " ";
		}
		cout << endl;
	}
}

//Funci�n generar un sudoku f�cil
void generarSudokuFacil(vector<vector<int>>& tablero) {
	// Inicializar el tablero vac�o
	tablero.assign(N, vector<int>(N, 0));
	
	// Resolver el Sudoku (llenarlo completamente con un backtracking)
	if (!resolverSudoku(tablero)) {
		throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
	}
	
	// Eliminar algunos n�meros para hacerlo m�s desafiante
	int eliminados = 40;  // Eliminamos 40 celdas
	vector<pair<int, int>> celdas;
	
	// A�adir todas las celdas al vector
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			celdas.push_back({i, j});
		}
	}
	
	// Mezclar las celdas aleatoriamente
	shuffle(celdas.begin(), celdas.end(), gen);
	
	// Eliminar n�meros en celdas aleatorias usando el generador de n�meros aleatorios
	for (int i = 0; i < eliminados; ++i) {
		int fila = celdas[i].first;
		int col = celdas[i].second;
		tablero[fila][col] = 0;  // Eliminar el n�mero en la celda
	}
}

//Funci�n para generar un sudoku nivel medio
void generarSudokuMedio(vector<vector<int>>& tablero) {
	// Inicializar el tablero vac�o
	tablero.assign(N, vector<int>(N, 0));
	
	// Resolver el Sudoku (llenarlo completamente con un backtracking)
	if (!resolverSudoku(tablero)) {
		throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
	}
	
	// Eliminar algunos n�meros para hacerlo m�s desafiante
	int eliminados = 50;  // Eliminamos 50 celdas
	vector<pair<int, int>> celdas;
	
	// A�adir todas las celdas al vector
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			celdas.push_back({i, j});
		}
	}
	
	// Mezclar las celdas aleatoriamente
	shuffle(celdas.begin(), celdas.end(), gen);
	
	// Eliminar n�meros en celdas aleatorias usando el generador de n�meros aleatorios
	for (int i = 0; i < eliminados; ++i) {
		int fila = celdas[i].first;
		int col = celdas[i].second;
		tablero[fila][col] = 0;  // Eliminar el n�mero en la celda
	}
}

//Funci�n para generar un sudoku dificil
void generarSudokuDificil(vector<vector<int>>& tablero) {
	// Inicializar el tablero vac�o
	tablero.assign(N, vector<int>(N, 0));
	
	// Resolver el Sudoku (llenarlo completamente con un backtracking)
	if (!resolverSudoku(tablero)) {
		throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
	}
	
	// Eliminar algunos n�meros para hacerlo m�s desafiante
	int eliminados = 57;  // Eliminamos 57 celdas
	vector<pair<int, int>> celdas;
	
	// A�adir todas las celdas al vector
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			celdas.push_back({i, j});
		}
	}
	
	// Mezclar las celdas aleatoriamente
	shuffle(celdas.begin(), celdas.end(), gen);
	
	// Eliminar n�meros en celdas aleatorias usando el generador de n�meros aleatorios
	for (int i = 0; i < eliminados; ++i) {
		int fila = celdas[i].first;
		int col = celdas[i].second;
		tablero[fila][col] = 0;  // Eliminar el n�mero en la celda
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "spanish");
	vector<vector<int>> sudoku(N, vector<int>(N));
	int opc = 0;
	char exit = 'S', error = 'S';
	
	cout << "-------------------- Generador y resolutor de sudokus --------------------" << endl;
	
	while (exit != 'N' && exit != 'n') {
		cout << "Selecciona una opci�n" << endl;
		cout << "1.- Generar sudoku" << endl;
		cout << "2.- Resolver sudoku" << endl;
		
		try {
			cout << "Tu elecci�n: ";
			cin >> opc;
			
			// Verificar si la entrada fue v�lida
			if (cin.fail()) {
				throw invalid_argument("Error: debes ingresar un n�mero v�lido.");
			}
			
		} catch (const invalid_argument& e) {
			cout << e.what() << endl;
			cin.clear();  // Limpiar el estado de error
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar el resto de la entrada
			continue;  // Repetir el bucle
		}
		
		switch (opc) {
		case 1:
			cout << "�Qu� dificultad quieres para el sudoku?" << endl;
			cout << "1.- F�cil" << endl;
			cout << "2.- Medio" << endl;
			cout << "3.- D�ficil" << endl;
			try {
				cout << "Tu elecci�n: ";
				cin >> opc;
				
				// Verificar si la entrada fue v�lida
				if (cin.fail()) {
					throw invalid_argument("Error: debes ingresar un n�mero v�lido.");
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
					cout << "La opci�n " << opc << " no existe, por favor verif�cala" << endl;
					break;
			}
			break;
			
		case 2:
			cout << "Inserci�n de n�meros en el sudoku" << endl;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					int num = 0;
					bool input_correct = false;
					while (!input_correct) {
						cout << "Inserta el elemento " << i + 1 << "," << j + 1 << ": ";
						cin >> num;
						
						try {
							// Verificar si la entrada es un n�mero v�lido
							if (cin.fail()) {
								throw invalid_argument("Error: debes insertar un n�mero v�lido.");
							}
							
							// Asignar el n�mero al sudoku
							sudoku[i][j] = num;
							
							// Verificar si el n�mero fue insertado correctamente
							cout << "�El n�mero es correcto? S/N: ";
							cin >> error;
							
							if (error == 'S' || error == 's') {
								input_correct = true;  // Salir del bucle si el n�mero es correcto
							} else {
								throw invalid_argument("El n�mero no es correcto, vuelve a intentarlo.");
							}
						} catch (const invalid_argument& e) {
							cout << e.what() << endl;
							cin.clear();  // Limpiar el estado de error
							cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar la entrada inv�lida
						}
					}
				}
			}
			break;
			
		default:
			cout << "La opci�n " << opc << " no existe, por favor verif�cala" << endl;
			break;
		}
		
		cout << "�Quieres seguir? S/N" << endl;
		cout << "Tu elecci�n: ";
		cin >> exit;
		
		// Si la entrada para 'exit' no es v�lida, terminamos el programa
		if (cin.fail() || (exit != 'S' && exit != 's' && exit != 'N' && exit != 'n')) {
			cout << "Entrada inv�lida. Terminando el programa." << endl;
			break;
		}
	}
	
	cout << "Presiona una tecla para continuar..." << endl;
	_getch();
	
	return 0;
}

// Funci�n para generar un Sudoku aleatorio, con eliminaci�n de celdas
/*void generarSudoku(vector<vector<int>>& tablero) {
// Inicializar el tablero vac�o
tablero.assign(N, vector<int>(N, 0));

// Resolver el Sudoku (llenarlo completamente con un backtracking)
if (!resolverSudoku(tablero)) {
throw runtime_error("Error al generar el Sudoku: No se pudo resolver.");
}

// Eliminar algunos n�meros para hacerlo m�s desafiante
int eliminados = 40 + distrib(gen) % 11;  // Eliminamos entre 40 y 50 celdas
vector<pair<int, int>> celdas;

// A�adir todas las celdas al vector
for (int i = 0; i < N; ++i) {
for (int j = 0; j < N; ++j) {
celdas.push_back({i, j});
}
}

// Mezclar las celdas aleatoriamente
shuffle(celdas.begin(), celdas.end(), gen);

// Eliminar n�meros en celdas aleatorias usando el generador de n�meros aleatorios
for (int i = 0; i < eliminados; ++i) {
int fila = celdas[i].first;
int col = celdas[i].second;
tablero[fila][col] = 0;  // Eliminar el n�mero en la celda
}
}*/
