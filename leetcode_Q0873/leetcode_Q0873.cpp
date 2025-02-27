// leetcode_Q0873.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        const size_t n = size(arr);
        vector<vector<int>> dp(n, vector<int>(n));

        int max_len = 0;
        for (int i = 2; i < size(arr); i++) {
            const auto& num = arr[i];
            for (int j = i - 1; j >= 0; j--) {
                const auto remain = num - arr[j];
                const auto end_it = next(cbegin(arr), j);
                const auto it = lower_bound(cbegin(arr), end_it, remain);
                if (it != end_it && *it == remain) {
                    const auto index = distance(cbegin(arr), it);
                    const auto prev_value = dp[j][index];
                    if (prev_value == 0) {
                        dp[i][j] = 3;
                        max_len = max(max_len, 3);
                    }
                    else {
                        dp[i][j] = prev_value + 1;
                        max_len = max(max_len, dp[i][j]);
                    }
                }
            }
        }


        return max_len;
    }
};

void test(vector<int>&& arr) {
    cout << Solution().lenLongestFibSubseq(arr) << endl;
}
int main()
{
    test(get_list_int("[2392,2545,2666,5043,5090,5869,6978,7293,7795]"));
    test(get_list_int("[1,3,7,11,12,14,18]"));
    test(get_list_int("[1,2,3,4,5,6,7,8]"));
    return 0;
}