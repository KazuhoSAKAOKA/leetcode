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
    long long mostPoints(vector<vector<int>>& questions) {
        const auto n = size(questions);
        vector<long long> dp(n + 1);
        for (int i = 0; i < n; i++) {
            const auto& question = questions[i];
            const auto point = question.front();
            const auto brain_power = question.back();
            dp[i + 1] = max(dp[i + 1], dp[i]);
            dp[i] += static_cast<long long>(point);
            const auto index = min(static_cast<int>(n), i + brain_power + 1);
            dp[index] = max(dp[index], dp[i]);
        }
        return dp.back();
    }
};

void test(vector<vector<int>>&& questions) {
    cout << Solution().mostPoints(questions) << endl;
}
int main() {
    test(get_matrix_int("[[12,46],[78,19],[63,15],[79,62],[13,10]]"));
    test(get_matrix_int("[[1,1],[2,2],[3,3],[4,4],[5,5]]"));
    test(get_matrix_int("[[3,2],[4,3],[4,4],[2,5]]"));
    return 0;
}