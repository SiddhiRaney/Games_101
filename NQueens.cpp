#include <iostream>
#include <vector>
using namespace std;

// Function to print the board
void printBoard(vector<string> &board, int n) {
    for (int i = 0; i < n; i++)
        cout << board[i] << endl;
    cout << "-----------------------" << endl;
}

// Function to check if placing a queen is safe
bool isSafe(int row, int col, vector<string> &board, int n) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q') return false;

    // Check upper-left diagonal
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q') return false;

    // Check upper-right diagonal
    for (int i = row-1, j = col+1; i >= 0 && j < n; i--, j++)
        if (board[i][j] == 'Q') return false;

    return true;
}

// Recursive function to solve the N-Queens problem
void solve(int row, vector<string> &board, int n, int &solutionCount) {
    if (row == n) {
        solutionCount++;
        cout << "Solution " << solutionCount << ":\n";
        printBoard(board, n);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board, n)) {
            board[row][col] = 'Q';
            solve(row + 1, board, n, solutionCount);
            board[row][col] = '.'; // backtrack
        }
    }
}

int main() {
    int n;
    cout << "👑 N-Queens Puzzle 👑\n";
    cout << "---------------------------\n";
    cout << "RULES:\n";
    cout << "1. Place N queens on an N x N chessboard.\n";
    cout << "2. No two queens can attack each other.\n";
    cout << "   (i.e., no same row, column, or diagonal)\n";
    cout << "---------------------------\n";
    cout << "Enter the value of N (e.g., 4, 8): ";
    cin >> n;

    vector<string> board(n, string(n, '.'));
    int solutionCount = 0;

    solve(0, board, n, solutionCount);

    if (solutionCount == 0)
        cout << "No solution exists for N = " << n << endl;
    else
        cout << "Total solutions found: " << solutionCount << endl;

    return 0;
}
