#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

const int WIDTH = 40, HEIGHT = 20;
const char BIRD = '*', PIPE = '|', EMPTY = ' ';

int birdX = 5, birdY = HEIGHT / 2, score = 0;
vector<pair<int, int>> pipes;

void draw() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == birdY && j == birdX)
                cout << BIRD;
            else {
                bool isPipe = false;
                for (auto &p : pipes) {
                    if (j == p.first && (i < p.second || i > p.second + 5)) {
                        cout << PIPE;
                        isPipe = true;
                        break;
                    }
                }
                if (!isPipe) cout << EMPTY;
            }
        }
        cout << endl;
    }
    cout << "\nScore: " << score << endl;
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == ' ') birdY -= 2;
    }
    birdY += 1;
}

void logic() {
    for (int i = 0; i < pipes.size(); i++)
        pipes[i].first--;

    if (pipes.size() && pipes[0].first < 0)
        pipes.erase(pipes.begin());

    if (pipes.empty() || pipes.back().first < WIDTH - 15)
        pipes.push_back({WIDTH - 1, rand() % (HEIGHT - 8) + 1});

    for (auto &p : pipes) {
        if (p.first == birdX && (birdY < p.second || birdY > p.second + 5)) {
            cout << "Game Over! Final Score: " << score << endl;
            exit(0);
        }
    }

    if (pipes.size() && pipes[0].first == birdX)
        score++;
    
    if (birdY >= HEIGHT || birdY < 0) {
        cout << "Game Over! Final Score: " << score << endl;
        exit(0);
    }
}

int main() {
    while (true) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    return 0;
}
