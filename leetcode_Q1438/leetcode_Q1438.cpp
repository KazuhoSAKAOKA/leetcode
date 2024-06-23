// leetcode_Q1438.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {

        map<int, int> freq_map;
        int l = 0;
        int r = 0;
        int longest = 0;
        for (; r < nums.size(); r++) {
            freq_map[nums[r]]++;
            int current_min = cbegin(freq_map)->first;
            int current_max = crbegin(freq_map)->first;
            int current_diff = current_max - current_min;
            while (limit < current_diff && l < r) {
                freq_map[nums[l]]--;
                if (freq_map[nums[l]] == 0) {
                    freq_map.erase(nums[l]);
                }
                current_min = cbegin(freq_map)->first;
                current_max = crbegin(freq_map)->first;
                current_diff = current_max - current_min;
                l++;
            }
            longest = max(longest, r - l + 1);
        }
        return longest;
    }
};

void test(vector<int>&& nums, int limit) {
    cout << Solution().longestSubarray(nums, limit) << endl;
}

int main()
{
    test(get_list_int("[8,2,4,7]"), 4);
    test(get_list_int("[10,1,2,4,7,2]"), 5);
    test(get_list_int("[4,2,2,2,4,4,2,2]"), 0);
}