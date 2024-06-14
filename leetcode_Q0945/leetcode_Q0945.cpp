// leetcode_Q0945.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        const auto it_max = max_element(cbegin(nums), cend(nums));
        const int max_value = *it_max;
        vector<int> counts(max_value + 1, 0);
        for (auto&& num : nums) {
            counts[num]++;
        }
        int total_moves = 0;
        int current_value = 0;
        for (auto&& value : counts) {
            const auto diff = value - 1;
            current_value += diff;
            current_value = max(0, current_value);
            total_moves += current_value;
        }
        while (current_value > 1) {
            current_value--;
            total_moves += current_value;
        }
        return total_moves;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minIncrementForUnique(nums) << endl;
}

int main()
{
    test(get_list_int("[2,2,2,2,0]"));
    test(get_list_int("[2,2,2,1]"));
    test(get_list_int("[1,2,2]"));
    test(get_list_int("[3,2,1,2,1,7]"));
}