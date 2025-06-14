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
    enum class result {
        get_value,
        failure,
        empty,
    };
    static pair<pair<int, int>, result> dfs(const vector<int>& preorder, int current, int end_limit) {
        if (end_limit <= current) {
            return { {0,0}, result::empty };
        }

        const auto current_value = preorder[current];
        int right_start = end_limit;
        for (int i = current + 1; i < end_limit; i++) {
            if (current_value <= preorder[i]) {
                right_start = i;
                break;
            }
        }

        int min_value = current_value;
        int max_value = current_value;
        const auto [left_values, left_result] = dfs(preorder, current + 1, right_start);
        const auto [right_values, right_result] = dfs(preorder, right_start, end_limit);
        if (left_result == result::failure || right_result == result::failure) {
            return { {0,0}, result::failure };
        }
        if (left_result == result::get_value) {
            if (left_values.second >= current_value) {
                return  { {0,0}, result::failure };
            }
            min_value = min(min_value, left_values.first);
        }
        if (right_result == result::get_value) {
            if (right_values.first < current_value) {
                return  { {0,0}, result::failure };
            }
            max_value = max(max_value, right_values.second);
        }
        return {  { min_value, max_value  }, result::get_value };
    }

    bool verifyPreorder(vector<int>& preorder) {
        const auto [_, ret] = dfs(preorder, 0, size(preorder));
        return ret == result::get_value;
    }
};

void test(vector<int>&& preorder) {
    cout << Solution().verifyPreorder(preorder) << endl;
}
int main() {
    test(get_list_int("[5,2,1,3,6]"));
    test(get_list_int("[5,2,6,1,3]"));
    return 0;
}