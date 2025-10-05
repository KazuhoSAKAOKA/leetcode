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

    static vector<vector<bool>> bfs(const vector<vector<int>>& heights, vector<pair<int,int>>& starts) {
        const auto n = size(heights);
        const auto m = size(heights.front());
        vector<vector<bool>> from_cells(n, vector<bool>(m));
        vector<vector<bool>> visited(n, vector<bool>(m));
        queue<pair<int, int>> q;
        for (auto&& [y, x] : starts) {
            visited[y][x] = true;
            from_cells[y][x] = true;
            q.push({ y,x });
        }
        static const vector<pair<int, int>> dirs{
            {-1,0},{1,0}, {0,-1}, {0,1},
        };

        while (!q.empty()) {
            const auto [y, x] = q.front();
            q.pop();
            for (auto&& [dy, dx] : dirs) {
                const auto ny = y + dy;
                const auto nx = x + dx;
                if (0 <= ny && ny < n && 0 <= nx && nx < m && !visited[ny][nx] && heights[y][x] <= heights[ny][nx]) {
                    visited[ny][nx] = true;
                    from_cells[ny][nx] = true;
                    q.push({ ny,nx });
                }
            }
        }
        return from_cells;
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const auto n = size(heights);
        const auto m = size(heights.front());
        vector<pair<int, int>> starts_pacifics;
        starts_pacifics.reserve(n + m);
        vector<pair<int, int>> starts_atlantics;
        starts_atlantics.reserve(n + m);
        for (int i = 0; i < n; i++) {
            starts_pacifics.emplace_back(make_pair(i, 0));
            starts_atlantics.emplace_back(make_pair(i, m - 1));
        }
        for (int j = 0; j < m; j++) {
            starts_pacifics.emplace_back(make_pair(0, j));
            starts_atlantics.emplace_back(make_pair(n - 1, j));
        }
        const vector<vector<bool>> pacifics = bfs(heights, starts_pacifics);
        const vector<vector<bool>> atlantics = bfs(heights, starts_atlantics);
        
        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacifics[i][j] && atlantics[i][j]) {
                    ans.emplace_back(vector<int>{i, j});
                }
            }
        }


        return ans;
    }
};

static void test(vector<vector<int>>&& heights) {
    output_matrix(Solution().pacificAtlantic(heights));
}
int main() {
    test(get_matrix_int("[[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]"));
    test(get_matrix_int("[[1]]"));
    return 0;
}