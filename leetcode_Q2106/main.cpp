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

    static inline int get_len(int l, int r, int center, const vector<vector<int>>& fruits) {
        const auto leftpos = fruits[l][0];
        const auto rightpos = fruits[r][0];
        const auto near = min(center - leftpos, rightpos - center);
        const auto far = max(center - leftpos, rightpos - center);
        return near * 2 + far;
    }

    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        const auto n = size(fruits);
        const auto lower_limit = startPos - k;
        const auto upper_limit = startPos + k;
        int r = 0;
        while (r < n && fruits[r][0] < lower_limit) {
            r++;
        }
        int current_fruits = 0;
        int l = r;
        while (r < n && fruits[r][0] <= startPos) {
            current_fruits += fruits[r][1];
            r++;
        }
        int max_fruits = current_fruits;
        while (r < n && fruits[r][0] <= upper_limit) {
            current_fruits += fruits[r][1];

            while (l < r && k < get_len(l, r, startPos, fruits)) {
                current_fruits -= fruits[l][1];
                l++;
            }

            max_fruits = max(max_fruits, current_fruits);
            r++;
        }

        return max_fruits;
    }
};

static void test(vector<vector<int>>&& fruits, int startPos, int k) {
    cout << Solution().maxTotalFruits(fruits, startPos, k) << endl;
}
int main() {
    test(get_matrix_int("[[2,8],[6,3],[8,6]]"), 5, 4);
    test(get_matrix_int("[[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]]"), 5, 4);
    test(get_matrix_int("[[0,3],[6,4],[8,5]]"), 3, 2);
    return 0;
}