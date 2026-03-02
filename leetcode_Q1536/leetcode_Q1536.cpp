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
    int minSwaps(vector<vector<int>>& grid) {
        const auto n = size(grid);
        vector<int> right_zeros(n);
        auto zero_counting = [](const vector<int>& row) {
            size_t c = 0;
            for (auto it = crbegin(row); it != crend(row); ++it) {
                if (*it != 0) {
                    return c;
                }
                c++;
            }
            return c;
            };
        for (size_t i = 0; i < n; i++) {
            const auto& row = grid[i];
            right_zeros[i] = zero_counting(row);
        }
        vector<bool> used(n);
        vector<int> indexes(n);
        for (int i = 0; i < n; i++) {
            const auto required = n - i - 1;
            auto find_pos = [&]()->int {
                for (int j = 0; j < n; j++) {
                    if (!used[j] && required <= right_zeros[j]) {
                        return j;
                    }
                }
                return -1;
                };
            indexes[i] = find_pos();
            if (indexes[i] < 0) {
                return -1;
            }
            used[indexes[i]] = true;
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            int c1 = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (indexes[i] < indexes[j]) {
                    c1++;
                }
            }
            count += c1;
        }


        return count;
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().minSwaps(grid) << endl;
}
int main(){
    test(get_matrix_int("[[1,0,0,0,0,0],[0,0,0,1,0,0],[0,0,0,0,1,0],[0,0,1,0,0,0],[0,1,0,0,0,0],[0,0,0,0,0,1]]"));
    test(get_matrix_int("[[1,0,0,0],[1,1,1,1],[1,0,0,0],[1,0,0,0]]"));
    test(get_matrix_int("[[0,0,1],[1,1,0],[1,0,0]]"));
    test(get_matrix_int("[[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]"));
    test(get_matrix_int("[[1,0,0],[1,1,0],[1,1,1]]"));
    return 0;
}