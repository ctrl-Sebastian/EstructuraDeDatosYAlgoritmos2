#include <iostream>

#define N 4 

bool board[N][N] = { 0 };

void backtracking(int x, int y) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j]) {
                continue;
            }
        }
        
    }
        
}

int main()
{


    return 0;
}