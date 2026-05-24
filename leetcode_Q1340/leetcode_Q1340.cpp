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

    static int dfs(const vector<int>& arr, int d, int index, vector<int>& memo) {
        if (memo[index] != 0) {
            return memo[index];
        }
        int cur_visit = 1;
        const int n = size(arr);
        for (int i = index - 1; i >= max(0, index - d); i--) {
            if (arr[i] >= arr[index]) { break; }
            cur_visit = max(cur_visit, dfs(arr, d, i, memo) + 1);
        }
        for (int i = index + 1; i <= min(n-1, index + d); i++) {
            if (arr[i] >= arr[index]) { break; }
            cur_visit = max(cur_visit, dfs(arr, d, i, memo) + 1);
        }
        memo[index] = cur_visit;
        return cur_visit;
    }

    int maxJumps(vector<int>& arr, int d) {
        const auto n = size(arr);
        vector<int> memo(n);
        int max_visit = 0;
        for (int i = 0; i < n; i++) {
            max_visit = max(max_visit, dfs(arr, d, i, memo));
        }
        return max_visit;
    }
};

static void test(vector<int>&& arr, int d) {
    cout << Solution().maxJumps(arr, d) << endl;
}
int main() {
    test(get_list_int("[6,4,14,6,8,13,9,7,10,6,12]"), 2);
    test(get_list_int("[3,3,3,3,3]"), 3);
    test(get_list_int("[7,6,5,4,3,2,1]"), 1);
    return 0;
}