#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

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
Carta userInput[3] = {{1, CORAZON}, {2, DIAMANTE}, {3, TREBOL}};

void llenarBaraja() {
    for (int i = 0; i < 52; i++)
    {
        baraja[i].numero = i % 13;
        baraja[i].icon = Icono(i / 13);
    }
}

bool esCartaUsuario(Carta carta) {
    for (int i = 0; i < 3; i++) {
        if (carta == userInput[i]) {
            return true;
        }
    }
    return false;
}

bool esAs(Carta carta) {
    return carta.numero == 0;
}

void imprimirBaraja() {
    for (int i = 0; i < 52; i++) {
        bool esUsuario = esCartaUsuario(baraja[i]);
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

        cout << "Numero: " << baraja[i].numero << " Icono: ";
        switch (baraja[i].icon) {
            case CORAZON: cout << "Corazones"; break;
            case DIAMANTE: cout << "Diamantes"; break;
            case TREBOL: cout << "Tréboles"; break;
            case PICA: cout << "Picas"; break;
        }

        if (esUsuario) {
            cout << " (Usuario)";
        }

        if (esCartaAs) {
            cout << " (As)";
        }

        if (usuarioGano || casinoGano || esCartaAs) {
            cout << "\033[0m";  // ddefault
        }

        cout << endl;
    }
}

bool chequearTresCartasDelUsuarioEnBaraja() { 
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

bool chequearCuatroAcesEnBaraja() {                                           
    for (int i = 0; i < 52; i++)
    {
        if (esAs(baraja[i])) 
        {
            if (esAs(baraja[i+1])) 
            {
                if (esAs(baraja[i+2])) 
                {
                    if (esAs(baraja[i+3])) 
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

    /*
    for (int t = 0; t < 3; t++) {
        cout << "Elige el numero de la carta: " << endl;
        cout << "A 2 3 4 5 6 7 8 9 10 J Q K" << endl;
        cout << "- - - - - - - - - - - - - -" << endl;
        cout << "1 2 3 4 5 6 7 8 9 10 11 12 13" << endl;

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
    

    for (int i = 0; i < 1000000; i++) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(std::begin(baraja), std::end(baraja), std::default_random_engine(seed));

        cout << "Intento: " << i << endl;

            if (chequearTresCartasDelUsuarioEnBaraja()) {
                found = true;
                cout << "¡Se encontró la combinación en el intento: " << i << "!" << endl;
                imprimirBaraja();
                break;
            } else if (chequearCuatroAcesEnBaraja()) {
                cout << "¡El casino gana! Se encontraron 4 Ases consecutivos en el intento: " << i << endl;
                imprimirBaraja();
                break;
            }

        cout << "Estado previamente barajado" << endl;
    }
    if (found == false) {
        cout << "No se encontro la combinacion en 1 millon de intentos" << endl;
    }

    return 0;
}