// leetcode_Q1605.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        vector<vector<long long>> ans(rowSum.size(), vector<long long>(colSum.size(), 0));

        for (int j = 0; j < colSum.size(); j++) {
            ans[0][j] = colSum[j];
        }

        for (int i = 0; i < rowSum.size() - 1; i++) {
            auto sum = accumulate(cbegin(ans[i]), cend(ans[i]), 0LL);
            int j = 0;
            while (sum > rowSum[i] && j < colSum.size()) {
                const auto shift = min(sum - static_cast<long long>(rowSum[i]), ans[i][j]);
                sum -= shift;
                ans[i][j] -= shift;
                ans[i + 1][j] += shift;
                j++;
            }
            assert(sum == rowSum[i]);
        }
        const auto last_sum = accumulate(cbegin(ans[rowSum.size() - 1]), cend(ans[rowSum.size() - 1]), 0);
        assert(last_sum == rowSum[rowSum.size() - 1]);

        vector<vector<int>> ans1(rowSum.size(), vector<int>(colSum.size(), 0));
        for (int i = 0; i < rowSum.size(); i++) {
            for (int j = 0; j < colSum.size(); j++) {
                ans1[i][j] = static_cast<int>(ans[i][j]);
            }
        } 

        return ans1;
    }
};

void test(vector<int>&& rowSum, vector<int>&& colSum) {
    const auto ans = Solution().restoreMatrix(rowSum, colSum);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    test(get_list_int("[3,8]"), get_list_int("[4,7]"));
    test(get_list_int("[5,7,10]"), get_list_int("[8,6,8]"));
    return 0;
}