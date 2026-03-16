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
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        const auto n = static_cast<int>(size(grid));
        const auto m = static_cast<int>(size(grid.front()));
        set<int> sums;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int len = 0;
                while (
                    ((i - len) >= 0) && ((i + len) < n) &&
                    ((j - len) >= 0) && ((j + len) < m)
                    ) {
                    int sum = 0;
                    sum += grid[i - len][j];
                    for (int k = 1; k <= len; k++) {
                        sum += grid[i - len + k][j - k];
                        sum += grid[i - len + k][j + k];
                    }
                    if (len > 0) {
                        sum += grid[i + len][j];
                    }
                    for (int k = 1; k < len; k++) {
                        sum += grid[i + len - k][j - k];
                        sum += grid[i + len - k][j + k];
                    }
                    sums.insert(sum);
                    if (size(sums) > 3) {
                        sums.erase(cbegin(sums));
                    }
                    len += 1;
                }
            }
        }
        vector<int> ans(crbegin(sums), crend(sums));
        return ans;
    }
};

static void test(vector<vector<int>>&& grid) {
    output(Solution().getBiggestThree(grid));
}

int main() {
    test(get_matrix_int("[[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]"));
    test(get_matrix_int("[[1,2,3],[4,5,6],[7,8,9]]"));
    test(get_matrix_int("[[7,7,7]]"));
    return 0;
}
