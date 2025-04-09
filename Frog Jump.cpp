// Backtracking with Pruning 
#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<vector<char>> solutionSteps;

void display(const vector<char>& frogs) {
    for (char c : frogs) cout << c << ' ';
    cout << endl;
}

bool isCompleted(const vector<char>& frogs, int n) {
    for (int i = 0; i < n; i++)
        if (frogs[i] != 'D') return false;
    if (frogs[n] != '_') return false;
    for (int i = n + 1; i < 2 * n + 1; i++)
        if (frogs[i] != 'L') return false;
    return true;
}

bool solve(vector<char>& frogs, int empty, int n, set<string>& visited) {
    if (isCompleted(frogs, n)) {
        solutionSteps.push_back(frogs);
        return true;
    }

    // Create a unique string key for visited
    string state(frogs.begin(), frogs.end());
    if (visited.count(state)) return false;
    visited.insert(state);

    // Try all possible moves
    for (int i = 0; i < frogs.size(); i++) {
        // L frogs can move right
        if (frogs[i] == 'L') {
            if (i + 1 == empty || (i + 2 == empty && frogs[i + 1] != '_')) {
                swap(frogs[i], frogs[empty]);
                int new_empty = i;
                if (solve(frogs, new_empty, n, visited)) {
                    solutionSteps.push_back(frogs);
                    return true;
                }
                swap(frogs[i], frogs[empty]); // backtrack
            }
        }
        // D frogs can move left
        else if (frogs[i] == 'D') {
            if (i - 1 == empty || (i - 2 == empty && frogs[i - 1] != '_')) {
                swap(frogs[i], frogs[empty]);
                int new_empty = i;
                if (solve(frogs, new_empty, n, visited)) {
                    solutionSteps.push_back(frogs);
                    return true;
                }
                swap(frogs[i], frogs[empty]); // backtrack
            }
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of frogs on each side: ";
    cin >> n;

    vector<char> frogs(2 * n + 1);
    for (int i = 0; i < n; i++) frogs[i] = 'L';
    frogs[n] = '_';
    for (int i = n + 1; i < 2 * n + 1; i++) frogs[i] = 'D';
    int empty = n;

    cout << "\nSolving Puzzle...\n";
    set<string> visited;
    if (solve(frogs, empty, n, visited)) {
        cout << "\n🔁 Optimal Move Sequence:\n";
        for (int i = solutionSteps.size() - 1; i >= 0; i--)
            display(solutionSteps[i]);
        cout << "\n🎉 Puzzle Solved in " << solutionSteps.size() - 1 << " moves!\n";
    } else {
        cout << "❌ No solution found.\n";
    }

    return 0;
}
