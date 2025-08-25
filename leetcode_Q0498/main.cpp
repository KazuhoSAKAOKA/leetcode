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
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> ans;
        const int h = size(mat);
        const int w = size(mat.front());
        ans.reserve(h * w);

        int y = 0;
        int x = 0;
        vector<pair<int, int>> dxys{
            {-1,1},{1,-1},
        };
        int cur_index = 0;
        ans.emplace_back(mat[0][0]);
        while (size(ans) < h * w) {
            const auto& [dy, dx] = dxys[cur_index];
            y += dy;
            x += dx;
            if (y < 0 || h <= y || x < 0 || w <= x) {
                if (cur_index == 0) {
                    x++;
                }
                else {
                    y++;
                }

                cur_index++;
                cur_index %= size(dxys);

                const auto& [dy1, dx1] = dxys[cur_index];
                while (y < 0 || h <= y || x < 0 || w <= x) {
                    y += dy1;
                    x += dx1;
                }
            }
            ans.emplace_back(mat[y][x]);
        }
        return ans;
    }
};

static void test(vector<vector<int>>&& mat) {
    output(Solution().findDiagonalOrder(mat));
}

int main() {
    test(get_matrix_int("[[1,2],[3,4]]"));
    test(get_matrix_int("[[1,2,3],[4,5,6],[7,8,9]]"));
    return 0;
}