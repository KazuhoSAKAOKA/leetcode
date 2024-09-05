// leetcode_Q2028.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        const auto sums = accumulate(cbegin(rolls), cend(rolls), 0);
        auto diffsum = abs(mean * static_cast<int>(size(rolls)) - sums);
        vector<int> ans(n, mean);
        if (diffsum == 0) {
            return ans;
        }
        const auto multiples = sums > mean * static_cast<int>(size(rolls)) ? -1 : 1;
        const auto val = multiples > 0 ? 6 - mean : mean - 1;

        for (int i = 0; i < n; i++) {
            const auto diff = min(diffsum, val);
            ans[i] = mean + multiples * diff;
            diffsum -= diff;
        }
        if (diffsum != 0) {
            return vector<int>();
        }
        return ans;
    }
};

void test(vector<int>&& rolls, int mean, int n) {
    output( Solution().missingRolls(rolls, mean, n));
}

int main()
{
    test(get_list_int("[3,2,4,3]"), 4, 2);
    test(get_list_int("[1,5,6]"), 3, 4);
    test(get_list_int("[1,2,3,4]"), 6, 4);
    return 0;
}