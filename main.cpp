#include <iostream>
#include <vector>


char player = 'X';
char bot = 'O';

struct BotDecision
{
    int x, y;
};


class TicTacToe {

private:
    int SIZE = 3;
    char board[3][3];

public:
    TicTacToe() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void printBoard() {
        std::cout << "\n" << std::endl;
        std::cout << "  |===0=====1=====2===|";
        for (int i = 0; i < SIZE; i++) {
            std::cout << "\n" << i << " ||";
            for (int j = 0; j < SIZE; j++) {
                std::cout << "  " << board[i][j] << " " << " |";
            }
            std::cout << "|";
        }
        std::cout << "\n  |===================|\n";
    }

    bool draw() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkWin(char sign) {
        return ((board[0][0] == sign && board[0][1] == sign && board[0][2] == sign) ||
                (board[1][0] == sign && board[1][1] == sign && board[1][2] == sign) ||
                (board[2][0] == sign && board[2][1] == sign && board[2][2] == sign) ||
                (board[0][0] == sign && board[1][0] == sign && board[2][0] == sign) ||
                (board[0][1] == sign && board[1][1] == sign && board[2][1] == sign) ||
                (board[0][2] == sign && board[1][2] == sign && board[2][2] == sign) ||
                (board[0][0] == sign && board[1][1] == sign && board[2][2] == sign) ||
                (board[0][2] == sign && board[1][1] == sign && board[2][0] == sign));
    }

    BotDecision lowSkillBot() {
        srand(time(NULL));
        std::vector<BotDecision> decisions;
        BotDecision botDecision;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    botDecision.x = i;
                    botDecision.y = j;
                    decisions.push_back(botDecision);
                }
            }
        }

        botDecision = decisions[rand() % decisions.size()];
        return botDecision;
    }

    int score() {
        if (checkWin(player)) {
            return 1;
        }
        else if (checkWin(bot)) {
            return -1;
        }
        else if (draw()) {
            return 0;
        }
        return INT_MAX;
    }

    BotDecision miniMax() {
        int score = INT_MAX;
        BotDecision decision;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = bot;
                    int value = maxi();
                    if (value < score) {
                        score = value;
                        decision.x = i;
                        decision.y = j;
                    }
                    board[i][j] = ' ';
                }
            }
        }
        return decision;
    }

    int maxi() {
        int points = score();
        if (points != INT_MAX) {
            return points;
        }
        int score = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    score = std::max(score, mini());
                    board[i][j] = ' ';
                }
            }
        }
        return score;
    }

    int mini() {
        int points = score();
        if (points != INT_MAX) {
            return points;
        }
        int score = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = bot;
                    score = std::min(score, maxi());
                    board[i][j] = ' ';
                }
            }
        }
        return score;
    }

    void playerTurn() {
        int row, col;
        do {
            std::cout << "Enter your move: <row col> ";
            scanf("%d %d", &row, &col);

            if (board[row][col] != ' ') {
                std::cout << "Try another one" << std::endl;
            }
        } while (board[row][col] != ' ');

        board[row][col] = player;
    }

    void start(bool level) {
        int turn = 0;
        bool exit = false;

        std::cout << "Hello, today you're gonna play versus our bots!" << std::endl;
        printBoard();

        while (true) {
            if (turn == 0) {
                playerTurn();
                printBoard();

                if (checkWin(player)) {
                    std::cout << "Player won!\n";
                    break;
                }
            }

            else if (turn == 1) {
                BotDecision decision;

                if (level) {
                    decision = lowSkillBot();
                } else {
                    decision = miniMax();
                }

                board[decision.x][decision.y] = bot;
                printBoard();

                if (checkWin(bot))
                {
                    std::cout << "Bot won!\n";
                    break;
                }
            }

            if (draw()) {
                std::cout << "\nIt's a draw\n";
                break;
            }

            turn = 1 - turn;
        }
    }
};

int main(int argc, char *argv[]) {

    TicTacToe TicTacToe;

    if (argc != 2) {
        std::cout << "Wrong number of arguments!" << std::endl;
        std::cout << "The format is following: <bot>" << std::endl;
        std::cout << "It is two bots: L and H" << std::endl;
        return 1;
    }

    if (strcmp(argv[1], "L")) {
        TicTacToe.start(0);
    } else {
        TicTacToe.start(1);
    }


}