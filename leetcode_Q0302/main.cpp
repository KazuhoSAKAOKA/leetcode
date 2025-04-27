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
    int minArea(vector<vector<char>>& image, int x, int y) {
        const auto X = size(image);
        const auto Y = size(image.front());
        int min_x = INT_MAX;
        int max_x = 0;
        int min_y = INT_MAX;
        int max_y = 0;

        const vector<pair<int, int>> dirs{
            {-1,0},{1,0},{0,-1},{0,1},
        };
        vector<vector<bool>> visited(X, vector<bool>(Y));
        queue<pair<int, int>> q;
        visited[x][y] = true;
        q.push({ x,y });
        while (!q.empty()) {
            const auto [cur_x, cur_y] = q.front();
            q.pop();
            min_x = min(min_x, cur_x);
            max_x = max(max_x, cur_x);
            min_y = min(min_y, cur_y);
            max_y = max(max_y, cur_y);

            for (auto&& [dx, dy] : dirs) {
                const auto nextx = cur_x + dx;
                const auto nexty = cur_y + dy;
                if (0 <= nextx && nextx < X && 0 <= nexty && nexty < Y && !visited[nextx][nexty] && image[nextx][nexty] == '1') {
                    visited[nextx][nexty] = true;
                    q.push({ nextx,nexty });
                }
            }
        }

        return (max_x - min_x + 1) * (max_y - min_y + 1);
    }
};
void test(vector<vector<char>>&& image, int x, int y) {
    cout << Solution().minArea(image, x, y) << endl;
}
int main() {
    test(get_matrix_char(R"([["0","0","1","0"],["0","1","1","0"],["0","1","0","0"]],)"), 0, 2);
	return 0;
}