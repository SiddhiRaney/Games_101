#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct Node {
    vector<vector<int>> board;
    int x, y, cost, level;
    string path;

    bool operator>(const Node& other) const {
        return (cost + level) > (other.cost + other.level);
    }
};

int calculateCost(vector<vector<int>>& start, vector<vector<int>>& goal) {
    int cost = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (start[i][j] != 0 && start[i][j] != goal[i][j])
                cost++;
    return cost;
}

bool isValid(int x, int y) {
    return (x >= 0 && x < 3 && y >= 0 && y < 3);
}

void printBoard(vector<vector<int>>& board) {
    for (auto& row : board) {
        for (int cell : row)
            cout << cell << " ";
        cout << "\n";
    }
    cout << "\n";
}

void solve(vector<vector<int>>& start, vector<vector<int>>& goal, int x, int y) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<vector<vector<int>>> visited;

    int row[] = {1, 0, -1, 0};
    int col[] = {0, -1, 0, 1};
    string moves[] = {"D", "L", "U", "R"};

    pq.push({start, x, y, calculateCost(start, goal), 0, ""});
    visited.insert(start);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.cost == 0) {
            cout << "Solution Found in " << node.level << " moves!\n";
            cout << "Path: " << node.path << "\n";
            printBoard(node.board);
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = node.x + row[i], newY = node.y + col[i];

            if (isValid(newX, newY)) {
                vector<vector<int>> newBoard = node.board;
                swap(newBoard[node.x][node.y], newBoard[newX][newY]);

                if (visited.find(newBoard) == visited.end()) {
                    pq.push({newBoard, newX, newY, calculateCost(newBoard, goal), node.level + 1, node.path + moves[i]});
                    visited.insert(newBoard);
                }
            }
        }
    }

    cout << "No solution found!\n";
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
    vector<vector<int>> goal = {{1, 2, 3}, {5, 8, 6}, {0, 7, 4}};

    int x = 1, y = 2;
    solve(start, goal, x, y);

    return 0;
}
