// leetcode_Q2460.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        vector<int> ans(size(nums));

        int index = 0;
        int index_num = 0;
        while (index_num < size(nums) - 1) {
            if (nums[index_num] == 0) {
                index_num++;
            }
            else if (nums[index_num] == nums[index_num + 1]) {
                ans[index] = nums[index_num] * 2;
                index++;
                index_num += 2;
            }
            else {
                ans[index] = nums[index_num];
                index++;
                index_num++;
            }
        }
        if (index_num < size(nums)) {
            ans[index] = nums.back();
        }
        return ans;
    }
};

void test(vector<int>&& nums) {
    output(Solution().applyOperations(nums));
}

int main()
{
    test(get_list_int("[1,2,2,1,1,0]"));
    test(get_list_int("[0,1]"));
    return 0;
}