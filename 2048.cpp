#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

const int SIZE = 4;
int grid[SIZE][SIZE];

void printGrid() {
    system("clear"); // use "cls" on Windows
    cout << "\n\t\t2048 GAME\n\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0)
                cout << setw(6) << ".";
            else
                cout << setw(6) << grid[i][j];
        }
        cout << "\n\n";
    }
}

void addRandomTile() {
    vector<pair<int, int>> empty;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (grid[i][j] == 0)
                empty.push_back({i, j});
    if (!empty.empty()) {
        auto [x, y] = empty[rand() % empty.size()];
        grid[x][y] = (rand() % 10 == 0) ? 4 : 2;
    }
}

bool canMove() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0)
                return true;
            if (j + 1 < SIZE && grid[i][j] == grid[i][j + 1])
                return true;
            if (i + 1 < SIZE && grid[i][j] == grid[i + 1][j])
                return true;
        }
    return false;
}

bool slideLeft() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int tmp[SIZE] = {0}, idx = 0;
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != 0)
                tmp[idx++] = grid[i][j];
        }
        for (int j = 0; j < SIZE - 1; j++) {
            if (tmp[j] && tmp[j] == tmp[j + 1]) {
                tmp[j] *= 2;
                tmp[j + 1] = 0;
                moved = true;
            }
        }
        int newRow[SIZE] = {0}; idx = 0;
        for (int j = 0; j < SIZE; j++)
            if (tmp[j])
                newRow[idx++] = tmp[j];

        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != newRow[j]) {
                moved = true;
                grid[i][j] = newRow[j];
            }
        }
    }
    return moved;
}

void rotateClockwise() {
    int tmp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            tmp[j][SIZE - i - 1] = grid[i][j];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = tmp[i][j];
}

bool move(char dir) {
    int rotations = 0;
    if (dir == 'w') rotations = 1;
    else if (dir == 'd') rotations = 2;
    else if (dir == 's') rotations = 3;

    for (int i = 0; i < rotations; i++) rotateClockwise();
    bool moved = slideLeft();
    for (int i = 0; i < (4 - rotations) % 4; i++) rotateClockwise();

    return moved;
}

int main() {
    srand(time(0));
    addRandomTile();
    addRandomTile();

    while (true) {
        printGrid();
        cout << "Move (w/a/s/d): ";
        char input;
        cin >> input;

        if (input != 'w' && input != 'a' && input != 's' && input != 'd')
            continue;

        if (move(input))
            addRandomTile();

        if (!canMove()) {
            printGrid();
            cout << "Game Over!\n";
            break;
        }
    }

    return 0;
}
