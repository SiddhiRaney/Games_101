#include <bits/stdc++.h>
using namespace std;

// Board size
const int N = 100;

// Function to roll the dice
int rollDice() {
    return rand() % 6 + 1; // Generates a number between 1 and 6
}

// Function to get new position after encountering snake or ladder
int getNewPosition(int pos, unordered_map<int, int> &snakes, unordered_map<int, int> &ladders) {
    if (snakes.find(pos) != snakes.end()) {
        cout << "Oops! Bitten by snake at " << pos << endl;
        return snakes[pos];
    }
    if (ladders.find(pos) != ladders.end()) {
        cout << "Yay! Climb up a ladder at " << pos << endl;
        return ladders[pos];
    }
    return pos;
}

// Main game function
void playGame(unordered_map<int, int> &snakes, unordered_map<int, int> &ladders) {
    int player1 = 1, player2 = 1;
    int turn = 1;

    while (player1 < N && player2 < N) {
        int roll = rollDice();
        cout << "Player " << turn << " rolls a " << roll << endl;

        if (turn == 1) {
            player1 += roll;
            if (player1 <= N) {
                player1 = getNewPosition(player1, snakes, ladders);
                cout << "Player 1 moves to " << player1 << endl;
            } else {
                player1 -= roll; // If exceeds 100, stay at the same position
            }
            if (player1 == N) {
                cout << "Player 1 wins!" << endl;
                break;
            }
            turn = 2;
        } else {
            player2 += roll;
            if (player2 <= N) {
                player2 = getNewPosition(player2, snakes, ladders);
                cout << "Player 2 moves to " << player2 << endl;
            } else {
                player2 -= roll;
            }
            if (player2 == N) {
                cout << "Player 2 wins!" << endl;
                break;
            }
            turn = 1;
        }
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Define snakes and ladders positions
    unordered_map<int, int> snakes, ladders;

    // Snakes: head -> tail
    snakes[98] = 28;
    snakes[95] = 24;
    snakes[92] = 51;
    snakes[83] = 19;
    snakes[73] = 1;
    snakes[64] = 60;
    snakes[50] = 5;
    snakes[46] = 25;
    snakes[20] = 8;

    // Ladders: start -> end
    ladders[6] = 27;
    ladders[11] = 49;
    ladders[60] = 85;
    ladders[68] = 90;
    ladders[74] = 94;
    ladders[2] = 38;
    ladders[13] = 46;
    ladders[33] = 76;
    ladders[43] = 62;

    playGame(snakes, ladders);

    return 0;
}
