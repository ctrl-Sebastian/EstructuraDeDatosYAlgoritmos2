#include <iomanip>
#include <iostream>

#define N 8
#define IN_RANGE(x) (0 <= x && x < N)

int board[N][N] = { 1 };

int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

void print_board() {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << std::setw(2) << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}

bool backtrack(int x, int y, int steps = 2)
{    
    if (steps == N * N) {
        print_board();
        return true;
    }

    for (int i = 0; i < 8; ++i) {
        int xNext = x + xMove[i];
        int yNext = y + yMove[i];

        if (!IN_RANGE(xNext) || !IN_RANGE(yNext)) {
            continue;
        }

        if (board[yNext][xNext]) {
            continue;
        }

        board[yNext][xNext] = steps;

        if (backtrack(xNext, yNext, steps + 1))
            return true;

        board[yNext][xNext] = 0;
    }

    return false;
}

int main()
{
    backtrack(0, 0);
    return 0;
}
