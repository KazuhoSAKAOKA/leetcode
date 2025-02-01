// leetcode_Q1852.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> distinctNumbers(vector<int>& nums, int k) {
        const auto N = size(nums);
        vector<int> ans(N - k + 1);
        map<int, int> freqs;
        int distincts = 0;
        for (int i = 0; i < k - 1; i++) {
            if (freqs[nums[i]] == 0) {
                distincts++;
            }
            freqs[nums[i]]++;
        }

        for (int i = 0; i <= N - k; i++) {
            if (freqs[nums[i + k - 1]] == 0) {
                distincts++;
            }
            freqs[nums[i + k - 1]]++;
            ans[i] = distincts;

            freqs[nums[i]]--;
            if (freqs[nums[i]] == 0) {
                distincts--;
            }
        }
        return ans;
    }
};

void test(vector<int>&& nums, int k) {
    output(Solution().distinctNumbers(nums, k));
}


int main()
{
    test(get_list_int("[1,2,3,2,2,1,3]"), 3);
    test(get_list_int("[1,1,1,1,2,3,4]"), 4);
    return 0;
}