#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <set>          
#include <vector> 

using namespace std;

enum Icono {
    CORAZON = 0,
    DIAMANTE = 1,
    TREBOL = 2,
    PICA = 3
};

bool found = false;

struct Carta {
    int numero;
    Icono icon;

    bool operator==(const Carta& other) const {
        return numero == other.numero && icon == other.icon;
    }
};

Carta baraja[52] = {0};

void llenarBaraja() {
    for (int i = 0; i < 52; i++)
    {
        baraja[i].numero = i % 13;
        baraja[i].icon = Icono(i / 13);
    }
}

bool esCartaUsuario(Carta carta, Carta userInput[3]) {
    for (int i = 0; i < 3; i++) {
        if (carta.numero == userInput[i].numero && carta.icon == userInput[i].icon) {
            return true;
        }
    }
    return false;
}

bool esAs(Carta carta) {
    return carta.numero == 0;
}

void imprimirBaraja(Carta userInput[3]) {
    for (int i = 0; i < 52; i++) {
        bool esUsuario = esCartaUsuario(baraja[i], userInput);
        bool esCartaAs = esAs(baraja[i]);

        bool usuarioGano = esUsuario && found == true;
        bool casinoGano = esUsuario && found == false;


        if (esCartaAs) {
            cout << "\033[31m";  // rojo
        }
        if (casinoGano) {
            cout << "\033[33m"; // amarillo

        }
        if (usuarioGano) {
            cout << "\033[32m";  // verde
        }

        cout << "Numero: " << baraja[i].numero + 1 << " Icono: ";
        switch (baraja[i].icon) {
            case CORAZON: cout << "Corazones"; break;
            case DIAMANTE: cout << "Diamantes"; break;
            case TREBOL: cout << "Tréboles"; break;
            case PICA: cout << "Picas"; break;
        }

        if (usuarioGano || casinoGano || esCartaAs) {
            cout << "\033[0m";  // ddefault
        }

        cout << endl;
    }
}


vector<int> convertirBarajaAEstado() {
    vector<int> estado;
    for (int i = 0; i < 52; i++) {
        estado.push_back(baraja[i].numero * 10 + baraja[i].icon); 
    }
    return estado;
}

bool estadoPreviamenteBarajado(set<vector<int>>& estadosPrevios) {
    vector<int> estadoActual = convertirBarajaAEstado();
    return estadosPrevios.find(estadoActual) != estadosPrevios.end();
}

void almacenarEstadoBaraja(set<vector<int>>& estadosPrevios) {
    vector<int> estadoActual = convertirBarajaAEstado();
    estadosPrevios.insert(estadoActual);
}

bool chequearTresCartasDelUsuarioEnBaraja(Carta userInput[3]) { 
    for (int i = 0; i < 52; i++)
    {
        if (baraja[i] == userInput[0]) 
        {
            if (baraja[i+1] == userInput[1]) 
            {
                if (baraja[i+2] == userInput[2])
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool chequearCuatroAcesEnBaraja(Carta userInput[3]) {                                           
    for (int i = 0; i < 52; i++)
    {
        if (baraja[i].numero == 0 && baraja[i].icon == 0) 
        {
            if (baraja[i+1].numero == 0 && baraja[i+1].icon == 1) 
            {
                if (baraja[i+2].numero == 0 && baraja[i+2].icon == 2) 
                {
                    if (baraja[i+3].numero == 0 && baraja[i+3].icon == 3) 
                    {
                        return true;
                    }   
                }
            }
        }
    }
    return false;
}

int main()
{
    llenarBaraja();

    Carta userInput[3] = {{1, CORAZON}, {2, DIAMANTE}, {3, TREBOL}};

    /*
    for (int t = 0; t < 3; t++) {
        cout << "Elige el numero de la carta: " << endl;
        cout << "A 2 3 4 5 6 7 8 9 10 J Q K" << endl;
        cout << "- - - - - - - - - - - - - -" << endl;
        cout << "0 1 2 3 4 5 6 7 8 9 10 11 12 13" << endl;

        int numero;
        cin >> numero;

        cout << "Elige el icono de la carta: " << endl;
        cout << "0. Corazon" << endl;
        cout << "1. Diamante" << endl;
        cout << "2. Trebol" << endl;
        cout << "3. Pica" << endl;
        int icono;
        cin >> icono;

        userInput[t].numero = numero;
        userInput[t].icon = Icono(icono);
    }

    */
    

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(baraja), std::end(baraja), std::default_random_engine(seed));

    set<vector<int>> estadosPrevios;

    for (int i = 0; i < 1000000; i++) {
        cout << "Intento: " << i << endl;

        if (!estadoPreviamenteBarajado(estadosPrevios)) {
            if (chequearTresCartasDelUsuarioEnBaraja(userInput)) {
                found = true;
                cout << "¡Se encontró la combinación en el intento: " << i << "!" << endl;
                imprimirBaraja(userInput);
                break;
            } else if (chequearCuatroAcesEnBaraja(userInput)) {
                cout << "¡El casino gana! Se encontraron 4 Ases consecutivos en el intento: " << i << endl;
                imprimirBaraja(userInput);
                break;
            }

            almacenarEstadoBaraja(estadosPrevios);
        }

        shuffle(begin(baraja), end(baraja), default_random_engine(seed));
    }
    if (found == false) {
        cout << "No se encontro la combinacion en 1 millon de intentos" << endl;
    }

    return 0;
}