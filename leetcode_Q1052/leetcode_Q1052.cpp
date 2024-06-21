// leetcode_Q1052.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    static  int mle(vector<int>& customers, vector<int>& grumpy, int minutes) {
        vector<vector<int>> dp(minutes, vector<int>(minutes, 0));
        int not_use_technique = grumpy[0] == 0 ? customers[0] : 0;
        int used_technique = 0;
        dp[0][0] = customers[0];

        for (int i = 1; i < customers.size(); i++) {
            const int dp_index = i % minutes;
            const int dp_before_index = (i - 1) % minutes;

            dp[dp_index][0] = not_use_technique + customers[i];
            for (int j = 1; j < minutes; j++) {
                dp[dp_index][j] = dp[dp_before_index][j - 1] + customers[i];
            }
            not_use_technique = not_use_technique + (grumpy[i] == 0 ? customers[i] : 0);
            used_technique = max(used_technique, dp[dp_before_index][minutes - 1]) + (grumpy[i] == 0 ? customers[i] : 0);
        }
        int max_value = max(not_use_technique, used_technique);
        const int index = (customers.size() - 1) % minutes;
        for (int i = 0; i < dp.back().size(); i++) {
            max_value = max(max_value, dp[index][i]);
        }
        return max_value;
    }

    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int max_value = 0;
        for (int i = 0; i < customers.size(); i++) {
            if (i < minutes) {
                max_value = max_value + customers[i];
            }
            else {
                if (grumpy[i] == 0) {
                    max_value += customers[i];
                }
            }
        }
        int current_value = max_value;
        if (minutes < customers.size()) {
            for (int x = 1; x <= customers.size() - minutes; x++) {
                if (grumpy[x - 1] == 1) {
                    current_value -= customers[x - 1];
                }
                if (grumpy[x + minutes - 1] == 1) {
                    current_value += customers[x + minutes - 1];
                }
                max_value = max(max_value, current_value);
            }
        }

        return max_value;
    }
};

void test(vector<int>&& customers, vector<int>&& grumpy, int minutes) {
    cout << Solution().maxSatisfied(customers, grumpy, minutes) << endl;
}

int main()
{
    test(get_list_int("[4,10,10]"), get_list_int("[1,1,0]"), 2);
    test(get_list_int("[1,0,1,2,1,1,7,5]"), get_list_int("[0,1,0,1,0,1,0,1]"), 3);
    test(get_list_int("[1]"), get_list_int("[0]"), 3);
}