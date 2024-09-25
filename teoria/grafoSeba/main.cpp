/*
-----------------------------------------
Integrantes:
Angel Medina 😠
Sebastian De Leon 🙋
Lazaro Alvarez 🥱

Desarrollar un programa en C++ que modele un grafo con al menos 15 vértices, máximo 30, donde el 
usuario pueda capturar dos vértices y el programa deberá encontrar y mostrar todas las rutas posibles 
entre ellos.

La cantidad de vértices debe ser elegida de forma aleatoria (15-30).
Las aristas entre vértices deben ser generadas aleatoriamente con mínimo 2 relaciones, máximo= N/3.
(Ejemplo 20/3=~7 aristas). 

Restricciones:

1. El programa deberá representar un grafo dirigido.
2. El grafo debe contener al menos 15 vértices o nodos y puede estar representado mediante una matriz 
de adyacencia o listas de adyacencia.
3. El programa debe permitir al usuario capturar dos vértices (de inicio y de destino) mediante entrada 
por teclado.
4. Utilizar algoritmos de búsqueda como DFS (Depth-First Search) o BFS (Breadth-First Search) para 
encontrar todas las rutas posibles entre los vértices capturados.
5. Si no existe una ruta entre los vértices, el programa deberá indicarlo.
6. Antes de realizar la captura de los vértices de inicio y destino, el programa debe mostrar la matriz de 
adyacencia o la lista de adyacencia

-----------------------------------------
*/
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <limits>
using namespace std;

const int MIN_VERTICES = 15;
const int MAX_VERTICES = 30;
const int MIN_ARISTAS = 2;

vector<vector<int>> mat;

void addEdgeFromAToB(vector<vector<int>>& adj, int firstVertex, int secondVertex) {
    adj[firstVertex].push_back(secondVertex);
}

void displayAdjList(const vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": "; // Print the vertex
        for (int j : adj[i]) {
            cout << j << " "; // Print its adjacent
        }
        cout << endl; 
    }
}

void generateGraph(vector<vector<int>> &adj, int numVertices) {
    srand(time(0));
    for (int i = 0; i < numVertices; i++) {
        int numEdges = MIN_ARISTAS + rand() % (numVertices / 3 - MIN_ARISTAS + 1);
        for (int j = 0; j < numEdges; j++) {
            int destination;
            destination = rand() % numVertices;
            addEdgeFromAToB(adj, i, destination);
        }
    }
}

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

void funcionMasBacana(vector<vector<int>> &adj, int numVertices, int startVertex, int endVertex) {
    bool visited[numVertices] = {false};
    struct node {
        int vertex;
        int steps;
    };

    deque<node> queue;

    queue.push_back({startVertex, 0});
    while(!queue.empty()) {
        node front = queue.front();
        queue.pop_front();

        if (front.vertex == endVertex) {
            cout << "Ruta encontrada en " << front.steps << " pasos." << endl;
            return;
        }

        
    }
    // def bfs(start, end, steps)
    //    if start == end:
    //        return steps
    //    adjacents = get_adjacents(start)
    //    for adjacent in adjacents:
    //        return bfs(adjacent, end, steps + 1)
    //

    
}


int main() {
    int numVertices = MIN_VERTICES + rand() % (MAX_VERTICES - MIN_VERTICES + 1);
    vector<vector<int>> adj(numVertices); 

    generateGraph(adj, numVertices);

    cout << "Adjacency List Representation:" << endl;
    displayAdjList(adj);

    int startVertex = obtenerEntradaNumerica(numVertices, "Ingrese el numero del primer nodo (vertice)");
    int endVertex = obtenerEntradaNumerica(numVertices, "Ingrese el numero del segundo nodo (vertice)");

    cout << "Rutas desde" << startVertex << " a " << endVertex << ":" << endl;


    return 0;
}