#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int playInnings(string teamName, int overs) {
    int totalRuns = 0;
    int balls = overs * 6;
    
    cout << "\n== " << teamName << " is batting ==" << endl;

    for (int ball = 1; ball <= balls; ++ball) {
        int run = rand() % 8; // Random run from 0 to 7 (where 7 is a wicket)

        if (run == 7) {
            cout << "Ball " << ball << ": WICKET!" << endl;
        } else {
            totalRuns += run;
            cout << "Ball " << ball << ": " << run << " runs" << endl;
        }

        // Optional: stop if 10 wickets fall
        // (Can add a wicket counter and break here if needed)
    }

    cout << teamName << " scored: " << totalRuns << " runs.\n";
    return totalRuns;
}

int main() {
    srand(time(0)); // Seed random number generator

    string team1 = "Punjab Kings";
    string team2 = "Royal Challengers Bangalore";
    int overs = 2;

    cout << "🏏 Welcome to IPL Match Simulation: Punjab Kings vs RCB 🏏\n";
    cout << "Match Format: " << overs << " overs per side\n";

    // Team 1 bats
    int score1 = playInnings(team1, overs);

    // Team 2 bats
    int score2 = playInnings(team2, overs);

    // Match Result
    cout << "\n Match Result:\n";
    cout << team1 << ": " << score1 << " runs\n";
    cout << team2 << ": " << score2 << " runs\n";

    if (score1 > score2)
        cout << "🏆 " << team1 << " wins by " << (score1 - score2) << " runs!" << endl;
    else if (score2 > score1)
        cout << "🏆 " << team2 << " wins by " << (score2 - score1) << " runs!" << endl;
    else
        cout << "🤝 It's a TIE!" << endl;

    return 0;
}
