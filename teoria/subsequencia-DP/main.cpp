#include<iostream>
using namespace std;

/*
La tarea es encontrar la subsecuencia común más larga utilizando programación dinámica (DP). Una
subsecuencia es una cadena generada a partir de la cadena original eliminando 0 o más caracteres y sin
cambiar el orden relativo de los caracteres restantes. Por ejemplo, las subsecuencias de “ABC” son “A”,
“B”, “C”, “AB”, “AC”, “BC” y “ABC”. En general, una cadena de longitud n tiene 2 o más subsecuencias.
*/

string subsequencia = "";

int dp(string cadena1, string cadena2, int size1, int size2) {
    if(size1 == 0 || size2 == 0) {
        if (size1 != 0) subsequencia = cadena1[size1] + subsequencia;
        if (size2 != 0) subsequencia = cadena2[size2] + subsequencia;
        return 0;
    }
    if(cadena1[size1] == cadena2[size2]) {
        subsequencia = cadena1[size1] + subsequencia;
        return 1 + dp(cadena1, cadena2, size1 - 1, size2 - 1);
    } else {
        
        return max(dp(cadena1, cadena2, size1-1, size2), dp(cadena1, cadena2, size1, size2-1));
    }


}

int main()
{
    string cadena1, cadena2;
    
    cout << "Ingrese la cadena 1: ";
    cin >> cadena1;

    cout << "Ingrese la cadena 2: ";
    cin >> cadena2;

    cout << "La longitud de la subsecuencia común más larga es: " << dp(cadena1, cadena2, cadena1.size(), cadena2.size()) << endl;
    cout << "subsequencia: " << subsequencia << endl;

    return 0;
}