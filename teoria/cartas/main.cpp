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
};

Carta baraja[52] = {0};

void llenarBaraja() {
    for (int i = 0; i < 52; i++)
    {
        baraja[i].numero = i % 13;
        baraja[i].icon = Icono(i / 13);
    }
}

bool chequearEntreInputUsuario(Carta userInput[3], Carta carta) {
    for (int i = 0; i < 3; i++)
    {
        if(userInput[i].numero == carta.numero && userInput[i].icon == carta.icon) {
            return true;
        }
    }

    return false;
    
}

bool chequearTresPrimeras(Carta userInput[3]) {
    for (int i = 0; i < 3; i++)
    {
        if(!chequearEntreInputUsuario(userInput, baraja[i])) {
            return false;
        }
    }
    return true;
}


int main()
{
    llenarBaraja();

    Carta userInput[3];


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

    int counter = 1;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    for (int i = 0; i < 1000000; i++){
        cout << "Counter: " << counter << endl;
        if(chequearTresPrimeras(userInput)){
            break;
        } else {
            shuffle(begin(baraja), end(baraja), default_random_engine(seed));

        }
        counter += 1;
    }

    cout << "Counter: " << counter << endl;
    return 0;
}