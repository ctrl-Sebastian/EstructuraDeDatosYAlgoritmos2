#include <vector>
#include <iomanip>
#include <iostream>
#include <functional>

#define NONE -1

// Vector de dos dimensiones para el tablero.
typedef std::vector<std::vector<int>> board_t;

// array de dos dimensinoes con las tuplas de los movimientos
int directions[][2] = {
    {  1,  2 },
    {  1, -2 },
    { -1,  2 },
    { -1, -2 },
    {  2,  1 },
    {  2, -1 },
    { -2,  1 },
    { -2, -1 },
};

// funcion para imprimir el tablero
void print(const board_t &board) {
    for (auto row : board) {
        for (auto n : row) {
            std::cout << std::setw(2) << n << " ";
        }
        std::cout << std::endl;
    }
}

// la funcion recibe el board, las coordenadas x y y y el numero de pasos
bool backtrack(board_t &board, size_t x, size_t y, size_t steps) {
    // si el numero de pasos es igual al tamaño del tablero al cuadrado devuelve true y se hizo el recorrido entero
    if (steps == board.size() * board.size()) {
        return true;
    }

    // por cada moviento posible del caballo
    for (auto dir : directions) {
        // nx y ny son las nuevas coordenadas del caballo despues de la posicion pasada
        // size_t: tipo de dato para enteros sin signo
        size_t nx = x + dir[0];
        size_t ny = y + dir[1];

        // n es el tamaño del tablero
        size_t n = board.size();

        // si las nuevas coordenadas estan fuera del tablero o si ya hay un numero en esa posicion
        if (nx >= n || ny >= n || board[ny][nx] != NONE) {
            continue;
        }

        // se asigna el numero de pasos a la nueva posicion
        board[ny][nx] = steps;

        // si se puede hacer el recorrido con las nuevas coordenadas
        if (backtrack(board, nx, ny, steps + 1)) {
            // devuelve true
            return true;
        }

        // si no se puede hacer el recorrido con las nuevas coordenadas se asigna NONE a la posicion  
        board[ny][nx] = NONE;
    }

    return false;
}

// funcion inicial para resolver el problema, llama a backtrack
// recibe n para el tamaño del tablero y las primeras coordenadas

void solve(size_t n, size_t x, size_t y) {
    // creamos el board con el tamaño n y lo llenamos de NONE (-1)
    board_t board(n, std::vector<int>(n, NONE));
    // iniciamos en el paso 0
    board[y][x] = 0;

    // si retorna false no se pudo hacer el recorrido y se imprime "No solution"
    if (!backtrack(board, x, y, 1)) {
        std::cout << "No solution" << std::endl;
        return;
    }

    // si se pudo hacer el recorrido se imprime el tablero.
    print(board);
}

// obtencion de input por parte de usuario
template <typename T>
// la funcion recibe un array de chars y una funcion anonima que devuelve un booleano para validar la entrada del usuario
T input(const char *msg, std::function<bool(T)> valid) {
    
    // variable
    T _input;

    // se le imprime al usuario el mensaje msg
    std::cout << msg;

    // continuar pidiendo input hasta que el usuario ingrese un valor valido
    while (!(std::cin >> _input) || !valid(_input)) {
        std::cin.clear();
        // ignora hasta 256 caracteres o hasta encontrar un salto de linea
        std::cin.ignore(256, '\n');
        // imprime "Invalid input." y el mensaje msg
        std::cout << "Invalid input." << std::endl << msg;
    }

    // la funcion devuelve el input del usuario
    return _input;
}

int main() {
    // funcion anonima para validar que n es mayor que 0.
    auto validate_n = [](int n){ return n > 0; };

    // se obtiene el tamaño del tablero y se valida que es mayor que 0.
    int n = input<int>("n: ", validate_n);

    // funcion anonima para validar que x y y estan dentro del tablero.
    auto validate_x_y = [n](int x_y){ return x_y >= 0 && x_y < n; };

    // se obtienen las coordenadas x y y y se valida que caben dentro del tablero.
    int x = input<int>("x: ", validate_x_y);
    int y = input<int>("y: ", validate_x_y);

    // se llama la funcion solve para resolver el problema con un tablero de tamaño n en las posiciones iniciales (x, y).
    solve(n, x, y);

    return 0;
}
