#Optimized using Divide and Conquer - Recursively
#include <iostream>
#include <cmath>
using namespace std;

// Recursive function to solve Tower of Hanoi
void towerOfHanoi(int n, char src, char dest, char aux) {
    if (n == 0)  // Base case: no disks to move
        return;

    // Move n-1 disks from source to auxiliary
    towerOfHanoi(n - 1, src, aux, dest);
    
    // Move the nth disk from source to destination
    cout << "Move disk " << n << " from " << src << " to " << dest << endl;

    // Move n-1 disks from auxiliary to destination
    towerOfHanoi(n - 1, aux, dest, src);
}

// Optimized wrapper function to calculate minimum moves
void solveHanoi(int n) {
    int minMoves = pow(2, n) - 1;
    cout << "Minimum moves required: " << minMoves << endl;

    // Start solving from source 'A' to destination 'C' using auxiliary 'B'
    towerOfHanoi(n, 'A', 'C', 'B');
}

int main() {
    int numDisks;
    cout << "Enter the number of disks: ";
    cin >> numDisks;

    solveHanoi(numDisks);
    return 0;
}
