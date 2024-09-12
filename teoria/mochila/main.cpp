#include <iostream>
#include <iomanip>

using namespace std;

struct Item {
    int peso;
    int beneficio;
};

double beneficioMaximo = 0.0;
int pesoMaximo = 100;
int mejorSeleccion[5] = {0};

void mochila(Item items[], int numItems, int indice, int pesoActual, double beneficioActual, int seleccionActual[]) {
    if (pesoActual > pesoMaximo) return;

    if (beneficioActual > beneficioMaximo) {
        beneficioMaximo = beneficioActual;
        for (int i = 0; i < numItems; ++i) {
            mejorSeleccion[i] = seleccionActual[i];
        }
    }

    if (indice == numItems) return;

    // Opción 1: No incluir el elemento actual
    mochila(items, numItems, indice + 1, pesoActual, beneficioActual, seleccionActual);

    // Opción 2: Incluir el elemento actual
    if (pesoActual + items[indice].peso <= pesoMaximo) {
        seleccionActual[indice]++;
        mochila(items, numItems, indice, pesoActual + items[indice].peso, beneficioActual + items[indice].beneficio, seleccionActual);
        seleccionActual[indice]--;
    }
}

int main() {
    const int numItems = 5;
    Item items[numItems] = {{10, 20}, {20, 30}, {30, 65}, {40, 40}, {50, 60}};
    int seleccionActual[5] = {0}; // Asumiendo un máximo de 5 elementos

    cout << "Tabla de paquetes:\n";
    cout << setw(10) << "Paquete" << setw(10) << "Peso" << setw(15) << "Beneficio" << endl;
    for (int i = 0; i < numItems; ++i) {
        cout << setw(10) << "Paquete " << i + 1 << setw(10) << items[i].peso << setw(15) << items[i].beneficio << endl;
    }
    cout << endl;

    mochila(items, numItems, 0, 0, 0.0, seleccionActual);

    cout << "El beneficio máximo es: " << beneficioMaximo << endl;
    cout << "Paquetes seleccionados:" << endl;
    for (int i = 0; i < numItems; ++i) {
        if (mejorSeleccion[i] > 0) {
            cout << "Paquete " << i + 1 << ": " << mejorSeleccion[i] << " paquetes, beneficio total = " << mejorSeleccion[i] * items[i].beneficio << endl;
        }
    }

    return 0;
}