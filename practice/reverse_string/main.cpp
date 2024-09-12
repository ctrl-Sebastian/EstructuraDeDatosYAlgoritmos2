#include<iostream>
using namespace std;

// Reverse the string recursevly

// str = hola
void reverse (string str) {
    if (str.length() == 0) {
        return;
    }
    string rest = str.substr(1);
    // revers(ola) -> reverse(la) -> reverse(a) -> reverse()
    reverse(rest);
    // a -> l -> o -> h
    cout << str[0];
}

int main()
{
    reverse("hola");

    return 0;
}