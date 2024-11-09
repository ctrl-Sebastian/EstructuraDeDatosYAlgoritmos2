#include <iostream>
#include <string>

enum class Letra {
    Consonante,
    Fuerte,
    Debil
};

// diptongo: que tenga debil
// hiato: vocal cerrada + vocal abierta

// ma ri po sa
// ciudad

Letra identificar(char c) {
    if (c == 'a'|| c == 'e'|| c == 'o') return Letra::Fuerte;
    if (c == 'i'|| c == 'u') return Letra::Debil;
    return Letra::Consonante;
}

int main()
{
    std::string palabra;

    std::cin >> palabra;

    int cursor = 0;

    for (int i = 0; i < palabra.size(); i++)
    {
        Letra tipo = identificar(palabra[i]);

        if (tipo == Letra::Consonante)
            continue;
    
        int size = i - cursor + 1;

        bool foundDebil = tipo == Letra::Debil;
        for (int j = i + 1; j < palabra.size(); j++)
        {
            
            Letra siguienteLetra = identificar(palabra[j]);
            if (siguienteLetra == Letra::Consonante)
                break;

            foundDebil |= siguienteLetra == Letra::Debil;
            if (foundDebil) {
                size++;
                i++;
            } else break;
        }

        if (identificar(palabra[i + 1]) == Letra::Consonante && 
            (i + 2 >= palabra.size() || identificar(palabra[i + 2]) == Letra::Consonante)) {
            size++;
            i++;
        }
        
        std::string silaba = palabra.substr(cursor, size);
        std::cout << silaba << " - ";

        cursor += size;
        

    }
    



    return 0;
}