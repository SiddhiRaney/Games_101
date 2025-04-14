#include <iostream>     
#include <cstdlib>      // For srand, rand
#include <ctime>        // For time (used to seed random generator)
#include <string>       // For string operations
#include <algorithm>    // For random_shuffle

using namespace std;

// Fisher-Yates Shuffle Algorithm (via random_shuffle)
// Used to randomize the characters of the selected word
string shuffleWord(string word) {
    random_shuffle(word.begin(), word.end());
    return word;
}

// Simple string comparison
// Used to verify if user guessed the correct word
bool checkGuess(string guess, string originalWord) {
    return guess == originalWord;
}

int main() {
    // Game Rules Display
    cout << "==============================" << endl;
    cout << "     WELCOME TO ANAGRAM GUESSER!" << endl;
    cout << "==============================" << endl;
    cout << "🎮  RULES OF THE GAME:" << endl;
    cout << "1. You will be shown a jumbled (anagram) word." << endl;
    cout << "2. Your task is to guess the original word." << endl;
    cout << "3. You can guess multiple times until you're right." << endl;
    cout << "4. The game will tell you how many attempts you took." << endl;
    cout << "==============================" << endl << endl;

    // Word bank
    string words[] = {"silent", "listen", "elbow", "below", "state", "taste", "finder", "friend"};
    int numWords = sizeof(words) / sizeof(words[0]);

    // Random seed initialization
    srand(time(0));

    // Select a random word and shuffle it
    string originalWord = words[rand() % numWords];
    string shuffledWord = shuffleWord(originalWord);

    cout << "Your anagram is: " << shuffledWord << endl;

    string guess;
    int attempts = 0;
    bool correct = false;

    while (!correct) {
        attempts++;
        cout << "Enter your guess: ";
        cin >> guess;

        if (checkGuess(guess, originalWord)) {
            cout << "🎉 Congratulations! You guessed the word correctly: " << originalWord << endl;
            cout << "✅ You took " << attempts << " attempts." << endl;
            correct = true;
        } else {
            cout << "❌ Wrong guess. Try again!" << endl;
        }
    }

    return 0;
}
