#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
using namespace std;

enum Icono {
    CORAZON = 0,
    DIAMANTE = 1,
    TREBOL = 2,
    PICA = 3
};

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


void imprimirBaraja(Carta userInput[3]) {
    for (int i = 0; i < 52; i++) {
        bool esUsuario = esCartaUsuario(baraja[i], userInput);

        if (esUsuario) {
            cout << "\033[31m";  // rojo
        }

        cout << "Numero: " << baraja[i].numero + 1 << " Icono: ";
        switch (baraja[i].icon) {
            case CORAZON: cout << "Corazones"; break;
            case DIAMANTE: cout << "Diamantes"; break;
            case TREBOL: cout << "Tréboles"; break;
            case PICA: cout << "Picas"; break;
        }

        if (esUsuario) {
            cout << "\033[0m";  // ddefault
        }

        cout << endl;
    }
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

    Carta userInput[3] = {{0, CORAZON}, {0, DIAMANTE}, {0, TREBOL}};

    bool found = false;
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

    shuffle(begin(baraja), end(baraja), default_random_engine(seed));
    while(!chequearTresCartasDelUsuarioEnBaraja(userInput)){
        system("clear");
        shuffle(begin(baraja), end(baraja), default_random_engine(seed));

        imprimirBaraja(userInput);
    }
/*
    for (int i = 1; i < 10000000; i++){
        if(chequearTresCartasDelUsuarioEnBaraja(userInput)){
            found = true;
            cout << "Se encontro la combinacion en el intento: " << i << endl;
            imprimirBaraja(userInput);
            break;
        } else if (chequearCuatroAcesEnBaraja(userInput)) {
            cout << "El casino gana" << endl;
            cout << "Se encontraron 4 aces en el intento: " << i << endl;
            imprimirBaraja(userInput);
            break;
        } else {
            shuffle(begin(baraja), end(baraja), default_random_engine(seed));
        }
    }

    if (found == false) {
        cout << "No se encontro la combinacion en 10 millones de intentos" << endl;
    }
*/
    return 0;
}