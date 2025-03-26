#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string getFullForm(char choice) {
    if (choice == 'r') return "Rock";
    if (choice == 'p') return "Paper";
    return "Scissors";
}

char getComputerChoice() {
    int choice = rand() % 3; // 0, 1, 2
    if (choice == 0) return 'r';
    if (choice == 1) return 'p';
    return 's';
}

char getPlayerChoice(int playerNum) {
    char choice;
    cout << "Player " << playerNum << ", enter (r)ock, (p)aper, or (s)cissors: ";
    cin >> choice;
    while (choice != 'r' && choice != 'p' && choice != 's') {
        cout << "Invalid choice. Enter r, p, or s: ";
        cin >> choice;
    }
    return choice;
}

int determineWinner(char p1, char p2) {
    if (p1 == p2) return 0; // Tie
    if ((p1 == 'r' && p2 == 's') || (p1 == 's' && p2 == 'p') || (p1 == 'p' && p2 == 'r')) {
        return 1; // Player 1 wins
    }
    return 2; // Player 2 or Computer wins
}

int main() {
    srand(time(0));
    int choice;
    cout << "Choose an option:\n";
    cout << "1. Play vs Computer\n";
    cout << "2. Play vs Player\n";
    cout << "Enter your choice: ";
    cin >> choice;

    int p1Score = 0, p2Score = 0;

    if (choice == 1) {
        for (int round = 1; round <= 3; round++) {
            cout << "\n--- Round " << round << " ---\n";
            char playerChoice = getPlayerChoice(1);
            char computerChoice = getComputerChoice();

            cout << "You chose: " << getFullForm(playerChoice) << endl;
            cout << "Computer chose: " << getFullForm(computerChoice) << endl;

            int result = determineWinner(playerChoice, computerChoice);
            if (result == 1) {
                cout << "You win this round!\n";
                p1Score++;
            } else if (result == 2) {
                cout << "Computer wins this round!\n";
                p2Score++;
            } else {
                cout << "It's a tie!\n";
            }
        }

        cout << "\n--- Final Result ---\n";
        if (p1Score > p2Score) cout << "Congrats! You won the game!\n";
        else if (p1Score < p2Score) cout << "Computer wins! Better luck next time!\n";
        else cout << "It's a tie overall!\n";
    } 
    
    else if (choice == 2) {
        for (int round = 1; round <= 3; round++) {
            cout << "\n--- Round " << round << " ---\n";
            char p1 = getPlayerChoice(1);
            char p2 = getPlayerChoice(2);

            cout << "Player 1 chose: " << getFullForm(p1) << endl;
            cout << "Player 2 chose: " << getFullForm(p2) << endl;

            int result = determineWinner(p1, p2);
            if (result == 1) {
                cout << "Player 1 wins this round!\n";
                p1Score++;
            } else if (result == 2) {
                cout << "Player 2 wins this round!\n";
                p2Score++;
            } else {
                cout << "It's a tie!\n";
            }
        }

        cout << "\n--- Final Result ---\n";
        if (p1Score > p2Score) cout << "Player 1 wins the game!\n";
        else if (p1Score < p2Score) cout << "Player 2 wins the game!\n";
        else cout << "It's a tie overall!\n";
    } 
    
    else {
        cout << "Invalid choice. Exiting game.\n";
    }

    return 0;
}
