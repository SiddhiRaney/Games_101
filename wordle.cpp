#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

// Function to check and give feedback
string getFeedback(string guess, string secret) {
    string feedback = "XXXXX"; // X = wrong, Y = right letter wrong spot, G = correct spot
    bool secretUsed[5] = {false};
    bool guessUsed[5] = {false};

    // First pass: Check for greens (correct letter and position)
    for (int i = 0; i < 5; i++) {
        if (guess[i] == secret[i]) {
            feedback[i] = 'G';
            secretUsed[i] = true;
            guessUsed[i] = true;
        }
    }

    // Second pass: Check for yellows (correct letter wrong position)
    for (int i = 0; i < 5; i++) {
        if (!guessUsed[i]) {
            for (int j = 0; j < 5; j++) {
                if (!secretUsed[j] && guess[i] == secret[j]) {
                    feedback[i] = 'Y';
                    secretUsed[j] = true;
                    break;
                }
            }
        }
    }

    return feedback;
}

int main() {
    vector<string> wordList = {
        "apple", "brain", "crane", "drain", "eagle",
        "flame", "grape", "house", "input", "joker",
        "kneel", "lemon", "magic", "noble", "ocean",
        "pride", "queen", "risky", "sunny", "teeth"
    };

    srand(time(0));
    string secret = wordList[rand() % wordList.size()];
    string guess;
    int attempts = 6;

    cout << "🟨🟩 Welcome to Word Guess! (C++ Wordle) 🟩🟨\n";
    cout << "Guess the 5-letter word. You have 6 attempts.\n\n";

    while (attempts--) {
        cout << "Enter guess (" << attempts + 1 << " left): ";
        cin >> guess;

        // Lowercase conversion
        transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

        if (guess.length() != 5) {
            cout << "❌ Enter a 5-letter word only!\n";
            attempts++; // Don't count invalid input
            continue;
        }

        string feedback = getFeedback(guess, secret);
        cout << "Feedback: " << feedback << "\n";

        if (guess == secret) {
            cout << "🎉 Correct! You guessed the word!\n";
            break;
        }

        if (attempts == 0) {
            cout << "💀 Game Over! The word was: " << secret << endl;
        }
    }

    return 0;
}
