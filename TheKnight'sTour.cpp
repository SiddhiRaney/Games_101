#include <iostream>
#include <iomanip> // "input/output manipulation" to control the formatting of output; reference point Line 65... setw() 
using namespace std;

const int N = 8; // Size of the board

// Knight's 8 possible moves
int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

// Check if move is valid
bool isValid(int x, int y, int board[N][N]) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

// Solve Knight's Tour using Backtracking
bool solveKnightTour(int x, int y, int moveCount, int board[N][N]) {
    if (moveCount == N * N) return true;

    for (int i = 0; i < 8; i++) {
        int nextX = x + moveX[i];
        int nextY = y + moveY[i];

        if (isValid(nextX, nextY, board)) {
            board[nextX][nextY] = moveCount;

            if (solveKnightTour(nextX, nextY, moveCount + 1, board))
                return true;

            board[nextX][nextY] = -1; // backtrack
        }
    }
    return false;
}

// Display rules before starting
void printRules() {
    cout << " WELCOME TO THE KNIGHT'S TOUR " << endl;
    cout << "----------------------------------" << endl;
    cout << " RULES:" << endl;
    cout << "1. The board is " << N << "x" << N << " in size." << endl;
    cout << "2. The knight moves in an 'L' shape: 2 steps in one direction and 1 step perpendicular." << endl;
    cout << "3. The knight must visit every cell exactly once." << endl;
    cout << "4. This solution uses backtracking to find a valid path." << endl;
    cout << "----------------------------------\n\n";
}

// Start the Knight's Tour
void startKnightTour() {
    int board[N][N];

    // Initialize board with -1 (unvisited)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    // Start from top-left corner
    int startX = 0, startY = 0;
    board[startX][startY] = 0;

    if (solveKnightTour(startX, startY, 1, board)) {
        cout << "\n SOLUTION FOUND! Knight's path:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << setw(3) << board[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "\n❌ No solution exists from this starting position." << endl;
    }
}

int main() {
    printRules();
    startKnightTour();
    return 0;
}
