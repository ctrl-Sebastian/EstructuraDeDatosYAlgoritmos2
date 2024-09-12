#include <iostream>

bool esPrimo(int arr[], int size, int n){
    for (int i = 0; (arr[i] * arr[i]) <= n; i++)
    {
        if(n % arr[i] == 0) {
            return false;
        }
    }
    return true;
}

void generarPrimosHasta(int arr[], int size, int n)
{
    for (int i = 3; i < n; i += 2)
    {
        if(esPrimo(arr, size, i)) {
            arr[size++] = i;

            int b = arr[size-1];
            int a = arr[size-2];
            if(b - a == 2) {
                std::cout << "(" << a << "," << b << ")" << std::endl;
            }
        }
    }
    
}

int main()
{
    unsigned long long n;
    std::cout << "Ingrese numero limite: " << std::endl;
    std::cin >> n;

    int primos[n];
    primos[0] = 2;

    generarPrimosHasta(primos, 1, n);


    return 0;
}