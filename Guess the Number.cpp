#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0)); // Seed for random number generation
    int target = rand() % 100 + 1; // Random number between 1 and 100
    int guess, attempts = 3;

    cout << "I have chosen a number between 1 and 100. Try to guess it!" << endl;

    for (int i = 1; i <= attempts; i++) {
        cout << "Attempt " << i << ": Enter your guess: ";
        cin >> guess;

        if (guess == target) {
            cout << "Congratulations! You guessed it right in " << i << " attempts!\n";
            return 0;
        } 
        else if (guess < target) {
            cout << "Hint: Try a higher number!\n";
        } 
        else {
            cout << "Hint: Try a lower number!\n";
        }
    }

    cout << "Game Over! The correct number was: " << target << endl;
    return 0;
}
