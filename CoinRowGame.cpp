// DP - Greedy
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Display coins from current left to right index
void displayCoins(const vector<int>& coins, int left, int right) {
    cout << "Current coins: ";
    for (int i = left; i <= right; ++i) {
        cout << coins[i] << " ";
    }
    cout << "\n";
}

// Dynamic Programming function to calculate the best possible score
int optimalMove(const vector<int>& coins, int l, int r, vector<vector<int>>& dp) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];

    int pickLeft = coins[l] + min(optimalMove(coins, l+2, r, dp), optimalMove(coins, l+1, r-1, dp));
    int pickRight = coins[r] + min(optimalMove(coins, l+1, r-1, dp), optimalMove(coins, l, r-2, dp));

    return dp[l][r] = max(pickLeft, pickRight);
}

// --------------------
// Mode 1: User vs Computer
// --------------------
void singlePlayer(vector<int> coins) {
    int l = 0, r = coins.size() - 1;
    int userScore = 0, compScore = 0;
    vector<vector<int>> dp(coins.size(), vector<int>(coins.size(), -1));

    while (l <= r) {
        displayCoins(coins, l, r);
        int choice;

        // User's move
        cout << "\nYour turn: Pick a coin\n1. Left (" << coins[l] << ")  2. Right (" << coins[r] << "): ";
        cin >> choice;
        if (choice == 1) {
            userScore += coins[l++];
        } else if (choice == 2) {
            userScore += coins[r--];
        } else {
            cout << "Invalid! Try again.\n";
            continue;
        }

        if (l > r) break;

        // Computer's move using DP
        int pickLeft = coins[l] + min(optimalMove(coins, l+2, r, dp), optimalMove(coins, l+1, r-1, dp));
        int pickRight = coins[r] + min(optimalMove(coins, l+1, r-1, dp), optimalMove(coins, l, r-2, dp));

        if (pickLeft >= pickRight) {
            cout << "\nComputer picks LEFT: " << coins[l] << "\n";
            compScore += coins[l++];
        } else {
            cout << "\nComputer picks RIGHT: " << coins[r] << "\n";
            compScore += coins[r--];
        }
    }

    // Final scores
    cout << "\nFinal Scores:\nYou: " << userScore << "  |  Computer: " << compScore << "\n";
    if (userScore > compScore)
        cout << "🎉 You win!\n";
    else if (userScore < compScore)
        cout << "💻 Computer wins!\n";
    else
        cout << "🤝 It's a tie!\n";
}

// --------------------
// Mode 2: Player vs Player
// --------------------
void twoPlayer(vector<int> coins) {
    int l = 0, r = coins.size() - 1;
    int p1 = 0, p2 = 0;
    bool isP1 = true;

    while (l <= r) {
        displayCoins(coins, l, r);
        cout << "\n" << (isP1 ? "Player 1" : "Player 2") << "'s turn.\n";
        int choice;
        cout << "Pick a coin\n1. Left (" << coins[l] << ")  2. Right (" << coins[r] << "): ";
        cin >> choice;

        if (choice == 1) {
            (isP1 ? p1 : p2) += coins[l++];
        } else if (choice == 2) {
            (isP1 ? p1 : p2) += coins[r--];
        } else {
            cout << "Invalid! Try again.\n";
            continue;
        }

        isP1 = !isP1;
    }

    // Final scores
    cout << "\nFinal Scores:\nPlayer 1: " << p1 << "  |  Player 2: " << p2 << "\n";
    if (p1 > p2)
        cout << "🏆 Player 1 wins!\n";
    else if (p1 < p2)
        cout << "🏆 Player 2 wins!\n";
    else
        cout << "🤝 It's a tie!\n";
}

// --------------------
// Main Menu
// --------------------
int main() {
    int choice;

    // Predefined coins row - you can change or randomize
    vector<int> coins = {3, 9, 1, 2, 8, 7};

    // Print rules using printf
    printf("====================================\n");
    printf("        🎮 COIN ROW GAME 🎮\n");
    printf("====================================\n");
    printf("RULES:\n");
    printf("1. A row of coins is placed on the table, each with a specific value.\n");
    printf("2. Two players take turns to pick coins from either LEFT or RIGHT end.\n");
    printf("3. Each player tries to maximize their total value.\n");
    printf("4. In Single Player mode, the computer plays optimally using logic.\n");
    printf("5. Game ends when all coins are picked. Highest score wins!\n");
    printf("====================================\n");

    while (true) {
        cout << "\n======= MAIN MENU =======\n";
        cout << "Choose a mode:\n";
        cout << "1. Single Player (You vs Computer)\n";
        cout << "2. Two Player (Player 1 vs Player 2)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
            singlePlayer(coins);
        else if (choice == 2)
            twoPlayer(coins);
        else if (choice == 3) {
            cout << "Thanks for playing!\n";
            break;
        } else
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
    }

    return 0;
}
