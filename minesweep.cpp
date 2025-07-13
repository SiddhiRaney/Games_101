#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const char MINE = '*';
const char HIDDEN = '#';
const char EMPTY = ' ';
const int DX[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int DY[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

int rows, cols, mines;
vector<vector<char>> board;      // Actual board with mines and numbers
vector<vector<char>> display;    // What the player sees
vector<vector<bool>> visited;

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

void placeMines() {
    int placed = 0;
    while (placed < mines) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (board[r][c] != MINE) {
            board[r][c] = MINE;
            placed++;
        }
    }
}

void calculateNumbers() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == MINE) continue;
            int count = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + DX[d], nj = j + DY[d];
                if (isValid(ni, nj) && board[ni][nj] == MINE) {
                    count++;
                }
            }
            if (count > 0)
                board[i][j] = '0' + count;
            else
                board[i][j] = EMPTY;
        }
    }
}

void printBoard(const vector<vector<char>>& b) {
    cout << "   ";
    for (int j = 0; j < cols; j++) cout << setw(2) << j << " ";
    cout << "\n";
    for (int i = 0; i < rows; i++) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < cols; j++) {
            cout << "[" << b[i][j] << "]";
        }
        cout << endl;
    }
}

void reveal(int x, int y) {
    if (!isValid(x, y) || visited[x][y]) return;
    visited[x][y] = true;
    display[x][y] = board[x][y];
    if (board[x][y] == EMPTY) {
        for (int d = 0; d < 8; d++) {
            reveal(x + DX[d], y + DY[d]);
        }
    }
}

bool checkWin() {
    int unrevealed = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (display[i][j] == HIDDEN)
                unrevealed++;
    return unrevealed == mines;
}

int main() {
    srand(time(0));
    cout << "Enter board size (rows cols): ";
    cin >> rows >> cols;
    cout << "Enter number of mines: ";
    cin >> mines;

    board.assign(rows, vector<char>(cols, EMPTY));
    display.assign(rows, vector<char>(cols, HIDDEN));
    visited.assign(rows, vector<bool>(cols, false));

    placeMines();
    calculateNumbers();

    bool gameOver = false;

    while (!gameOver) {
        printBoard(display);
        int x, y;
        cout << "Enter cell to reveal (row col): ";
        cin >> x >> y;

        if (!isValid(x, y)) {
            cout << "Invalid coordinates.\n";
            continue;
        }

        if (board[x][y] == MINE) {
            cout << "💥 You hit a mine! Game Over.\n";
            printBoard(board);
            break;
        }

        reveal(x, y);

        if (checkWin()) {
            cout << "🎉 Congratulations! You cleared the board!\n";
            printBoard(board);
            break;
        }
    }

    return 0;
}
