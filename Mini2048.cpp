#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> board(4, 0); // 1D row with 4 tiles

// Spawn a 2 or 4 at a random empty position
void spawnTile() {
    vector<int> emptyIndices;
    for (int i = 0; i < 4; i++) {
        if (board[i] == 0) emptyIndices.push_back(i);
    }

    if (!emptyIndices.empty()) {
        int index = emptyIndices[rand() % emptyIndices.size()];
        board[index] = (rand() % 2 + 1) * 2; // spawn 2 or 4
    }
}

// Display the board
void display() {
    for (int val : board) cout << val << "\t";
    cout << endl;
}

// Slide and merge to the left
void moveLeft() {
    vector<int> newBoard(4, 0);
    int index = 0;

    for (int i = 0; i < 4; i++) {
        if (board[i] == 0) continue;

        if (newBoard[index] == 0)
            newBoard[index] = board[i];
        else if (newBoard[index] == board[i]) {
            newBoard[index] *= 2;
            index++;
        } else {
            index++;
            newBoard[index] = board[i];
        }
    }

    board = newBoard;
}

bool checkWin() {
    for (int val : board) {
        if (val == 2048) return true;
    }
    return false;
}

int main() {
    srand(time(0));
    spawnTile();
    spawnTile();

    while (true) {
        display();

        cout << "Enter L to move left, Q to quit: ";
        char choice;
        cin >> choice;

        if (choice == 'Q' || choice == 'q') break;
        else if (choice == 'L' || choice == 'l') {
            moveLeft();
            spawnTile();
        }

        if (checkWin()) {
            cout << "🎉 You reached 2048! You win!\n";
            break;
        }
    }

    return 0;
}
