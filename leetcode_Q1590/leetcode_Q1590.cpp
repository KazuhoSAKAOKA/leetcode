// leetcode_Q1590.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        vector<long long> prefix_sums(size(nums) + 1);
        for (size_t i = 0; i < size(nums); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + static_cast<long long>(nums[i]);
        }
        if (prefix_sums[size(nums)] % p == 0) {
            return 0;
        }
        for (size_t len = 1; len < size(nums); len++) {
            for (size_t i = 0; i < size(nums) - len + 1; i++) {
                if ((prefix_sums[size(nums)] - (prefix_sums[i + len] - prefix_sums[i])) % p == 0) {
                    return static_cast<int>(len);
                }
            }
        }
        return -1;
    }
};

void test(vector<int>&& nums, int p) {
    cout << Solution().minSubarray(nums, p) << endl;
}
int main()
{
    test(get_list_int("[3,1,4,2]"), 6);
    test(get_list_int("[6,3,5,2]"), 9);
    test(get_list_int("[1,2,3]"), 3);
    return 0;
}