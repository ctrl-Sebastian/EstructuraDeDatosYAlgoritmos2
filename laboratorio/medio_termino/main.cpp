#include<iostream>
using namespace std;
/*
1. capturar arreglo de n elementos
2. verificar que no haya elementos repetidos
3. imprimir todas las permutaciones posibles utilizando backtracking y / o recursividad
4. imprimir la cantidad de permutaciones
*/
                    //   1 2 3 4      4         0
                    //   1 2 3 4      4         1
                    //   1 2 3 4      4         2
                    //   1 2 3 4      4         3
                    //   1 2 3 4      4         4


void permutaciones(int numbers[], int size, int index)
{
    // CASO BASE
    if (index == size)
    {
        for (int i = 0; i < size; i++)
        {
            cout << numbers[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = index; i < size; i++)
    {
        std::swap(numbers[index], numbers[i]);
        permutaciones(numbers, size, index + 1);
        // BACKTRACK
        std::swap(numbers[index], numbers[i]);
    }
}


int main()
{
    int size;
    cout << "ingrese n: ";
    cin >> size;

    int numbers[size] = { 0 };
    for (int i = 0; i < size; i++)
    {
        cin >> numbers[i];
        for (int j = 0; j < i; j++)
        {
            if (numbers[j] == numbers[i]) {
                cout << "numero repetido, ingrese uno distinto: ";
                numbers[i] = 0;
                cin >> numbers[i];
            }
        }
        
    }

    // factorial of size
    int count = 1;
    for (int i = 1; i <= size; i++)
    {
        count *= i;
    }

    cout << "permutaciones: " << endl;
    permutaciones(numbers, size, 0);
    cout << "cantidad de permutaciones: " << count << endl;

    return 0;
}