#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

string getHiddenWord(const string& word, const vector<bool>& guessed) {
    string display = "";
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i])
            display += word[i];
        else
            display += '_';
        display += ' ';
    }
    return display;
}

int main() {
    vector<string> words = {"hangman", "computer", "keyboard", "algorithm", "puzzle"};
    srand(time(0));
    string word = words[rand() % words.size()];
    vector<bool> guessed(word.length(), false);
    int attempts = 6;
    vector<char> wrongGuesses;

    cout << "🎮 Welcome to HANGMAN!\n";
    cout << "Guess the word letter by letter. You have " << attempts << " wrong attempts.\n\n";

    while (attempts > 0) {
        cout << "Word: " << getHiddenWord(word, guessed) << "\n";
        cout << "Wrong guesses: ";
        for (char ch : wrongGuesses) cout << ch << " ";
        cout << "\nEnter a letter: ";
        char guess;
        cin >> guess;

        guess = tolower(guess);
        bool correct = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                correct = true;
            }
        }

        if (!correct) {
            if (find(wrongGuesses.begin(), wrongGuesses.end(), guess) == wrongGuesses.end()) {
                wrongGuesses.push_back(guess);
                attempts--;
            } else {
                cout << "You already guessed that letter!\n";
            }
        }

        if (all_of(guessed.begin(), guessed.end(), [](bool b){ return b; })) {
            cout << "\n🎉 Congrats! You guessed the word: " << word << "\n";
            return 0;
        }
    }

    cout << "\n💀 Game Over! The word was: " << word << "\n";
    return 0;
}
