#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

const int SIZE = 5; // 5x5 grid
const vector<string> colors = {RED, GREEN, YELLOW, BLUE, CYAN};
const vector<string> colorNames = {"Red", "Green", "Yellow", "Blue", "Cyan"};

struct Cell {
    char ch;
    string color;
};

void displayGrid(vector<vector<Cell>>& grid) {
    for (auto& row : grid) {
        for (auto& cell : row) {
            cout << cell.color << cell.ch << " " << RESET;
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    vector<vector<Cell>> grid(SIZE, vector<Cell>(SIZE));

    // Fill grid with random letters and random colors
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            char letter = 'A' + rand() % 26;
            string color = colors[rand() % colors.size()];
            grid[i][j] = {letter, color};
        }
    }

    // Place 5 random colored 'E's
    for (int k = 0; k < 5; ++k) {
        int i = rand() % SIZE;
        int j = rand() % SIZE;
        string color = colors[rand() % colors.size()];
        grid[i][j] = {'E', color};
    }

    // Choose a color to find
    string targetColor = colors[rand() % colors.size()];
    string targetColorName;
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == targetColor)
            targetColorName = colorNames[i];
    }

    cout << "\n Welcome to the E-Colour Puzzle Game!\n";
    cout << " Your goal: Find all '" << targetColor << "E" << RESET << "' (i.e., E letters in " << targetColorName << ").\n\n";
    
    displayGrid(grid);

    int count = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j].ch == 'E' && grid[i][j].color == targetColor)
                count++;
        }
    }

    cout << "\n Number of target colored 'E's: " << count << endl;
    cout << "Try to spot them visually!\n";

    return 0;
}
