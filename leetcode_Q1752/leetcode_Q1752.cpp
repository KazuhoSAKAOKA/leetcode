// leetcode_Q1752.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        bool exist_seam = false;
        for (int i = 1; i < size(nums); i++) {
            if (nums[i - 1] > nums[i]) {
                if (exist_seam) {
                    return false;
                }
                exist_seam = true;
            }
        }
        if (!exist_seam) { return true; }
        return nums.back() <= nums.front();
    }
};

void test(vector<int>&& nums) {
    cout << Solution().check(nums) << endl;
}
int main()
{
    test(get_list_int("[3,4,5,1,2,3]"));
    test(get_list_int("[3,4,5,1,2,10]"));
    test(get_list_int("[3,4,5,1,2]"));
    test(get_list_int("[2,1,3,4]"));
    test(get_list_int("[1,2,3]"));
    return 0;
}