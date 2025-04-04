#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 5;

// Toggle a cell and its neighbors
void toggle(vector<vector<int>>& grid, int row, int col) {
    int dx[] = {0, 1, -1, 0, 0}; // center, down, up, right, left
    int dy[] = {0, 0, 0, 1, -1};

    for (int i = 0; i < 5; ++i) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
            grid[newRow][newCol] ^= 1; // Toggle 0 ↔ 1
        }
    }
}

// Check if all lights are off
bool isGameWon(const vector<vector<int>>& grid) {
    for (const auto& row : grid)
        for (int cell : row)
            if (cell == 1)
                return false;
    return true;
}

// Print the grid
void printGrid(const vector<vector<int>>& grid) {
    cout << "\nCurrent Grid:\n";
    for (const auto& row : grid) {
        for (int cell : row)
            cout << (cell ? "🔆 " : "⬛ ");
        cout << "\n";
    }
}

int main() {
    srand(time(0));
    vector<vector<int>> grid(N, vector<int>(N));

    // Randomly initialize the grid
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            grid[i][j] = rand() % 2;

    int row, col;
    while (true) {
        printGrid(grid);
        if (isGameWon(grid)) {
            cout << "\n🎉 You won! All lights are off!\n";
            break;
        }

        cout << "Enter row and column to toggle (0-indexed, e.g. 2 3): ";
        cin >> row >> col;

        if (row < 0 || row >= N || col < 0 || col >= N) {
            cout << "Invalid input. Try again.\n";
            continue;
        }

        toggle(grid, row, col);
    }

    return 0;
}
