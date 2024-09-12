    #include<iostream>
using namespace std;

const int WIDTH = 3;
int matrix[WIDTH][WIDTH];
bool taken[9] ={false};

bool checkNumbers () {
    if(matrix[0][0] + matrix[0][1] + matrix[0][2] != 15) return false;
    if(matrix[1][0] + matrix[1][1] + matrix[1][2] != 15) return false;
    if(matrix[2][0] + matrix[2][1] + matrix[2][2] != 15) return false;

    if(matrix[0][0] + matrix[1][0] + matrix[2][0] != 15) return false;
    if(matrix[0][1] + matrix[1][1] + matrix[2][1] != 15) return false;
    if(matrix[0][2] + matrix[1][2] + matrix[2][2] != 15) return false;

    if(matrix[0][0] + matrix[1][1] + matrix[2][2] != 15) return false;
    if(matrix[0][2] + matrix[1][1] + matrix[2][0] != 15) return false;

    return true;
}

void printMatrix() {
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}

void putNumber(int x, int y) {
    if (x > 2) {
        x = 0;
        ++y;
    }

    if(y == 3) {
        if(checkNumbers()){
            printMatrix();
            return;
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        if(taken[i-1]) {
            continue;
        }

        matrix[y][x] = i;
        taken[i-1] = true;
        putNumber(x+1, y);
        taken[i-1] = false;
    }
}

int main () {
    putNumber(0,0);
    return 0;
}