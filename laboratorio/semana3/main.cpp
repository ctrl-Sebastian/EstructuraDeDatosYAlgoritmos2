#include <iostream>

std::string guess = "";
const std::string chars= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-_";

bool validate(std::string guess) {
    return guess == "Pas21";
}

bool brute(int index, int size) {
    for (char c : chars) {
        guess[index] = c;
        if (validate(guess)) {
            return true;
        }
        
        if ((index < size-1) && brute(index + 1, size)) {
            return true;
        }
    }

    return false;
}

int main()
{

    int i = 1;
    bool done = false;
    while (!done) {
        guess.resize(i);
        done = brute(0, i++);
    }
    std::cout << "contrasena es: " << guess << std::endl;

    return 0;
}