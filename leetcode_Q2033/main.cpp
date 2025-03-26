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
    int minOperations(vector<vector<int>>& grid, int x) {
        const auto n = size(grid);
        const auto m = size(grid.front());
        const auto nm = n * m;
        vector<int> values(nm);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                values[i * m + j] = grid[i][j];
            }
        }
        const int first = values.front();
        if (any_of(begin(values), end(values), [&](int a)->bool { return abs(first - a) % x != 0;  })) {
            return -1;
        }

        sort(begin(values), end(values));
        auto calc = [&](int v) {
            int count = 0;
            for (auto&& value : values) {
                const auto diff = abs(v - value);
                count += diff / x;
            }
            return count;
            };

        int min_ops = INT_MAX;
        const int check_count = nm % 2 == 0 ? 2 : 1;
        const int center = nm % 2 == 0 ? nm / 2 - 1 : nm / 2;
        for (int i = 0; i < check_count; i++) {
            min_ops = min(min_ops, calc(values[center + i]));
        }
        return min_ops;
    }
};
void test(vector<vector<int>>&& grid, int x) {
    cout << Solution().minOperations(grid, x) << endl;
}
int main() {
    test(get_matrix_int("[[1]]"), 2);
    test(get_matrix_int("[[1],[1]]"), 2);
    test(get_matrix_int("[[2,4],[6,8]]"), 2);
    test(get_matrix_int("[[1,5],[2,3]]"), 1);
    test(get_matrix_int("[[1,2],[3,4]]"), 2);
    return 0;
}