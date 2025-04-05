#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Rules of the game:
// 1. You are a character ('@') who pushes snowballs around a grid.
// 2. Snowballs have 3 sizes: small (s), medium (m), large (l).
// 3. Snowballs roll over snow-covered ground ('.') and grow in size:
//    small → medium → large.
// 4. A snowman is complete if there is a large ball with a medium ball
//    on top and a small one on top of that (from bottom to top: l, m, s).
// 5. Snowballs can't roll over walls ('#') or other balls.
// 6. The goal is to stack snowballs correctly in a specific spot ('*').

const int ROWS = 7;
const int COLS = 9;

vector<string> grid = {
    "#########",
    "#.......#",
    "#..s....#",
    "#.......#",
    "#..@....#",
    "#...*...#",
    "#########"
};

int playerRow = 4, playerCol = 3;

void printGrid() {
    for (const string& row : grid)
        cout << row << '\n';
}

bool isInside(int r, int c) {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

char& cell(int r, int c) {
    return grid[r][c];
}

char growSnowball(char size) {
    if (size == 's') return 'm';
    if (size == 'm') return 'l';
    return 'l'; // can't grow beyond large
}

void movePlayer(int dr, int dc) {
    int newR = playerRow + dr;
    int newC = playerCol + dc;

    if (!isInside(newR, newC)) return;

    char next = cell(newR, newC);

    // Move into empty space or snow
    if (next == '.' || next == '*') {
        cell(playerRow, playerCol) = '.';
        cell(newR, newC) = '@';
        playerRow = newR;
        playerCol = newC;
    }

    // Pushing snowball
    if (next == 's' || next == 'm' || next == 'l') {
        int snowR = newR + dr;
        int snowC = newC + dc;

        if (!isInside(snowR, snowC)) return;

        char after = cell(snowR, snowC);

        // Can push into snow ground or empty
        if (after == '.') {
            char newSize = growSnowball(next);
            cell(snowR, snowC) = newSize;
            cell(newR, newC) = '@';
            cell(playerRow, playerCol) = '.';
            playerRow = newR;
            playerCol = newC;
        }
    }
}

int main() {
    cout << "=== A Good Snowman is Hard to Build ===\n";
    cout << "Controls: w = up, s = down, a = left, d = right, q = quit\n";

    char move;
    do {
        printGrid();
        cout << "Your move: ";
        cin >> move;

        switch (move) {
            case 'w': movePlayer(-1, 0); break;
            case 's': movePlayer(1, 0); break;
            case 'a': movePlayer(0, -1); break;
            case 'd': movePlayer(0, 1); break;
        }

    } while (move != 'q');

    cout << "Thanks for playing!\n";
    return 0;
}
