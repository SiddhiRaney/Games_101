#include <iostream>
#include <iomanip>
using namespace std;

// Function to display rules
void printRules() {
    cout << " WHAT IS A MAGIC SQUARE?\n\n";
    cout << "A magic square is a grid where:\n";
    cout << "1. All numbers from 1 to n*n appear exactly once.\n";
    cout << "2. The sum of each row, column, and both diagonals is the same.\n";
    cout << "3. This common sum is called the 'Magic Constant'.\n\n";

    cout << "📐 RULES FOR 3x3 MAGIC SQUARE (Odd Order):\n";
    cout << "- Uses numbers 1 to 9\n";
    cout << "- Magic Constant = n*(n^2 + 1)/2 = 3*(9 + 1)/2 = 15\n";
    cout << "- Every row, column, and diagonal will sum to 15\n\n";
}

// Function to generate a 3x3 magic square using Siamese method
void generateMagicSquare(int n) {
    int magicSquare[3][3] = {0};

    int number = 1;
    int i = 0, j = n / 2; // Start from middle of first row

    while (number <= n * n) {
        magicSquare[i][j] = number++;

        int newi = (i - 1 + n) % n;
        int newj = (j + 1) % n;

        if (magicSquare[newi][newj] != 0) {
            i = (i + 1) % n;
        } else {
            i = newi;
            j = newj;
        }
    }

    // Display the magic square
    cout << " Generated 3x3 Magic Square:\n\n";
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            cout << setw(4) << magicSquare[x][y];
        }
        cout << "\n";
    }
    cout << "\n Each row, column, and diagonal adds up to 15!\n";
}

int main() {
    printRules();
    generateMagicSquare(3);
    return 0;
}
