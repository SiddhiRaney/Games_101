#include <iostream>
#include <vector>
using namespace std;

// Display the current state of the frogs
void display(const vector<char>& frogs) {
    for (char c : frogs)
        cout << c << ' ';
    cout << endl;
}

// Check if the puzzle is solved
bool isCompleted(const vector<char>& frogs, int n) {
    for (int i = 0; i < n; i++)
        if (frogs[i] != 'D') return false;

    if (frogs[n] != '_') return false;

    for (int i = n + 1; i < 2 * n + 1; i++)
        if (frogs[i] != 'L') return false;

    return true;
}

int main() {
    int n;
    cout << "============================\n";
    cout << "    🐸 FROG JUMP PUZZLE\n";
    cout << "============================\n";
    cout << "RULES:\n";
    cout << "- You have 'L' frogs (Light Green) on the left\n";
    cout << "- You have 'D' frogs (Dark Green) on the right\n";
    cout << "- Middle space is empty (_)\n";
    cout << "- Goal: Swap the positions of L and D frogs\n";
    cout << "- L frogs can only move ➡️ right\n";
    cout << "- D frogs can only move ⬅️ left\n";
    cout << "- You can move 1 step into an empty space or jump over 1 frog into an empty space\n\n";

    cout << "EXAMPLE (n = 3):\n";
    cout << "Initial State:  L L L _ D D D\n";
    cout << "Final State:    D D D _ L L L\n\n";

    cout << "Enter number of frogs on each side: ";
    cin >> n;

    vector<char> frogs(2 * n + 1);

    // Setup initial state
    for (int i = 0; i < n; i++)
        frogs[i] = 'L';
    frogs[n] = '_';
    for (int i = n + 1; i < 2 * n + 1; i++)
        frogs[i] = 'D';

    int empty = n;

    cout << "\nInitial State:\n";
    display(frogs);

    // Game loop
    while (!isCompleted(frogs, n)) {
        int move;
        cout << "\nEnter frog position to move (0 to " << 2 * n << "): ";
        cin >> move;

        if (move < 0 || move > 2 * n) {
            cout << "❌ Invalid position.\n";
            continue;
        }

        // Light frog movement
        if (frogs[move] == 'L') {
            if (move + 1 == empty || (move + 2 == empty && frogs[move + 1] != '_')) {
                swap(frogs[move], frogs[empty]);
                empty = move;
            } else {
                cout << "❌ Invalid move for L frog.\n";
            }
        }
        // Dark frog movement
        else if (frogs[move] == 'D') {
            if (move - 1 == empty || (move - 2 == empty && frogs[move - 1] != '_')) {
                swap(frogs[move], frogs[empty]);
                empty = move;
            } else {
                cout << "❌ Invalid move for D frog.\n";
            }
        } else {
            cout << "❌ You selected the empty space. Choose a frog.\n";
        }

        display(frogs);
    }

    cout << "\n🎉 Congratulations! Puzzle Completed!\n";
    return 0;
}
