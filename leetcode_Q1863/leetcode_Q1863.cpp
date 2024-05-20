// leetcode_Q1863.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int total = 0;
        vector<int> before;
        for (int i = 0; i < nums.size(); i++) {
            vector<int> current;

            for (auto&& value : before) {
                const auto v = value ^ nums[i];
                current.emplace_back(v);
                total += v;
                current.emplace_back(value);
            }
            total += nums[i];
            current.emplace_back(nums[i]);
            before = current;
        }
        return total;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().subsetXORSum(nums) << endl;
}

int main()
{
    test(get_list_int("[1,3]"));
    test(get_list_int("[5,1,6]"));
    test(get_list_int("[3,4,5,6,7,8]"));
}