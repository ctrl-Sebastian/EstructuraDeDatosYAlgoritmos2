#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

constexpr int MIN_VERTICES = 15;
constexpr int MAX_VERTICES = 30;
constexpr int MIN_ARISTAS = 2;

// Clase para implementar una cola simple
class Queue {
private:
    vector<vector<int>> elements;
    int inicio;
    int final;

public:
    Queue() : inicio(0), final(0) {}

    void enqueue(const vector<int>& element) {
        elements.push_back(element);
        final++;
    }

    vector<int> dequeue() {
        if (!isEmpty()) {
            return elements[inicio++];
        } else {
            throw out_of_range("La cola está vacía");
        }
    }

    bool isEmpty() const {
        return inicio == final;
    }
};

// Función para agregar una arista a un grafo dirigido
void agregarArista(vector<vector<int>>& adj, int origen, int destino) {
    adj[origen].push_back(destino); // Grafo dirigido
}

// BFS para encontrar todas las rutas entre dos vértices
void bfs(vector<vector<int>>& adj, int inicio, int fin, int numVertices) {
    vector<bool> visitado(numVertices, false);
    Queue cola;

    // Comenzar desde el vértice de inicio
    cola.enqueue({inicio});

    bool hayRuta = false;

    while (!cola.isEmpty()) {
        vector<int> camino = cola.dequeue();

        // Último nodo del camino actual
        int nodo = camino.back();

        // Si encontramos el nodo final, imprimir la ruta
        if (nodo == fin) {
            hayRuta = true;
            for (int v : camino) {
                cout << v << " ";
            }
            cout << endl;
        }

        // Continuar buscando si el nodo no ha sido visitado
        if (!visitado[nodo]) {
            visitado[nodo] = true;

            // Explorar los vecinos del nodo actual
            for (int vecino : adj[nodo]) {
                if (!visitado[vecino]) {
                    vector<int> nuevoCamino(camino);
                    nuevoCamino.push_back(vecino);
                    cola.enqueue(nuevoCamino);
                }
            }
        }
    }

    if (!hayRuta) {
        cout << "No existe una ruta entre " << inicio << " y " << fin << "." << endl;
    }
}

// Función para generar un grafo dirigido aleatorio
void generarGrafo(vector<vector<int>>& adj, int numVertices) {
    srand(time(0)); // Semilla para la aleatoriedad
    for (int i = 0; i < numVertices; i++) {
        int numAristas = MIN_ARISTAS + rand() % (numVertices / 3 - MIN_ARISTAS + 1);

        for (int j = 0; j < numAristas; j++) {
            int destino;
            destino = rand() % numVertices;
            agregarArista(adj, i, destino);
        }
    }
}

// Función para imprimir la lista de adyacencia
void imprimirGrafo(const vector<vector<int>>& adj, int numVertices) {
    cout << "Lista de adyacencia:" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << i << " -> ";
        for (int vecino : adj[i]) {
            cout << vecino << " ";
        }
        cout << endl;
    }
}

// Función para obtener una entrada numérica válida del usuario
int obtenerEntradaNumerica(int numVertices, const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail() || valor < 0 || valor >= numVertices) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada no válida
            cout << "Por favor, introduce un número válido entre 0 y " << numVertices - 1 << "." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
            return valor;
        }
    }
}

int main() {
    srand(time(0)); // Inicializar la semilla aleatoria

    // Definir el número de vértices aleatorio
    int numVertices = MIN_VERTICES + rand() % (MAX_VERTICES - MIN_VERTICES + 1);

    // Lista de adyacencia para representar el grafo
    vector<vector<int>> adj(numVertices);

    // Generar el grafo aleatorio
    generarGrafo(adj, numVertices);

    // Imprimir el grafo generado (lista de adyacencia)
    imprimirGrafo(adj, numVertices);

    // Pedir al usuario los vértices de inicio y fin
    int inicio = obtenerEntradaNumerica(numVertices, "Introduce el vértice de inicio (0-" + to_string(numVertices - 1) + "): ");
    int fin = obtenerEntradaNumerica(numVertices, "Introduce el vértice de fin (0-" + to_string(numVertices - 1) + "): ");

    // Realizar la búsqueda BFS y encontrar todas las rutas posibles
    cout << "Rutas desde " << inicio << " hasta " << fin << ":" << endl;
    bfs(adj, inicio, fin, numVertices);

    return 0;
}
