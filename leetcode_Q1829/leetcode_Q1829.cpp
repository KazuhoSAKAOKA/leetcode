// leetcode_Q1829.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        vector<int> ans(size(nums));

        const int mask = (1 << maximumBit) - 1;
        int current_xor = 0;
        for (int i = 0; i < size(nums); i++) {
            current_xor ^= nums[i];
            const auto masked = mask & current_xor;
            ans[size(nums) - 1 - i] = (mask & ~masked);
        }
        return ans;
    }
};

void test(vector<int>&& nums, int maximumBit) {
    output(Solution().getMaximumXor(nums, maximumBit));
}

int main()
{
    test(get_list_int("[0,1,1,3]"), 2);
    test(get_list_int("[2,3,4,7]"), 3);
    test(get_list_int("[0,1,2,2,5,7]"), 3);
    return 0;
}