// leetcode_Q2161.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> ans(size(nums));
        int index = 0;
        for (auto&& num : nums) {
            if (num < pivot) {
                ans[index++] = num;
            }
        }
        for (auto&& num : nums) {
            if (num == pivot) {
                ans[index++] = num;
            }
        }
        for (auto&& num : nums) {
            if (num > pivot) {
                ans[index++] = num;
            }
        }
        return ans;
    }
};

void test(vector<int>&& nums, int pivot) {
    output(Solution().pivotArray(nums, pivot));
}
int main(){
    test(get_list_int("[9,12,5,10,14,3,10]"), 10);
    test(get_list_int("[-3,4,3,2]"), 2);
    return 0;
}