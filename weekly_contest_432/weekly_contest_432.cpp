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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:

    static tuple<int, int, int> get_next(int x, int y, int dx, int W, int H) {
        const int new_x = x + dx * 2;
        if (dx < 0 && new_x < 0) {
            if (y + 1 == H) {
                return { -1,-1, dx };
            }
            if (x == 0) {
                return { 1, y + 1, -dx };
            }
            else {
                return { 0, y + 1, -dx };
            }
        }
        else if(dx > 0 && new_x >= W) {
            if (y + 1 == H) {
                return { -1,-1 ,0 };
            }
            if (x == W - 2) {
                return { W - 1, y + 1, -dx };
            }
            else {
                return { W - 2, y + 1, -dx };
            }
        }
        return { new_x, y, dx };
    }

    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        vector<int> ans;
        const int W = size(grid.front());
        const int H = size(grid);

        int x = 0;
        int y = 0;
        int current_dx = 1;
        ans.emplace_back(grid[y][x]);
        for (;;) {
            const auto [new_x, new_y, new_dx] = get_next(x, y, current_dx, W, H);
            if (new_x < 0) {
                break;
            }
            ans.emplace_back(grid[new_y][new_x]);
            x = new_x;
            y = new_y;
            current_dx = new_dx;
        }
        return ans;
    }
}; 

static void test(vector<vector<int>>&& grid) {
    output(Solution().zigzagTraversal(grid));
}

static void run() {
    test(get_matrix_int("[[1,2],[3,4]]"));
    test(get_matrix_int("[[2,1],[2,1],[2,1]]"));
    test(get_matrix_int("[[1,2,3],[4,5,6],[7,8,9]]"));
}
}
namespace problem2 {
class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        const auto H = size(coins);
        const auto W = size(coins.front());

        vector<vector<vector<int>>> dp(H, vector<vector<int>>(W, vector<int>(3, -1000000)));

        dp[0][0][2] = coins[0][0];
        if (coins[0][0] < 0) {
            dp[0][0][1] = 0;
        }

        for (int j = 1; j < W; j++) {
            dp[0][j][2] = dp[0][j - 1][2] + coins[0][j];
            dp[0][j][1] = dp[0][j - 1][1] + coins[0][j];
            dp[0][j][0] = dp[0][j - 1][0] + coins[0][j];
            if (coins[0][j] < 0) {
                dp[0][j][1] = max(dp[0][j][1], dp[0][j - 1][2]);
                dp[0][j][0] = max(dp[0][j][0], dp[0][j - 1][1]);
            }
        }

        for (int i = 1; i < H; i++) {
            dp[i][0][2] = dp[i - 1][0][2] + coins[i][0];
            dp[i][0][1] = dp[i - 1][0][1] + coins[i][0];
            dp[i][0][0] = dp[i - 1][0][0] + coins[i][0];
            if (coins[i][0] < 0) {
                dp[i][0][1] = max(dp[i][0][1], dp[i - 1][0][2]);
                dp[i][0][0] = max(dp[i][0][0], dp[i - 1][0][1]);
            }
        }

        for (int i = 1; i < H; i++) {
            for (int j = 1; j < W; j++) {
                dp[i][j][2] = max(dp[i][j - 1][2], dp[i - 1][j][2]) + coins[i][j];
                dp[i][j][1] = max(dp[i][j - 1][1], dp[i - 1][j][1]) + coins[i][j];
                dp[i][j][0] = max(dp[i][j - 1][0], dp[i - 1][j][0]) + coins[i][j];
                if (coins[i][j] < 0) {
                    dp[i][j][1] = max(dp[i][j][1], max(dp[i][j - 1][2], dp[i - 1][j][2]));
                    dp[i][j][0] = max(dp[i][j][0], max(dp[i][j - 1][1], dp[i - 1][j][1]));
                }
            }
        }

        for (auto&& list : dp) {
            for (auto&& list1 : list) {
                cout << "[";
                for (auto&& value : list1) {
                    cout << value << ",";
                }
                cout << "],";
            }
            cout << endl;
        }


        int max_profit = -1000000;
        for (int i = 0; i < 3; i++) {
            max_profit = max(max_profit, dp[H - 1][W - 1][i]);
        }
        return max_profit;
    }
}; 

static void test(vector<vector<int>>&& coins) {
    cout << Solution().maximumAmount(coins) << endl;
}
static void run() {
    test(get_matrix_int("[[-16,-18],[-18,-14]]"));
    test(get_matrix_int("[[-7,12,12,13],[-6,19,19,-6],[9,-2,-10,16],[-4,14,-10,-9]]"));
    test(get_matrix_int("[[6,-16],[0,-18]]"));
    test(get_matrix_int("[[-4]]"));
    test(get_matrix_int("[[0,1,-1],[1,-2,3],[2,-3,4]]"));
    test(get_matrix_int("[[10,10,10],[10,10,10]]"));
}
}
namespace problem3 {
class Solution {
public:

    static bool dfs(int n, const vector<vector<pair<int, int>>>& graph, set<int>& visited, int threshold, int limit, int node) {    
        visited.insert(node);
        if (size(visited) == n) {
            return true;
        }

        for (auto&& [to, weight] : graph[node]) {
            if (visited.count(to) == 0 && weight <= limit) {
                if (dfs(n, graph, visited, threshold, limit, to)) {
                    return true;
                }
            }
        }
        return false;
    }


    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        vector<vector<pair<int, int>>> graph(n);
        int max_weight = 0;
        for (auto&& edge : edges) {
            const auto u = edge[0];
            const auto v = edge[1];
            const auto w = edge[2];
            graph[v].push_back({ u, w });
            max_weight = max(max_weight, w);
        }
        set<int> visited1;
        if (!dfs(n, graph, visited1, threshold, max_weight, 0)) {
            return -1;
        }
        auto check = [&](int limit)->bool {
            set<int> visited;
            return dfs(n, graph, visited, threshold, limit, 0);
            };
        auto binary_search_meguru = [&](int ok, int ng) {
            while (abs(ng - ok) > 1) {
                const auto mid = (ok + ng) / 2;
                if (check(mid)) {
                    ok = mid;
                }
                else {
                    ng = mid;
                }
            }
            return ok;
            };

        auto ans = binary_search_meguru(max_weight, -1);
        return ans;
    }
}; 

void test(int n, vector<vector<int>>&& edges, int threshold) {
    cout << Solution().minMaxWeight(n, edges, threshold) << endl;
}

static void run() {
    test(5, get_matrix_int("[[0,1,1],[0,2,2],[0,3,1],[0,4,1],[1,2,1],[1,4,1]]"), 1);
    test(5, get_matrix_int("[[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]]"), 2);
    test(5, get_matrix_int("[[1,2,1],[1,3,3],[1,4,5],[2,3,2],[3,4,2],[4,0,1]]"), 1);
    test(5, get_matrix_int("[[1,2,1],[1,3,3],[1,4,5],[2,3,2],[4,0,1]]"), 1);
}
}
namespace problem4 {
    static void run() {
    }
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}