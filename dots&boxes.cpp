// dots_and_boxes.cpp
// Simple 2-player Dots & Boxes console game
// Compile: g++ -std=c++17 dots_and_boxes.cpp -o dots
// Run: ./dots

#include <bits/stdc++.h>
using namespace std;

int n; // number of dots per row/col (n x n dots)
vector<vector<bool>> hor; // horizontal edges: n rows x (n-1) cols
vector<vector<bool>> ver; // vertical edges: (n-1) rows x n cols
vector<vector<int>> boxOwner; // (n-1) x (n-1), 0 = none, 1 or 2 owner

void drawBoard(){
    // For each dot-row
    for(int r=0;r<n;r++){
        // Print dots and horizontal edges on this dot-row
        for(int c=0;c<n;c++){
            cout << ".";
            if(c < n-1){
                if(hor[r][c]) cout << "---";
                else cout << "   ";
            }
        }
        cout << "\n";
        // Print vertical edges and box contents (for rows that have boxes below)
        if(r < n-1){
            for(int c=0;c<n;c++){
                if(ver[r][c]) cout << "|";
                else cout << " ";
                if(c < n-1){
                    // print box owner or spaces
                    if(boxOwner[r][c] == 0) cout << "   ";
                    else{
                        // show player number in middle
                        cout << " " << boxOwner[r][c] << " ";
                    }
                }
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

// check if a box at (r,c) is completed (all 4 edges present)
bool isBoxComplete(int r, int c){
    // r,c are box coordinates: 0..n-2
    bool top = hor[r][c];
    bool bottom = hor[r+1][c];
    bool left = ver[r][c];
    bool right = ver[r][c+1];
    return top && bottom && left && right;
}

// try to place a horizontal edge at (r,c) where 0<=r<n and 0<=c<n-1
// returns number of boxes completed by this placement (0..2) or -1 if invalid/already placed
int placeHorizontal(int r, int c, int player){
    if(r<0||r>=n||c<0||c>=n-1) return -1;
    if(hor[r][c]) return -1;
    hor[r][c] = true;
    int completed = 0;
    // check box above (r-1,c) if exists
    if(r-1 >= 0 && r-1 < n-1){
        if(boxOwner[r-1][c] == 0 && isBoxComplete(r-1,c)){
            boxOwner[r-1][c] = player;
            completed++;
        }
    }
    // check box below (r,c) if exists
    if(r >= 0 && r < n-1){
        if(boxOwner[r][c] == 0 && isBoxComplete(r,c)){
            boxOwner[r][c] = player;
            completed++;
        }
    }
    return completed;
}

// try to place a vertical edge at (r,c) where 0<=r<n-1 and 0<=c<n
int placeVertical(int r, int c, int player){
    if(r<0||r>=n-1||c<0||c>=n) return -1;
    if(ver[r][c]) return -1;
    ver[r][c] = true;
    int completed = 0;
    // check box left (r,c-1)
    if(c-1 >= 0 && c-1 < n-1){
        if(boxOwner[r][c-1] == 0 && isBoxComplete(r,c-1)){
            boxOwner[r][c-1] = player;
            completed++;
        }
    }
    // check box right (r,c)
    if(c >= 0 && c < n-1){
        if(boxOwner[r][c] == 0 && isBoxComplete(r,c)){
            boxOwner[r][c] = player;
            completed++;
        }
    }
    return completed;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Dots & Boxes (console)\n";
    cout << "Enter grid size (number of dots per row, e.g. 3 for 3x3 dots => 2x2 boxes): ";
    if(!(cin >> n) || n < 2){
        cout << "Invalid size. Exiting.\n";
        return 0;
    }

    // init structures
    hor.assign(n, vector<bool>(n-1, false));
    ver.assign(n-1, vector<bool>(n, false));
    boxOwner.assign(max(0,n-1), vector<int>(max(0,n-1), 0));

    int totalBoxes = (n-1)*(n-1);
    int score1 = 0, score2 = 0;
    int current = 1; // player 1 starts

    cout << "\nMoves format:\n";
    cout << "H r c   -> draw horizontal edge between dot (r,c) and (r,c+1)\n";
    cout << "V r c   -> draw vertical edge between dot (r,c) and (r+1,c)\n";
    cout << "(r and c are 1-based indices)\n\n";

    // main loop
    int moves = 0;
    int maxEdges = n*(n-1)*2; // total edges
    while(moves < maxEdges){
        drawBoard();
        cout << "Score -> Player1: " << score1 << "   Player2: " << score2 << "\n";
        cout << "Player " << current << "'s turn. Enter move: ";

        char type;
        int r,c;
        if(!(cin >> type >> r >> c)){
            cout << "Invalid input. Try again.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // convert to 0-based
        r--; c--;
        int completed = -1;
        if(type == 'H' || type == 'h'){
            completed = placeHorizontal(r, c, current);
        } else if(type == 'V' || type == 'v'){
            completed = placeVertical(r, c, current);
        } else {
            cout << "Unknown type. Use H or V.\n";
            continue;
        }

        if(completed == -1){
            cout << "Invalid move or edge already placed. Try again.\n";
            continue;
        }

        moves++;
        if(completed > 0){
            if(current == 1) score1 += completed;
            else score2 += completed;
            cout << "Nice! Player " << current << " completed " << completed << " box";
            if(completed>1) cout << "es";
            cout << " and gets another turn.\n";
            // current player goes again (do not toggle)
        } else {
            // switch player
            current = (current == 1 ? 2 : 1);
        }
    }

    // game over
    drawBoard();
    cout << "Final Score -> Player1: " << score1 << "   Player2: " << score2 << "\n";
    if(score1 > score2) cout << "Player 1 wins!\n";
    else if(score2 > score1) cout << "Player 2 wins!\n";
    else cout << "It's a tie!\n";

    return 0;
}
