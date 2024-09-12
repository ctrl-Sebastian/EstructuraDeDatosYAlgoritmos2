#include<iostream>
using namespace std;
//Write a C++ program to implement a recursive function to calculate the sum of digits of a given number. 

int sumOfDigits(int n) {
    if(n == 0) {
        return 0;
    }
    return n%10 + sumOfDigits(n/10);
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Sum of digits of " << n << " is " << sumOfDigits(n) << endl;

    return 0;
}