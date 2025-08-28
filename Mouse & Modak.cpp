#include <iostream>
#include <conio.h>   // for _kbhit() and _getch()
#include <cstdlib>   // for rand()
#include <ctime>     // for seeding rand()
using namespace std;

const int width = 20, height = 10;
int mouseX, mouseY, modakX, modakY, score;

void setup() {
    srand(time(0));
    mouseX = width / 2;
    mouseY = height / 2;
    modakX = rand() % width;
    modakY = rand() % height;
    score = 0;
}

void draw() {
    system("cls"); // clear console
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                cout << "#"; // boundary
            } else if (x == mouseX && y == mouseY) {
                cout << "M"; // mouse
            } else if (x == modakX && y == modakY) {
                cout << "*"; // modak
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
    cout << "Use W A S D to move the mouse!" << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w': mouseY--; break;
        case 's': mouseY++; break;
        case 'a': mouseX--; break;
        case 'd': mouseX++; break;
        }
    }
}

void logic() {
    // if mouse catches modak
    if (mouseX == modakX && mouseY == modakY) {
        score++;
        modakX = rand() % (width - 2) + 1;
        modakY = rand() % (height - 2) + 1;
    }
    // prevent going out of bounds
    if (mouseX <= 0) mouseX = 1;
    if (mouseX >= width - 1) mouseX = width - 2;
    if (mouseY <= 0) mouseY = 1;
    if (mouseY >= height - 1) mouseY = height - 2;
}

int main() {
    setup();
    while (true) {
        draw();
        input();
        logic();
    }
    return 0;
}
