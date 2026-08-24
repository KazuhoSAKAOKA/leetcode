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


    int stoneGameVIII(vector<int>& stones) {
        const long long n = size(stones);
        vector<long long> dp(n + 1);
        for (size_t i = 0; i < n; i++) { dp[i + 1] = dp[i] + stones[i]; }
        long long ans = dp[n];
        for (long long i = n - 1; i > 1; i--) {
            ans = max(ans, dp[i] - ans);
        }
        return static_cast<int>(ans);
    }
};

static void test(vector<int>&& stones) {
    cout << Solution().stoneGameVIII(stones) << endl;
}
int main() {
    test(get_list_int("[-1,2,-3,4,-5]"));
    test(get_list_int("[7,-6,5,10,5,-2,-6]"));
    test(get_list_int("[-10,-12]"));
    return 0;
}
