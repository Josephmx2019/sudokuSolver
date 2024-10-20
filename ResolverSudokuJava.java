import java.util.*;

public class ResolverSudokuJava{
    public static int N (){
        return 9;
    }

    // Generador de números aleatorios
    public Random gen = new Random();  // Puedes pasar una semilla si es necesario: new Random(seed)

    // Distribución para números entre 1 y 9
    public int randomNum = gen.nextInt(9) + 1;  // Genera un número entre 1 y 9 (inclusive)

    // Distribución para posiciones entre 0 y N-1
    public int randomPos = gen.nextInt(N());  // Genera un número entre 0 y N-1

    public static boolean esValido(ArrayList <ArrayList<Integer>> tablero, int fila, int col, int num){
        // verificar fila
        for (int x = 0; x < N(); x ++){
            if (tablero.get(fila).get(x) == num){
                return false;
            }
        }

        // verificar columna
        for (int x = 0; x < N(); x ++){
            if (tablero.get(x).get(col) == num){
                return false;
            }
        }

        // verificar subcuadro 3x3
        int inicioFila = fila - fila%3;
        int inicioCol = col - col%3;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (tablero.get(i+inicioFila).get(j+inicioCol) == num){
                    return false;
                }
            }
        }

        return true;
    }

    // Generador de Sudoku con backtracking
    public static boolean resolverSudoku(ArrayList<ArrayList<Integer>> tablero){
        // intentar colocar números en todas las celdas vacías
        for (int fila = 0; fila < N(); fila ++){
            for (int col = 0; col < N(); col ++){
                if (tablero.get(fila).get(col) == 0){ // si la celda está vacia
                    ArrayList<Integer> posibles = new ArrayList<>();
                    for (int num = 1; num < 10; num ++){
                        if (esValido(tablero, fila, col, num)){
                            posibles.add(num);
                        }
                    }

                    Collections.shuffle(posibles); // mezclar las opciones aleatorias

                    for (int num : posibles){
                        tablero.get(fila).set(col,num);
                        if (resolverSudoku(tablero)){
                            return true;
                        }
                        tablero.get(fila).set(col,0); // si no es posible backtrack
                    }
                    return false; // si no es posible colocar ningún número
                }
            }
        }
        return true; // sudoku resuelto
    }
    
    // Función para imprimir sudoku
    public static void imprimirSudoku(ArrayList<ArrayList<Integer>> tablero){
        for (ArrayList<Integer> fila : tablero){
            for (int num : fila){
                System.out.print(num + " ");
            }
            System.out.println("\n");
        }
    }

    // Función para inicializar el tablero
    public static void inicializarTablero(ArrayList<ArrayList<Integer>> tablero) {
        for (int i = 0; i < N(); i++) {
            ArrayList<Integer> fila = new ArrayList<>();
            for (int j = 0; j < N(); j++) {
                fila.add(0);  // Añadir 0 a cada columna
            }
            tablero.add(fila);  // Añadir la fila al tablero
        }
    }
    
    // Función para generar un sudoku facil
    public static void generarSudokuFacil(ArrayList<ArrayList<Integer>> tablero){
        // Inicializar el tablero vacío
        inicializarTablero(tablero);

        // Resolver el sudoku (llenarlo completamente con un backtracking)
        if (!resolverSudoku(tablero)){
            throw new RuntimeException("Error al generar el Sudoku: No se pudo resolver.");
        }

        // Eliminar algunos números 
        int eliminados = 40;
        ArrayList<Map.Entry<Integer,Integer>> celdas = new ArrayList<>();

        // Añadir las celdas al ArrayList
        for (int i = 0; i < N(); i ++){
            for (int j = 0 ; j < N(); j++){
                celdas.add(new AbstractMap.SimpleEntry<>(i,j));
            }
        }

        // Mezclar las celdas aleatoriamente
        Collections.shuffle(celdas);

        // Eliminar números en celdas aleatorias usando el generador de números aleatorios
        for (int i = 0; i < eliminados; i++){
            int fila = celdas.get(i).getKey();
            int col = celdas.get(i).getValue();
            tablero.get(fila).set(col,0);
        }
    }

    // Función para generar un sudoku medio
    public static void generarSudokuMedio(ArrayList<ArrayList<Integer>> tablero){
        // Inicializar el tablero vacío
        inicializarTablero(tablero);

        // Resolver el sudoku (llenarlo completamente con un backtracking)
        if (!resolverSudoku(tablero)){
            throw new RuntimeException("Error al generar el Sudoku: No se pudo resolver.");
        }

        // Eliminar algunos números 
        int eliminados = 50;
        ArrayList<Map.Entry<Integer,Integer>> celdas = new ArrayList<>();

        // Añadir las celdas al ArrayList
        for (int i = 0; i < N(); i ++){
            for (int j = 0 ; j < N(); j++){
                celdas.add(new AbstractMap.SimpleEntry<>(i,j));
            }
        }

        // Mezclar las celdas aleatoriamente
        Collections.shuffle(celdas);

        // Eliminar números en celdas aleatorias usando el generador de números aleatorios
        for (int i = 0; i < eliminados; i++){
            int fila = celdas.get(i).getKey();
            int col = celdas.get(i).getValue();
            tablero.get(fila).set(col,0);
        }
    }

    // Función para generar un sudoku díficil
    public static void generarSudokuDificil(ArrayList<ArrayList<Integer>> tablero){
        // Inicializar el tablero vacío
        inicializarTablero(tablero);

        // Resolver el sudoku (llenarlo completamente con un backtracking)
        if (!resolverSudoku(tablero)){
            throw new RuntimeException("Error al generar el Sudoku: No se pudo resolver.");
        }

        // Eliminar algunos números 
        int eliminados = 57;
        ArrayList<Map.Entry<Integer,Integer>> celdas = new ArrayList<>();

        // Añadir las celdas al ArrayList
        for (int i = 0; i < N(); i ++){
            for (int j = 0 ; j < N(); j++){
                celdas.add(new AbstractMap.SimpleEntry<>(i,j));
            }
        }

        // Mezclar las celdas aleatoriamente
        Collections.shuffle(celdas);

        // Eliminar números en celdas aleatorias usando el generador de números aleatorios
        for (int i = 0; i < eliminados; i++){
            int fila = celdas.get(i).getKey();
            int col = celdas.get(i).getValue();
            tablero.get(fila).set(col,0);
        }
    }
    public static void main(String[] args) {
       ArrayList<ArrayList<Integer>> sudoku = new ArrayList<>();
       Scanner leer = new Scanner(System.in);
       int opc = 0;
       String exit = "S", error = "S";
       char fin = 'S';

        // Inicializar el tablero bidimensional de tamaño N x N con ceros
        inicializarTablero(sudoku);

        System.out.println("-------------------- Generador y resolutor de sudokus --------------------");
        while(fin != 'N' && fin != 'n'){
            System.out.println("Selecciona una opción");
            System.out.println("1.- Generar sudoku");
            System.out.println("2.- Resolver sudoku");
            try {
                System.out.print("Tu elección: ");
                opc = leer.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("Error: debes ingresar un número válido.");
                leer.nextLine();
            }

            switch (opc){
                case 1:
                    System.out.println("¿Qué dificultad quieres para el sudoku?");
                    System.out.println("1.- Fácil");
                    System.out.println("2.- Medio");
                    System.out.println("3.- Díficil");
                    try {
                        System.out.print("Tu elección: ");
                        opc = leer.nextInt();
                    } catch (InputMismatchException e) {
                        System.out.println("Error: debes ingresar un número válido.");
                        leer.nextLine();
                    }

                    switch(opc){
                        case 1:
                            // Imprimir el sudoku generado
                            System.out.println("Sudoku generado");
                            generarSudokuFacil(sudoku);
                            imprimirSudoku(sudoku);
                            break;
                        
                        case 2:
                            // Imprimir el sudoku generado
                            System.out.println("Sudoku generado");
                            generarSudokuMedio(sudoku);
                            imprimirSudoku(sudoku);
                            break;
                        
                        case 3:
                            // Imprimir el sudoku generado
                            System.out.println("Sudoku generado");
                            generarSudokuDificil(sudoku);
                            imprimirSudoku(sudoku);
                            break;
                        
                        default:
                            System.out.println("La opción " + opc + "  no existe");
                            break;
                    }
                    break;
                
                case 2:
                    System.out.println("Inserción de números en el sudoku");
                    for (int i = 0; i < N(); i ++){
                        for (int j = 0; j < N(); j ++){
                            int num = 0;
                            boolean inputCorrect = false;
                            while (!inputCorrect){
                                try {
                                    System.out.print("Inserta el elemento " + i+1 + "," + j+1 + ": ");
                                    num = leer.nextInt();
                                } catch (InputMismatchException e) {
                                    System.out.println("Error: debes ingresar un número válido.");
                                    leer.nextLine();
                                }
                                // Asignar el número al sudoku
                                sudoku.get(i).set(j,num);

                                // Verificar el número es correcto
                                System.out.println("¿El número es correcto? S/N");
                                System.out.print("Tu elección: ");
                                error = leer.nextLine();
                                fin = error.charAt(0);

                                if (fin == 'S' || fin == 's'){
                                    inputCorrect = true;
                                } else {
                                    throw new IllegalArgumentException("El número no es correcto, vuelve a intentarlo.");
                                }
                            }
                        }
                    }
                    break;
                
                default:
                    System.out.println("La opción " + opc + "  no existe");
                    break;
            }
            
            System.out.println("¿Quieres continuar? S/N");
            System.out.print("Tu elección: ");
            exit = leer.next();
            fin = exit.charAt(0);
        }

        System.out.print("Presiona una tecla y da enter para finalizar");
        leer.next();
        leer.close();
    }
}