#include <iostream>

void mario(int x) {
    x++;
}

int main() {

    int yoshi = 1;

    mario(yoshi);

    std::cout << yoshi << std::endl;


    return 0;
}