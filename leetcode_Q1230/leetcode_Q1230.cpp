
#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        if (prob.size() < target) { return 0.0; }
        vector<vector<double>> dp(prob.size() + 1, vector<double>(target + 1, 0.0));
        dp[0][0] = 1.0;

        for (int i = 1; i <= prob.size(); i++) {
            dp[i][0] = dp[i - 1][0] * (1.0 - prob[i - 1]);
            for (int j = 1; j <= target; j++) {
                dp[i][j] = dp[i - 1][j] * (1.0 - prob[i - 1]) + dp[i - 1][j - 1] * prob[i - 1];
            }
        }

        return dp[prob.size()][target];
    }
};

void test(vector<double>&& prob, int target) {
    cout << Solution().probabilityOfHeads(prob, target) << endl;
}

int main()
{
    test(get_list_double("[0.4]"), 1);
    test(get_list_double("[0.5,0.5,0.5,0.5,0.5]"), 0);
    return 0;
}