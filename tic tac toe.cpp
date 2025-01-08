#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Function to draw the Tic Tac Toe board
void drawBoard(const vector<char> &board) {
    cout << "     |     |      " << endl;
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;
    cout << "_____|_____|______" << endl;
    cout << "     |     |      " << endl;
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;
    cout << "_____|_____|______" << endl;
    cout << "     |     |      " << endl;
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;
    cout << "     |     |      " << endl;
}

// Function to check if a player has won
bool checkWin(const vector<char> &board, char player) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player) {
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player) {
            return true;
        }
    }
    // Check diagonals
    if (board[0] == player && board[4] == player && board[8] == player) {
        return true;
    }
    if (board[2] == player && board[4] == player && board[6] == player) {
        return true;
    }
    return false;
}

// Function to check if the board is full
bool checkFull(const vector<char> &board) {
    for (char c : board) {
        if (c != 'X' && c != 'O') {
            return false;
        }
    }
    return true;
}

// Function for single player mode (against the computer)
void singlePlayerMode() {
    vector<char> board(9, ' ');
    int move;
    char player = 'X';
    while (true) {
        drawBoard(board);
        if (checkWin(board, 'X')) {
            cout << "You win!" << endl;
            break;
        } else if (checkWin(board, 'O')) {
            cout << "Computer wins!" << endl;
            break;
        } else if (checkFull(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
        if (player == 'X') {
            cout << "Enter your move (1-9): ";
            cin >> move;
            if (move < 1 || move > 9 || board[move - 1] != ' ') {
                cout << "Invalid move! Try again." << endl;
                continue;
            }
            board[move - 1] = player;
        } else {
            do {
                move = rand() % 9;
            } while (board[move] != ' ');
            cout << "Computer's move: " << move + 1 << endl;
            board[move] = player;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    drawBoard(board);
}

// Function for multiplayer mode
void multiPlayerMode() {
    vector<char> board(9, ' ');
    int move;
    char player = 'X';
    while (true) {
        drawBoard(board);
        if (checkWin(board, 'X')) {
            cout << "Player 1 wins!" << endl;
            break;
        } else if (checkWin(board, 'O')) {
            cout << "Player 2 wins!" << endl;
            break;
        } else if (checkFull(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
        cout << "Player " << (player == 'X' ? "1" : "2") << ", enter your move (1-9): ";
        cin >> move;
        if (move < 1 || move > 9 || board[move - 1] != ' ') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }
        board[move - 1] = player;
        player = (player == 'X') ? 'O' : 'X';
    }
    drawBoard(board);
}

// Main function
int main() {
    int mode;
    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Choose the mode: " << endl;
    cout << "1. Single Player Mode" << endl;
    cout << "2. Multiplayer Mode" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> mode;
    if (mode == 1) {
        singlePlayerMode();
    } else if (mode == 2) {
        multiPlayerMode();
    } else {
        cout << "Invalid choice! Please choose 1 or 2." << endl;
    }
    return 0;
}
