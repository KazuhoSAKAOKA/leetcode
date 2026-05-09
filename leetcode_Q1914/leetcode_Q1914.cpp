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

class Solution {
public:

    static int get_index(int height, int width, int y, int x) {
        if (x == 0) {
            return y;
        }
        else if (y == height - 1) {
            return x + (height - 1);
        }
        else if (x == width - 1) {
            return (height - y - 1) + ((height - 1) + (width - 1));
        }
        else if (y == 0) {
            return (width - x - 1) + ((height - 1) + (width - 1) + (height - 1));
        }
        throw runtime_error("");
    }

    static pair<int,int> get_xy(int height, int width, int index) {
        if (index <= (height - 1)) {
            return { index, 0 };
        }
        else if (index <= ((height - 1) + (width - 1))) {
            return { height - 1, index - (height - 1) };
        }
        else if (index <= ((height - 1) + (width - 1) + (height - 1))) {
            return { ((height - 1) + (width - 1) + (height - 1)) - index, width - 1 };
        }
        else if (index <= ((height - 1) + (width - 1) + (height - 1) + (width - 1))) {
            return { 0, ((height - 1) + (width - 1) + (height - 1) + (width - 1)) - index };
        }
        throw runtime_error("");
    }


    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        const auto n = size(grid);
        const auto m = size(grid.front());
        const auto layers = min(n, m) / 2;
        vector<vector<int>> ans(n, vector<int>(m));

        for (int i = 0; i < layers; i++) {
            const int height = n - i * 2;
            const int width = m - i * 2;

            const int count = ((height - 1) + (width - 1) + (height - 1) + (width - 1));
            for (int index = 0; index < count; index++) {
                const auto [basey, basex] = get_xy(height, width, index);
                const auto val = grid[basey + i][basex + i];
                const auto target_index = (index + k) % count;
                const auto [targety, targetx] = get_xy(height, width, target_index);
                ans[targety + i][targetx + i] = val;
            }
        }
        return ans;
    }
};

static void test(vector<vector<int>>&& grid, int k) {
    output_matrix(Solution().rotateGrid(grid, k));
}
int main() {

    //for (int i = 0; i < 14; i++) {
    //    const auto [y, x] = Solution::get_xy(5, 4, i);
    //    const auto index = Solution::get_index(5, 4, y, x);
    //    cout << i << ":" << "(" << y << "," << x << "):" << index << endl;
    //}

    test(get_matrix_int("[[40,10],[30,20]]"), 1);
    test(get_matrix_int("[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]"), 2);
    return 0;
}
