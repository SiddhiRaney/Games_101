#include <iostream>
using namespace std;

// Display the rules before starting the game
void displayRules() {
    cout << " Missionaries and Cannibals Game \n";
    cout << "\n Game Rules:\n";
    cout << "1. You have 3 Missionaries and 3 Cannibals on the left side of the river.\n";
    cout << "2. A boat can carry a maximum of 2 people.\n";
    cout << "3. Cannibals should NEVER outnumber Missionaries on either side.\n";
    cout << "4. Your goal is to move all Missionaries and Cannibals to the right side.\n";
    cout << "5. Enter the number of Missionaries and Cannibals to move in each turn.\n";
    cout << "6. Game ends when all 3 Missionaries and 3 Cannibals are safely across.\n";
    cout << "Good luck! \n\n";
}

// Display the current state of the game
void displayState(int ml, int cl, int mr, int cr, bool boat) {
    cout << "\nLeft Side: " << ml << " Missionaries, " << cl << " Cannibals";
    cout << " | Boat: " << (boat ? "Left" : "Right") << " | ";
    cout << "Right Side: " << mr << " Missionaries, " << cr << " Cannibals\n";
}

// Check if a state is valid (Missionaries >= Cannibals or no missionaries)
bool isValidState(int m, int c) {
    return (m == 0 || m >= c); // Valid if missionaries are 0 or more than cannibals
}

// Check if the move maintains a valid state
bool isValidMove(int ml, int cl, int mr, int cr) {
    return isValidState(ml, cl) && isValidState(mr, cr);
}

// Move people across the river
void movePeople(int &ml, int &cl, int &mr, int &cr, int m, int c, bool boatLeft) {
    if (boatLeft) {
        ml -= m;
        cl -= c;
        mr += m;
        cr += c;
    } else {
        ml += m;
        cl += c;
        mr -= m;
        cr -= c;
    }
}

// Main game loop
void playGame() {
    int ml = 3, cl = 3; // Missionaries and Cannibals on the left
    int mr = 0, cr = 0; // Missionaries and Cannibals on the right
    bool boatLeft = true; // Boat starts on the left

    displayState(ml, cl, mr, cr, boatLeft);

    while (mr != 3 || cr != 3) {
        int m, c;
        cout << "\nEnter number of Missionaries and Cannibals to move: ";
        cin >> m >> c;

        if ((m + c > 2) || (m < 0) || (c < 0) || (m + c == 0)) {
            cout << " Invalid move! Boat can carry 1 or 2 people.\n";
            continue;
        }

        // Try moving the people
        int new_ml = ml, new_cl = cl, new_mr = mr, new_cr = cr;
        movePeople(new_ml, new_cl, new_mr, new_cr, m, c, boatLeft);

        if (isValidMove(new_ml, new_cl, new_mr, new_cr)) {
            // Move successful
            ml = new_ml;
            cl = new_cl;
            mr = new_mr;
            cr = new_cr;
            boatLeft = !boatLeft; // Move boat to the other side
            displayState(ml, cl, mr, cr, boatLeft);
        } else {
            cout << " Invalid move! Cannibals would outnumber Missionaries.\n";
        }
    }
    cout << "\n Congratulations! All Missionaries and Cannibals are safely across!\n";
}

int main() {
    displayRules();
    playGame();
    return 0;
}
