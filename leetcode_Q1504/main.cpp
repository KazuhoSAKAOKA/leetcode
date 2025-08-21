#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        const auto H = size(mat);
        const auto W = size(mat.front());
        vector<vector<int>> prefix_sums(H + 1, vector<int>(W + 1));

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + mat[i][j];
            }
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto get_sums = [&](int sy, int sx, int ey, int ex) {
            return prefix_sums[ey][ex] - prefix_sums[ey][sx] - prefix_sums[sy][ex] + prefix_sums[sy][sx];
            };


        int count = 0;
        for (int sy = 0; sy < H; sy++) {
            for (int sx = 0; sx < W; sx++) {
                for (int ey = sy + 1; ey <= H; ey++) {
                    for (int ex = sx + 1; ex <= W; ex++) {
                        const auto expected = (ey - sy) * (ex - sx);
                        const auto actual = get_sums(sy, sx, ey, ex);
                        if (expected == actual) {
                            count++;
                        }
                    }
                }
            }
        }
        return count;
    }
};

static void test(vector<vector<int>>&& mat) {
    cout << Solution().numSubmat(mat) << endl;
}

int main() {
    test(get_matrix_int("[[1,0,1],[1,1,0],[1,1,0]]"));
    test(get_matrix_int("[[0,1,1,0],[0,1,1,1],[1,1,1,0]]"));
    return 0;
}