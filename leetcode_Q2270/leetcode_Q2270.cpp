// leetcode_Q2270.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        const auto total = accumulate(cbegin(nums), cend(nums), 0LL, [](long long a, int b) { return a + static_cast<long long>(b); });
        int count = 0;
        long long cur_total = 0;
        for (int i = 0; i < size(nums) - 1; i++) {
            cur_total += static_cast<long long>(nums[i]);
            const long long remain = total - cur_total;
            if (cur_total >= remain) {
                count++;
            }
        }
        return count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().waysToSplitArray(nums) << endl;
}
int main()
{
    test(get_list_int("[10,4,-8,7]"));
    test(get_list_int("[2,3,1,0]"));
    return 0;
}
