// leetcode_Q2419.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        const auto max_value = *max_element(cbegin(nums), cend(nums));
        int max_len = 0;
        int current_len = 0;
        for (int i = 0; i < size(nums); i++) {
            if (max_value == nums[i]) {
                current_len++;
                max_len = max(max_len, current_len);
            }
            else {
                current_len = 0;
            }
        }
        return max_len;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().longestSubarray(nums) << endl;
}
int main()
{

    test(get_list_int("[1,2,3,3,2,2]"));
    test(get_list_int("[1,2,3,4]"));
    return 0;
}