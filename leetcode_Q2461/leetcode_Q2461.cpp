// leetcode_Q2461.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long max_sum = 0;
        unordered_map<int, int> freq_map;
        long long current_sum = 0;
        for (int i = 0; i < k; i++) {
            freq_map[nums[i]]++;
            current_sum += static_cast<long long>(nums[i]);
        }

        for (int i = k; i < size(nums); i++) {
            if (size(freq_map) == k) {
                max_sum = max(max_sum, current_sum);
            }
            freq_map[nums[i]]++;
            current_sum += static_cast<long long>(nums[i]);

            freq_map[nums[i - k]]--;
            current_sum -= static_cast<long long>(nums[i - k]);
            if (freq_map[nums[i - k]] == 0) {
                freq_map.erase(nums[i - k]);
            }
        }
        if (size(freq_map) == k) {
            max_sum = max(max_sum, current_sum);
        }
        return max_sum;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maximumSubarraySum(nums, k) << endl;
}

int main()
{
    test(get_list_int("[1,1,1,7,8,9]"), 3);
    test(get_list_int("[1,5,4,2,9,9,9]"), 3);
    test(get_list_int("[4,4,4]"), 3);
    return 0;
}