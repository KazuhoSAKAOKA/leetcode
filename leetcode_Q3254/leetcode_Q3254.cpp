// leetcode_Q3254.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        vector<int> streaks(size(nums));
        streaks.back() = 1;
        for (int i = size(nums) - 2; i >= 0; i--) {
            if (nums[i] + 1 == nums[i + 1]) {
                streaks[i] = streaks[i + 1] + 1;
            }
            else {
                streaks[i] = 1;
            }
        }
        vector<int> ans;
        ans.reserve(size(nums) - k);
        for (int i = 0; i <= size(nums) - k; i++) {
            if (streaks[i] >= k) {
                ans.emplace_back(nums[i + k - 1]);
            }
            else {
                ans.emplace_back(-1);
            }
        }
        return ans;
    }
};

void test(vector<int>&& nums, int k) {
    output(Solution().resultsArray(nums, k));
}
int main()
{
    test(get_list_int("[1,2,3,4,3,2,5]"), 3);
    test(get_list_int("[2,2,2,2,2]"), 4);
    test(get_list_int("[3,2,3,2,3,2]"), 2);
    return 0;
}