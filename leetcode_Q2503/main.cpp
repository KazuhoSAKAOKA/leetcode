#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        const auto n = size(grid);
        const auto m = size(grid.front());
        const auto k = size(queries);
        vector<int> indexes(k);
        for (int i = 0; i < k; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](const auto& a, const auto& b) { return queries[a] < queries[b]; });

        int current_point = 0;
        vector<vector<bool>> visited(n, vector<bool>(m));
        auto compare = [&](const int& a, const int& b) {
            return grid[a / m][a % m] > grid[b / m][b % m];
            };
        priority_queue<int, vector<int>, decltype(compare)> pq(compare);
        pq.push(0);
        visited[0][0] = true;

        vector<int> ans(k);
        int ans_index = 0;

        const vector<pair<int, int>> directions = { {-1,0},{1,0},{0,-1},{0,1}, };

        while (!pq.empty()) {
            const auto current = pq.top();
            const auto y = current / m;
            const auto x = current % m;
            pq.pop();
            while (grid[y][x] >= queries[indexes[ans_index]]) {
                ans[indexes[ans_index]] = current_point;
                ans_index++;
                if (k == ans_index) {
                    return ans;
                }
            }
            current_point++;
            for (auto&& [dy,dx] : directions) {
                const auto nexty = y + dy;
                const auto nextx = x + dx;
                if (0 <= nexty && nexty < n && 0 <= nextx && nextx < m && !visited[nexty][nextx]) {
                    visited[nexty][nextx] = true;
                    pq.push(nexty * m + nextx);
                }
            }
        }
        while (ans_index < k) {
            ans[indexes[ans_index]] = current_point;
            ans_index++;
        }
        return ans;
    }
};
void test(vector<vector<int>>&& grid, vector<int>&& queries) {
    output(Solution().maxPoints(grid, queries));
}
int main() {
    test(get_matrix_int("[[1,2,3],[2,5,7],[3,5,1]]"), get_list_int("[5,6,2]"));
    test(get_matrix_int("[[5,2,1],[1,1,2]]"), get_list_int("[3]"));
    return 0;
}