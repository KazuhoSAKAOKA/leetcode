// leetcode_Q2191.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        unordered_map<int, int> mapped_values;
        auto convert = [&](int value)->int {
            if (value == 0) {
                return mapping[0];
            }
            int ret = 0;
            int current = value;
            int multiple = 1;
            while (current > 0) {
                const auto digit = current % 10;
                ret += mapping[digit] * multiple;
                current /= 10;
                multiple *= 10;
            }
            return ret;
            };
        for (int i = 0; i < nums.size(); i++) {
            mapped_values[nums[i]] = convert(nums[i]);
        }

        sort(begin(nums), end(nums), [&](const auto& a, const auto& b) {
            return mapped_values[a] < mapped_values[b];
            });
        return nums;
    }
};

void test(vector<int>&& mapping, vector<int>&& nums) {
    const auto ans = Solution().sortJumbled(mapping, nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(get_list_int("[9,8,7,6,5,4,3,2,1,0]"), get_list_int("[0,1,2,3,4,5,6,7,8,9]"));
    test(get_list_int("[8,9,4,0,2,1,3,5,7,6]"), get_list_int("[991,338,38]"));
    test(get_list_int("[0,1,2,3,4,5,6,7,8,9]"), get_list_int("[789,456,123]"));
    return 0;
}