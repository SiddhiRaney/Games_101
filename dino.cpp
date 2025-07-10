#include <iostream>
#include <conio.h>      // For _kbhit() and _getch()
#include <windows.h>    // For Sleep() and system("cls")
using namespace std;

const int width = 40;
const int height = 10;
int dinoY = height - 1;
int cactusX = width - 1;
int jumpPower = 0;
bool jumping = false;
bool gameOver = false;
int score = 0;

void draw() {
    system("cls"); // Clear screen

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 2 && y == dinoY)
                cout << "D"; // Dino
            else if (x == cactusX && y == height - 1)
                cout << "#"; // Cactus
            else if (y == height - 1)
                cout << "_"; // Ground
            else
                cout << " ";
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void logic() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == ' ' && !jumping) {
            jumping = true;
            jumpPower = 3;
        }
    }

    // Jumping mechanics
    if (jumping) {
        dinoY--;
        jumpPower--;
        if (jumpPower == 0) jumping = false;
    } else if (dinoY < height - 1) {
        dinoY++;
    }

    // Move cactus
    cactusX--;
    if (cactusX == 0) {
        cactusX = width - 1;
        score++;
    }

    // Collision detection
    if (cactusX == 2 && dinoY == height - 1) {
        gameOver = true;
    }
}

int main() {
    while (!gameOver) {
        draw();
        logic();
        Sleep(100); // Game speed
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    system("pause");
    return 0;
}
