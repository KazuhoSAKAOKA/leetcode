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
    int minMoves(vector<int>& nums, int limit) {
        const auto n = size(nums);
        vector<int> diffs(limit * 2 + 2);

        for (size_t i = 0; i < n / 2; i++) {
            const auto sum = nums[i] + nums[n - i - 1];
            diffs[2] += 2;
            diffs[min(nums[i], nums[n - i - 1]) + 1] -= 1;
            diffs[sum] -= 1;
            diffs[sum + 1] += 1;
            diffs[min(limit * 2 + 1, max(nums[i], nums[n - i - 1]) + limit + 1)] += 1;
        }

        int min_moves = INT_MAX;
        int cur_moves = 0;

        for (int i = 2; i <= limit * 2; i++) {
            cur_moves += diffs[i];
            min_moves = min(min_moves, cur_moves);
        }

        return min_moves;
    }
};

static void test(vector<int>&& nums, int limit) {
    cout << Solution().minMoves(nums, limit) << endl;
}

int main() {
    test(get_list_int("[1,3,1,1,1,2,3,2,3,1,3,2,1,3]"), 5);

    test(get_list_int("[1,2,4,3]"), 4);
    test(get_list_int("[1,2,2,1]"), 2);
    test(get_list_int("[1,2,1,2]"), 2);
    return 0;
}
