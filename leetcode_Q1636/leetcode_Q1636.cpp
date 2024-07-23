// leetcode_Q1636.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int, size_t> freq_map;
        for (auto&& value : nums) {
            freq_map[value]++;
        }

        sort(begin(nums), end(nums), [&](const auto& a, const auto& b) {
            if (a == b) { return false; }
            const auto a_freq = freq_map[a];
            const auto b_freq = freq_map[b];
            if (a_freq != b_freq) {
                return a_freq < b_freq;
            }
            return a > b;
            });

        return nums;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().frequencySort(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
int main()
{
    test(get_list_int("[1,1,2,2,2,3]"));
    test(get_list_int("[2,3,1,3,2]"));
    test(get_list_int("[-1,1,-6,4,5,-6,1,4,1]"));
    return 0;
}