#include <string>
#include <cstdint>
#include <iostream>
enum Team { CROSS = 0, CIRCLE = 1, NONE };

constexpr uint16_t masks[] = {
    0b1110000000,
    0b0001110000,
    0b0000001110,
    0b1001001000,
    0b0100100100,
    0b0010010010,
    0b1000100010,
    0b0010101000,
};

constexpr Team teams[] = { CROSS, CIRCLE };

constexpr char team_chars[] = { 'X', 'O', ' ' };

uint8_t read_single_digit() {
    std::string line;
    std::getline(std::cin, line);

    while (line.empty() || line.size() > 1 || line[0] < '1' || line[0] > '9') {
        std::cout << "Invalid input. Try again: ";
        std::getline(std::cin, line);
    }

    return line[0] - '0';
}

Team team_at(uint16_t* board, uint8_t pos) {
    for (auto team : teams)
        if (board[team] & (1 << pos))
            return team;
    
    return NONE;
}

bool play_at(uint16_t& teamBoard, uint8_t pos) {
    teamBoard |= (1 << pos);

    for (auto mask : masks)
        if ((teamBoard & mask) == mask)
            return true;

    return false;
}

void print(uint16_t* board) {
    std::cout << " 1 | 2 | 3" << std::endl;
    std::cout << " 4 | 5 | 6" << std::endl;
    std::cout << " 7 | 8 | 9" << std::endl;
    
    std::cout << std::endl;
        
    for (int i = 1; i <= 9; ++i) {
        std::cout << ' ' << team_chars[team_at(board, i)];

        if (i % 3) std::cout << " |";
        else std::cout << std::endl;
    }

    std::cout << std::endl;
}

void clear() {
#ifdef __WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

int main() {
    uint16_t board[2] = { 0 };
    std::string players[2];

    clear();
    
    std::cout << "Jugador 1 (X): ";
    std::getline(std::cin, players[0]);

    std::cout << "Jugador 2 (O): ";
    std::getline(std::cin, players[1]);

    bool won = false;

    clear();
    print(board);

    for (int i = 0; i < 9; ++i) {
        Team team = static_cast<Team>(i & 1);
        std::cout << players[team] << " (" << team_chars[team] << "): ";

        uint8_t pos = read_single_digit();

        while (team_at(board, pos) != NONE) {
            std::cout << "That position is already taken. Try again: ";
            pos = read_single_digit();
        }

        won = play_at(board[team], pos);

        clear();
        print(board);

        if (won) {
            std::cout << players[team] << " won!" << std::endl;
            break;
        }
    }

    if (!won) {
        std::cout << "It's a draw!" << std::endl;
    }
    
    return 0;
}
