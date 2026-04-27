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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:

    static int tle(vector<vector<int>>& grid, int k) {
        constexpr auto INF = INT_MAX;
        const auto n = size(grid);
        const auto m = size(grid.front());

        vector<int> indexes(n * m);
        for (int i = 0; i < n * m; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](int a, int b) { return grid[a / m][a % m] < grid[b / m][b % m]; });
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k + 1, INF)));
        dp[0][0][0] = 0;

        for (int l = 0; l < k; l++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i < n - 1 && dp[i][j][l] + grid[i + 1][j] < dp[i + 1][j][l]) {
                        dp[i + 1][j][l] = dp[i][j][l] + grid[i + 1][j];
                    }
                    if (j < m - 1 && dp[i][j][l] + grid[i][j + 1] < dp[i][j + 1][l]) {
                        dp[i][j + 1][l] = dp[i][j][l] + grid[i][j + 1];
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    for (int o = 0; o < n * m && grid[indexes[o] / m][indexes[o] % m] <= grid[i][j]; o++) {
                        const auto teldesty = indexes[o] / m;
                        const auto teldestx = indexes[o] % m;
                        if (dp[i][j][l] < dp[teldesty][teldestx][l + 1]) {
                            dp[teldesty][teldestx][l + 1] = dp[i][j][l];
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i < n - 1 && dp[i][j][k] + grid[i + 1][j] < dp[i + 1][j][k]) {
                    dp[i + 1][j][k] = dp[i][j][k] + grid[i + 1][j];
                }
                if (j < m - 1 && dp[i][j][k] + grid[i][j + 1] < dp[i][j + 1][k]) {
                    dp[i][j + 1][k] = dp[i][j][k] + grid[i][j + 1];
                }
            }
        }


        int min_cost = INT_MAX;
        for (auto&& cost : dp.back().back()) {
            min_cost = min(min_cost, cost);
        }
        return min_cost;
    }

    int minCost(vector<vector<int>>& grid, int k) {
        constexpr auto INF = INT_MAX;
        const auto n = size(grid);
        const auto m = size(grid.front());

        vector<int> indexes(n * m);
        for (int i = 0; i < n * m; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](int a, int b) { return grid[a / m][a % m] < grid[b / m][b % m]; });
        vector<vector<vector<int>>> costs(n, vector<vector<int>>(m, vector<int>(k + 1, INF)));


        struct P {
            int cost;
            int y;
            int x;
            int teleported;
            bool operator > (const P& other) const {
                return cost > other.cost;
            }
        };
        std::priority_queue<P, std::vector<P>, std::greater<P>> p_queue;
        p_queue.push(P{ 0, 0,0,0 });
        costs[0][0][0] = 0;
        while (!p_queue.empty()) {
            const auto cur = p_queue.top();
            p_queue.pop();
            if (costs[cur.y][cur.x][cur.teleported] < cur.cost) { continue; }
            if (cur.y == n - 1 && cur.x == m - 1) {
                continue;
            }
            if (cur.y < n - 1 && cur.cost + grid[cur.y + 1][cur.x] < costs[cur.y + 1][cur.x][cur.teleported]) {
                costs[cur.y + 1][cur.x][cur.teleported] = cur.cost + grid[cur.y + 1][cur.x];
                p_queue.push(P{ costs[cur.y + 1][cur.x][cur.teleported] , cur.y+1, cur.x, cur.teleported});
            }
            if (cur.x < m - 1 && cur.cost + grid[cur.y][cur.x + 1] < costs[cur.y][cur.x + 1][cur.teleported]) {
                costs[cur.y][cur.x + 1][cur.teleported] = cur.cost + grid[cur.y][cur.x + 1];
                p_queue.push(P{ costs[cur.y][cur.x + 1][cur.teleported] , cur.y, cur.x + 1, cur.teleported });
            }
            if (cur.teleported < k) {
                for (int o = 0; o < n * m && grid[indexes[o] / m][indexes[o] % m] <= grid[cur.y][cur.x]; o++) {
                    const auto teldesty = indexes[o] / m;
                    const auto teldestx = indexes[o] % m;
                    if (cur.cost < costs[teldesty][teldestx][cur.teleported + 1]) {
                        costs[teldesty][teldestx][cur.teleported + 1] = cur.cost;
                        p_queue.push(P{ costs[cur.y][cur.x + 1][cur.teleported] , cur.y, cur.x + 1, cur.teleported });
                    }
                }
            }
        }
        int min_cost = INT_MAX;
        for (auto&& cost : costs.back().back()) {
            min_cost = min(min_cost, cost);
        }
        return min_cost;
    }

};

static void test(vector<vector<int>>&& grid, int k) {
    cout << Solution().minCost(grid, k) << endl;
}

int main()
{
    test(get_matrix_int("[[1,3,3],[2,5,4],[4,3,5]]"), 2);
    test(get_matrix_int("[[1,2],[2,3],[3,4]]"), 1);

    return 0;
}