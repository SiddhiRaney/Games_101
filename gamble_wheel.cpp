#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int spinWheel() {
    return rand() % 8 + 1; // Wheel has 8 slots (1 to 8)
}

int main() {
    srand(time(0));
    int balance = 100; // Starting points
    char choice;

    cout << "🎰 Welcome to the Gamble Wheel Game!\n";
    cout << "You start with 100 points.\n";
    cout << "Spin the wheel and try your luck!\n";

    do {
        cout << "\nCurrent Balance: " << balance << " points";
        cout << "\nEnter 's' to spin or 'q' to quit: ";
        cin >> choice;

        if (choice == 's' || choice == 'S') {
            int result = spinWheel();
            cout << "Wheel stopped at: " << result << endl;

            if (result == 1) {
                cout << "🎉 Jackpot! You won 50 points!\n";
                balance += 50;
            } else if (result >= 2 && result <= 4) {
                cout << "👍 Nice! You won 20 points.\n";
                balance += 20;
            } else if (result == 5 || result == 6) {
                cout << "😐 Oops! You lost 10 points.\n";
                balance -= 10;
            } else {
                cout << "💸 Bad luck! You lost 30 points.\n";
                balance -= 30;
            }

            if (balance <= 0) {
                cout << "\n😞 You're out of points! Game over.\n";
                break;
            }
        }

    } while (choice != 'q' && choice != 'Q');

    cout << "\n🏁 Final Balance: " << balance << " points.\n";
    cout << "Thanks for playing!\n";

    return 0;
}
