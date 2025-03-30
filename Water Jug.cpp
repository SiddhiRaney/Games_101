#include <iostream>
#include <queue>
#include <set>
using namespace std;

// State representation
struct State {
    int jug1, jug2;
    State(int a, int b) : jug1(a), jug2(b) {}
};

// Check if the target is reached
bool isGoal(State s, int target) {
    return (s.jug1 == target || s.jug2 == target);
}

// BFS to solve the problem
void solveWaterJug(int cap1, int cap2, int target) {
    set<pair<int, int>> visited;
    queue<pair<State, string>> q;
    
    // Initial state (0, 0)
    q.push({State(0, 0), ""});
    
    while (!q.empty()) {
        auto front = q.front();
        State s = front.first;
        string steps = front.second;
        q.pop();
        
        // Check goal
        if (isGoal(s, target)) {
            cout << "Steps to reach the target:\n" << steps << endl;
            return;
        }
        
        // Skip if state is already visited
        if (visited.count({s.jug1, s.jug2})) 
            continue;
        
        visited.insert({s.jug1, s.jug2});
        
        // Generate possible moves
        q.push({State(cap1, s.jug2), steps + "Fill Jug1\n"});
        q.push({State(s.jug1, cap2), steps + "Fill Jug2\n"});
        q.push({State(0, s.jug2), steps + "Empty Jug1\n"});
        q.push({State(s.jug1, 0), steps + "Empty Jug2\n"});
        
        // Transfer Jug1 -> Jug2
        int pour = min(s.jug1, cap2 - s.jug2);
        q.push({State(s.jug1 - pour, s.jug2 + pour), steps + "Pour Jug1 -> Jug2\n"});
        
        // Transfer Jug2 -> Jug1
        pour = min(s.jug2, cap1 - s.jug1);
        q.push({State(s.jug1 + pour, s.jug2 - pour), steps + "Pour Jug2 -> Jug1\n"});
    }
    
    cout << "No solution possible.\n";
}

int main() {
    int cap1, cap2, target;
    cout << "Enter capacity of Jug1, Jug2 and target: ";
    cin >> cap1 >> cap2 >> target;
    
    solveWaterJug(cap1, cap2, target);
    return 0;
}
