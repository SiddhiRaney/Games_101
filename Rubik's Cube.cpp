#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

char cube[6][3][3] = {
    {{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}}, // Up (White)
    {{'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}}, // Down (Yellow)
    {{'G', 'G', 'G'}, {'G', 'G', 'G'}, {'G', 'G', 'G'}}, // Front (Green)
    {{'B', 'B', 'B'}, {'B', 'B', 'B'}, {'B', 'B', 'B'}}, // Back (Blue)
    {{'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}}, // Left (Orange)
    {{'R', 'R', 'R'}, {'R', 'R', 'R'}, {'R', 'R', 'R'}}  // Right (Red)
};

// Function to display the cube
void displayCube() {
    string faces[6] = {"Up", "Down", "Front", "Back", "Left", "Right"};
    for (int f = 0; f < 6; f++) {
        cout << faces[f] << " Face:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cout << cube[f][i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
}

// Rotate a face clockwise
void rotateFace(int face) {
    char temp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[j][2 - i] = cube[face][i][j];
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cube[face][i][j] = temp[i][j];
}

// Rotate a face counter-clockwise
void rotateFaceCounter(int face) {
    char temp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[2 - j][i] = cube[face][i][j];
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cube[face][i][j] = temp[i][j];
}

// Perform a move (U, D, L, R, F, B)
void move(string move) {
    if (move == "U") rotateFace(0);
    else if (move == "U'") rotateFaceCounter(0);
    else if (move == "D") rotateFace(1);
    else if (move == "D'") rotateFaceCounter(1);
    else if (move == "F") rotateFace(2);
    else if (move == "F'") rotateFaceCounter(2);
    else if (move == "B") rotateFace(3);
    else if (move == "B'") rotateFaceCounter(3);
    else if (move == "L") rotateFace(4);
    else if (move == "L'") rotateFaceCounter(4);
    else if (move == "R") rotateFace(5);
    else if (move == "R'") rotateFaceCounter(5);
}

// Scramble the cube
void scrambleCube() {
    string moves[] = {"U", "U'", "D", "D'", "L", "L'", "R", "R'", "F", "F'", "B", "B'"};
    srand(time(0));
    for (int i = 0; i < 20; i++) {
        string moveChoice = moves[rand() % 12];
        move(moveChoice);
        cout << moveChoice << " ";
    }
    cout << "\nScrambled Cube!\n";
}

// Main function
int main() {
    int choice;
    while (true) {
        cout << "\nRubik's Cube Simulator\n";
        cout << "1. Display Cube\n";
        cout << "2. Rotate Face\n";
        cout << "3. Scramble Cube\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            displayCube();
        } else if (choice == 2) {
            string moveChoice;
            cout << "Enter move (U, U', D, D', L, L', R, R', F, F', B, B'): ";
            cin >> moveChoice;
            move(moveChoice);
        } else if (choice == 3) {
            scrambleCube();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
