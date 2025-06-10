#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Function to get day of week using Zeller's Congruence
string getDayOfWeek(int day, int month, int year) {
    if(month < 3) {
        month += 12;
        year -= 1;
    }
    int K = year % 100;
    int J = year / 100;

    int h = (day + 13*(month+1)/5 + K + K/4 + J/4 + 5*J) % 7;

    string days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    return days[h];
}

// Function to generate a random date
void generateRandomDate(int &day, int &month, int &year) {
    year = rand() % 202 + 1900; // 1900 - 2101
    month = rand() % 12 + 1;

    // Days in each month
    int daysInMonth[] = {31, (year%4==0 && (year%100!=0 || year%400==0)) ? 29 : 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    day = rand() % daysInMonth[month - 1] + 1;
}

int main() {
    srand(time(0));
    int score = 0;
    char playAgain;

    cout << "🗓️ Welcome to the Calendar Game!" << endl;

    do {
        int day, month, year;
        generateRandomDate(day, month, year);

        cout << "\nWhat day of the week was " << day << "/" << month << "/" << year << "?" << endl;
        cout << "Enter your guess (e.g., Monday): ";
        string guess;
        cin >> guess;

        string correct = getDayOfWeek(day, month, year);

        if(guess == correct) {
            cout << "✅ Correct!" << endl;
            score++;
        } else {
            cout << "❌ Incorrect. It was " << correct << "." << endl;
        }

        cout << "Your current score: " << score << endl;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while(playAgain == 'y' || playAgain == 'Y');

    cout << "\n🎮 Final Score: " << score << ". Thanks for playing!" << endl;

    return 0;
}
