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


    int snakesAndLadders(vector<vector<int>>& board) {
        const auto n = static_cast<int>(size(board));
        auto get_coodinate = [&](int no)->pair<int, int> {
            const auto row = (no - 1) / n;
            const auto y = n - row - 1;
            int x = (no - 1) % n;
            if (row % 2 != 0) {
                x = n - x - 1;
            }
            return { y,x };
            };
        vector<vector<int>> cost(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        q.push({ 0, 1 });
        cost[n - 1][0] = 0;
        while (!q.empty()) {
            const auto [step, current] = q.front();
            q.pop();
            if (current == n * n) {
                return step;
            }
            const auto next_step = step + 1;
            for (int next = current + 1; next <= min(current + 6, n * n); next++) {
                const auto [nexty, nextx] = get_coodinate(next);
                if (board[nexty][nextx] != -1) {
                    const auto [skipy, skipx] = get_coodinate(board[nexty][nextx]);
                    if (cost[skipy][skipx] > next_step) {
                        cost[skipy][skipx] = next_step;
                        q.push({ next_step, board[nexty][nextx] });
                    }
                }
                else {
                    if (cost[nexty][nextx] > next_step) {
                        cost[nexty][nextx] = next_step;
                        q.push({ next_step, next });
                    }
                }
            }
        }
        return -1;
    }
};
void test(vector<vector<int>>&& board) {
    cout << Solution().snakesAndLadders(board) << endl;
}
int main() {
    test(get_matrix_int("[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]"));
    test(get_matrix_int("[[1,1,-1],[1,1,1],[-1,1,1]]"));
    test(get_matrix_int("[[-1,-1,-1,46,47,-1,-1,-1],[51,-1,-1,63,-1,31,21,-1],[-1,-1,26,-1,-1,38,-1,-1],[-1,-1,11,-1,14,23,56,57],[11,-1,-1,-1,49,36,-1,48],[-1,-1,-1,33,56,-1,57,21],[-1,-1,-1,-1,-1,-1,2,-1],[-1,-1,-1,8,3,-1,6,56]]"));
	return 0;
}