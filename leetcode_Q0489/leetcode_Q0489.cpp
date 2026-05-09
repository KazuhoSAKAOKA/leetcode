#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Robot {

private:
    vector<vector<int>> grid;
    vector<vector<bool>> cleaned;
    int H, W;
    int r, c;   // 現在位置
    int dir;    // 0:Up, 1:Right, 2:Down, 3:Left

    const int dr[4] = { -1, 0, 1, 0 };
    const int dc[4] = { 0, 1, 0, -1 };

public:
    Robot(const vector<vector<int>>& g, int sr, int sc)
        : grid(g), cleaned(size(g), vector<bool>(size(g[0]))), r(sr), c(sc), dir(0) // dir=0:Up
    {
        H = grid.size();
        W = grid[0].size();
    }

    // 前進できれば進んで true、壁なら false
    bool move() {
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (nr < 0 || nr >= H || nc < 0 || nc >= W) { return false; }
        if (grid[nr][nc] == 0) { return false; }

        r = nr;
        c = nc;
        return true;
    }

    // 左回転
    void turnLeft() {
        dir = (dir + 3) % 4;
    }

    // 右回転
    void turnRight() {
        dir = (dir + 1) % 4;
    }

    // 現在位置を clean
    void clean() {
        if (grid[r][c] == 1) {
            if (cleaned[r][c]) { throw runtime_error("failed"); }
            cleaned[r][c] = true; 
        }
    }

    // デバッグ用：現在の位置と向きを取得
    int getR() const { return r; }
    int getC() const { return c; }
    int getDir() const { return dir; }

    // デバッグ用：マップを取得（clean 状態確認）
    const vector<vector<int>>& get_map() const { return grid; }
    const vector<vector<bool>>& get_cleaned() const { return cleaned; }

    bool check() const {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (grid[i][j] == 1 && !cleaned[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

};


using point_t = pair<int, int>;

static inline point_t operator +(const point_t& p1, const point_t& p2) {
    return point_t{ p1.first + p2.first, p1.second + p2.second };
}
static inline point_t operator -(const point_t& p1, const point_t& p2) {
    return point_t{ p1.first - p2.first, p1.second - p2.second, };
}
static inline point_t operator * (const point_t& p, long long scaler) {
    return point_t{ p.first * scaler, p.second * scaler, };
}
const point_t UP_DIR{ -1,0 };
const point_t DOWN_DIR{ 1,0 };
const point_t LEFT_DIR{ 0,-1 };
const point_t RIGHT_DIR{ 0, 1 };

const vector<point_t> directions{ UP_DIR,RIGHT_DIR, DOWN_DIR,LEFT_DIR, };
enum class direction {
    up,right,down,left,
};
const map<direction, point_t> direction_map{ {direction::up, UP_DIR},{direction::right, RIGHT_DIR}, {direction::down, DOWN_DIR},{direction::left, LEFT_DIR}, };
enum class action {
    move, turn_right, turn_left, none,
};
const vector<action> actions{action::move,action::turn_right, action::turn_left, };

struct state_t {
    point_t pos;
    direction dir;

    state_t apply(action act) const {
        if (act == action::move) {
            return { pos + direction_map.at(dir), dir };
        }
        else if (act == action::turn_right) {
            return { pos, static_cast<direction>((static_cast<int>(dir) + 1) % 4) };
        }
        else if (act == action::turn_left) {
            return { pos, static_cast<direction>((static_cast<int>(dir) - 1 + 4) % 4) };
        }
        throw runtime_error("");
    }
    point_t get_front() const {
        return pos + direction_map.at(dir);
    }

    state_t reverse(action act) const {
        if (act == action::move) {
            return { pos + (direction_map.at(dir) * -1), dir };
        }
        else if (act == action::turn_left) {
            return { pos, static_cast<direction>((static_cast<int>(dir) + 1) % 4) };
        }
        else if (act == action::turn_right) {
            return { pos, static_cast<direction>((static_cast<int>(dir) - 1 + 4) % 4) };
        }
        throw runtime_error("");
    }
};

bool operator < (const state_t& a, const state_t& b) {
    if (a.pos == b.pos) {
        return a.dir < b.dir;
    }
    return a.pos < b.pos;
}

bool operator == (const state_t& a, const state_t& b) {
    return a.pos == b.pos && a.dir == b.dir;
}
bool operator != (const state_t& a, const state_t& b) {
    return a.pos != b.pos || a.dir != b.dir;
}


class Solution {
public:

    void cleanRoom(Robot& robot) {
        robot.clean();
        set<point_t> obstacles;
        set<point_t> candidates;
        set<point_t> completed{ {0,0} };

        auto add_candidate = [&](const point_t& cur) {
            for (auto&& d : directions) {
                const auto np = cur + d;
                if (obstacles.count(np) == 0 && completed.count(np) == 0) {
                    candidates.insert(np);
                }
            }
            };


        auto get_route = [&](const state_t& state)->vector<action> {
            queue<state_t> q;
            q.push(state);
            map<state_t, action> visited{ {state, action::none} };

            while (!q.empty()) {
                const auto& cur = q.front();
                for (auto&& act : actions) {
                    auto ns = cur.apply(act);
                    if (obstacles.count(ns.pos) == 0 && visited.count(ns) == 0) {
                        if (act == action::move && candidates.count(ns.pos) > 0) {
                            vector<action> path;
                            state_t rev(ns);
                            while (rev != state) {
                                path.push_back(visited[rev]);
                                rev = rev.reverse(path.back());
                            }
                            return vector<action>(crbegin(path), crend(path));
                        }
                        visited.insert({ ns, act });
                        q.push(ns);
                    }
                }
                q.pop();
            }
            throw runtime_error("");
            };

        state_t current{ {0,0}, direction::up };
        add_candidate(current.pos);
        while (!candidates.empty()) {
            const vector<action> route = get_route(current);
            for (auto&& act : route) {
                if (act == action::move) {
                    const auto f = current.get_front();
                    if (completed.count(f) == 0) {
                        candidates.erase(f);
                        if (!robot.move()) {
                            obstacles.insert(f);
                        }
                        else {
                            robot.clean();
                            completed.insert(f);
                            add_candidate(f);
                            current = current.apply(act);
                        }
                        break;
                    }
                    if (!robot.move()) {
                        throw runtime_error("failed");
                    }
                }
                else if (act == action::turn_right) {
                    robot.turnRight();
                }
                else if (act == action::turn_left) {
                    robot.turnLeft();
                }
                else {
                    throw runtime_error("failed");
                }
                current = current.apply(act);
            }
        }
    }
};


static void test(vector<vector<int>>&& grid, int row, int col) {
    Robot r(grid, row, col);
    Solution().cleanRoom(r);
    cout << r.check() << endl;
    if (!r.check()) {
        output_matrix(r.get_map());
        output_matrix(r.get_cleaned());
    }
}

int main() {
    test(get_matrix_int("[[1,1,1,1,1,0,1,1],[1,1,1,1,1,0,1,1],[1,0,1,1,1,1,1,1],[0,0,0,1,0,0,0,0],[1,1,1,1,1,1,1,1]]"), 1, 3);
    test(get_matrix_int("[[1]]"), 0, 0);
    return 0;
}