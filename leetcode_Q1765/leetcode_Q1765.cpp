// leetcode_Q1765.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        const auto H = size(isWater);
        const auto W = size(isWater.front());
        vector<vector<int>> ans(H, vector<int>(W, -1));
        queue<int> index_queue;

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (isWater[y][x] != 0) {
                    ans[y][x] = 0;
                    index_queue.push(y * W + x);
                }
            }
        }

        const vector<pair<int, int>> directions{
            {-1,0},{1,0},{0,-1},{0,1},
        };

        while (!index_queue.empty()) {
            const auto index = index_queue.front();
            index_queue.pop();
            const auto y = index / W;
            const auto x = index % W;
            const auto next_height = ans[y][x] + 1;
            for (auto&& [dy, dx] : directions) {
                const auto nexty = y + dy;
                const auto nextx = x + dx;
                if (0 <= nexty && nexty < H && 0 <= nextx && nextx < W && ans[nexty][nextx] < 0) {
                    ans[nexty][nextx] = next_height;
                    index_queue.push(nexty * W + nextx);
                }
            }
        }

        return ans;
    }
};

void test(vector<vector<int>>&& isWater) {
    output_matrix(Solution().highestPeak(isWater));
}

int main()
{
    test(get_matrix_int("[[0,1],[0,0]]"));
    test(get_matrix_int("[[0,0,1],[1,0,0],[0,0,0]]"));
    return 0;
}
