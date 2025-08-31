// ASCII Pac-Man (console, cross-platform)
// Build: g++ -std=c++17 pacman.cpp -O2 -o pacman
// Run:   ./pacman
// Windows (MSVC): cl /std:c++17 pacman.cpp
// Controls: W/A/S/D to move, Q to quit.

#include <bits/stdc++.h>
#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <fcntl.h>
#endif

using namespace std;

struct Pos { int r, c; };

static const int DR[4] = {-1, 0, 1, 0}; // Up, Right, Down, Left
static const int DC[4] = {0, 1, 0, -1};

#ifdef _WIN32
void sleep_ms(int ms){ Sleep(ms); }
bool kbhit_nonblock(){ return _kbhit(); }
int getch_nonblock(){ return _getch(); }
#else
// Non-blocking keyboard for Unix-like
static struct termios orig_termios;
void reset_terminal_mode(){
    tcsetattr(0, TCSANOW, &orig_termios);
}
void set_conio_terminal_mode(){
    struct termios new_termios;
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));
    // raw mode
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
    atexit(reset_terminal_mode);
}
bool kbhit_nonblock(){
    int oldf = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, oldf | O_NONBLOCK);
    unsigned char ch; int nread = read(0, &ch, 1);
    fcntl(0, F_SETFL, oldf);
    if(nread == 1){
        // stash it for getch_nonblock
        ungetc(ch, stdin);
        return true;
    }
    return false;
}
int getch_nonblock(){
    unsigned char ch;
    if(read(0, &ch, 1) == 1) return ch;
    return -1;
}
void sleep_ms(int ms){ usleep(ms * 1000); }
#endif

void clearScreen(){
    // ANSI clear + home
    cout << "\x1b[2J\x1b[H";
}

struct Ghost {
    Pos p;
    Pos spawn;
    int dir = 1; // 0U,1R,2D,3L
    bool frightened = false;
};

struct Game {
    vector<string> grid;
    int H, W;
    Pos pac;
    int pacDir = 1; // start right
    int score = 0;
    int lives = 3;
    vector<Ghost> ghosts;
    int dotsRemaining = 0;
    int powerTimer = 0; // frames left of power mode
    int tick = 0;

    // Simple classic-ish maze (31x28)
    vector<string> classic = {
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#o####.#####.##.#####.####o#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.##### ## #####.######",
        "     #.##### ## #####.#     ",
        "     #.##          ##.#     ",
        "######.## ###GG### ##.######",
        "........  #      #  ........",
        "######.## ######## ##.######",
        "     #.##          ##.#     ",
        "     #.##### ## #####.#     ",
        "######.##### ## #####.######",
        "#......##....##....##......#",
        "#.####.##.########.##.####.#",
        "#.####.##.########.##.####.#",
        "#o..##................##..o#",
        "###.##.#####.##.#####.##.###",
        "###.##.#####.##.#####.##.###",
        "#......#####.##.#####......#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    };

    void init() {
        // Prepare grid: replace spaces with walls edges kept as is
        grid = classic;
        H = (int)grid.size();
        W = (int)grid[0].size();

        // Place Pac-Man at a fixed start
        pac = {H - 2, 1}; // bottom-left corridor

        // Count dots and set up ghosts where 'G' are
        dotsRemaining = 0;
        ghosts.clear();
        for (int r = 0; r < H; ++r){
            for (int c = 0; c < W; ++c){
                char &ch = grid[r][c];
                if(ch == ' ') ch = '#'; // normalize empty to wall (only tunnels keep spaces)
                if(ch == '.') dotsRemaining++;
                if(ch == 'o') dotsRemaining++;
                if(ch == 'G'){
                    Ghost g; g.p = {r,c}; g.spawn = {r,c};
                    ghosts.push_back(g);
                    ch = ' '; // ghost sits in empty tile
                }
            }
        }
        // Ensure tunnels remain passable (we keep literal spaces there)
        // Already present in the map near the ghost house entrances.
    }

    bool passable(int r,int c) const {
        if(r < 0 || r >= H) return false;
        // horizontal tunnel wrap
        if(c < 0) c = W - 1;
        if(c >= W) c = 0;
        char ch = grid[r][c];
        return ch != '#';
    }

    int wrapC(int c) const {
        if(c < 0) return W - 1;
        if(c >= W) return 0;
        return c;
    }

    // BFS one step from src to dest (avoid walls). Returns next step direction (0..3) or -1 if stuck.
    int bfs_next_step(Pos src, Pos dest){
        if(src.r == dest.r && src.c == dest.c) return -1;
        vector<vector<int>> dist(H, vector<int>(W, -1));
        vector<vector<int>> prv(H, vector<int>(W, -1));
        deque<Pos> dq;

        auto push = [&](int r,int c,int d,int pd){
            c = wrapC(c);
            if(r<0||r>=H) return;
            if(dist[r][c] != -1) return;
            if(grid[r][c] == '#') return;
            dist[r][c] = d; prv[r][c] = pd; dq.push_back({r,c});
        };

        push(src.r, src.c, 0, -2);
        while(!dq.empty()){
            Pos u = dq.front(); dq.pop_front();
            if(u.r == dest.r && u.c == dest.c) break;
            for(int d=0; d<4; ++d){
                int nr = u.r + DR[d];
                int nc = wrapC(u.c + DC[d]);
                if(nr<0||nr>=H) continue;
                if(grid[nr][nc] == '#') continue;
                if(dist[nr][nc] != -1) continue;
                dist[nr][nc] = dist[u.r][u.c] + 1;
                prv[nr][nc] = d;
                dq.push_back({nr,nc});
            }
        }
        if(dist[dest.r][dest.c] == -1){
            // no path; try any valid move that isn't a wall
            for(int d=0; d<4; ++d){
                int nr = src.r + DR[d];
                int nc = wrapC(src.c + DC[d]);
                if(passable(nr,nc)) return d;
            }
            return -1;
        }
        // Reconstruct: walk backwards from dest to src to find the first direction
        int cr = dest.r, cc = dest.c;
        vector<int> path;
        while(!(cr == src.r && cc == src.c)){
            int d = prv[cr][cc];
            if(d == -2) break;
            path.push_back(d);
            cr -= DR[d];
            cc = wrapC(cc - DC[d]);
        }
        if(path.empty()) return -1;
        // The first move from src is the reverse of the last recorded step
        int last = path.back();
        // last is direction used to go forward from src; use it
        return last;
    }

    int farthest_step_away(Pos from, Pos awayFrom){
        // pick the step that maximizes Manhattan distance after moving 1 step
        int bestD = -1, bestDir = -1;
        for(int d=0; d<4; ++d){
            int nr = from.r + DR[d];
            int nc = wrapC(from.c + DC[d]);
            if(!passable(nr,nc)) continue;
            int md = abs(nr - awayFrom.r) + abs((nc - awayFrom.c + W + W) % W);
            if(md > bestD){ bestD = md; bestDir = d; }
        }
        if(bestDir == -1){
            // fallback any passable
            for(int d=0; d<4; ++d){
                int nr = from.r + DR[d];
                int nc = wrapC(from.c + DC[d]);
                if(passable(nr,nc)) return d;
            }
        }
        return bestDir;
    }

    void draw(){
        clearScreen();
        // Header
        cout << "ASCII Pac-Man   Score: " << score << "   Lives: " << lives
             << (powerTimer>0 ? "   POWER!" : "") << "\n";
        // Render with entities
        vector<string> frame = grid;
        // pellets/spaces already in grid, now overlay entities
        frame[pac.r][pac.c] = '@';
        for(auto &g: ghosts){
            char ch = g.frightened ? 'g' : 'G';
            frame[g.p.r][wrapC(g.p.c)] = ch;
        }
        for(string &row : frame){
            cout << row << "\n";
        }
        cout << "Controls: W/A/S/D to move, Q to quit.\n";
    }

    void handleInput(){
        if(!kbhit_nonblock()) return;
        int ch = getch_nonblock();
        if(ch == -1) return;
        ch = tolower(ch);
        if(ch == 'q'){ lives = 0; return; }
        if(ch == 'w') pacDir = 0;
        else if(ch == 'd') pacDir = 1;
        else if(ch == 's') pacDir = 2;
        else if(ch == 'a') pacDir = 3;
    }

    void stepPac(){
        int nr = pac.r + DR[pacDir];
        int nc = wrapC(pac.c + DC[pacDir]);
        if(passable(nr,nc)){
            pac.r = nr; pac.c = nc;
            char &tile = grid[pac.r][pac.c];
            if(tile == '.'){ score += 10; dotsRemaining--; tile = ' '; }
            else if(tile == 'o'){ score += 50; dotsRemaining--; tile = ' '; powerTimer = 200; // ~25s at 8fps
                for(auto &g: ghosts) g.frightened = true;
            }
        }
    }

    void stepGhosts(){
        for(auto &g : ghosts){
            int dir;
            if(powerTimer > 0){
                dir = farthest_step_away(g.p, pac);
            }else{
                dir = bfs_next_step(g.p, pac);
            }
            if(dir != -1){
                int nr = g.p.r + DR[dir];
                int nc = wrapC(g.p.c + DC[dir]);
                if(passable(nr,nc)){ g.p.r = nr; g.p.c = nc; g.dir = dir; }
            }
        }
    }

    void resolveCollisions(){
        for(auto &g : ghosts){
            if(g.p.r == pac.r && wrapC(g.p.c) == wrapC(pac.c)){
                if(powerTimer > 0){
                    score += 200;
                    g.p = g.spawn; // send back to house
                    g.frightened = false;
                }else{
                    // lose life, reset positions
                    lives--;
                    pac = {H - 2, 1};
                    pacDir = 1;
                    for(auto &gg: ghosts){ gg.p = gg.spawn; gg.frightened = false; }
                    powerTimer = 0;
                    sleep_ms(600);
                    break;
                }
            }
        }
    }

    bool isWin() const { return dotsRemaining == 0; }

    void loop(){
#ifndef _WIN32
        set_conio_terminal_mode();
#endif
        const int FPS = 8;
        const int frame_ms = 1000 / FPS;

        while(lives > 0){
            auto t0 = chrono::steady_clock::now();
            handleInput();
            stepPac();
            stepGhosts();
            resolveCollisions();
            if(powerTimer > 0){
                powerTimer--;
                if(powerTimer == 0){
                    for(auto &g: ghosts) g.frightened = false;
                }
            }
            draw();
            if(isWin()){
                cout << "\nYOU WIN! Final score: " << score << "\n";
                return;
            }
            // frame pacing
            auto t1 = chrono::steady_clock::now();
            int elapsed = (int)chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
            int wait = frame_ms - elapsed;
            if(wait > 0) sleep_ms(wait);
            tick++;
        }
        clearScreen();
        cout << "GAME OVER. Final score: " << score << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Game g;
    g.init();
    g.loop();
    return 0;
}
