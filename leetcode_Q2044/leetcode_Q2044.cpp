// leetcode_Q2044.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int rec(const vector<int>& nums, size_t index, int current, int max_or) {
        if (size(nums) == index) {
            if (current == max_or) {
                return 1;
            }
            return 0;
        }

        int total = 0;
        total = rec(nums, index + 1, current, max_or);
        total += rec(nums, index + 1, current | nums[index], max_or);
        return total;
    }


    int countMaxOrSubsets(vector<int>& nums) {
        int max_or = 0;
        for (auto&& num : nums) {
            max_or |= num;
        }

        return rec(nums, 0, 0, max_or);
    }
};

void test(vector<int>&& nums) {
    cout << Solution().countMaxOrSubsets(nums) << endl;
}

int main()
{
    test(get_list_int("[3,1]"));
    test(get_list_int("[2,2,2]"));
    test(get_list_int("[3,2,1,5]"));
    return 0;
}