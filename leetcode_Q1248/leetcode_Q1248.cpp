// leetcode_Q1248.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int tle(const vector<int>& nums, int k) {
        vector<int> prefix_sums(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i] % 2;
        }

        int total = 0;
        for (int i = 0; i < prefix_sums.size(); i++) {
            for (int j = i + 1; j < prefix_sums.size(); j++) {
                if (prefix_sums[j] - prefix_sums[i] == k) {
                    total++;
                }
            }
        }
        return total;
    }


    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> freq_map;
        freq_map[0] = 1;
        int total = 0;
        int current = 0;
        for (int i = 0; i < nums.size(); i++) {
            current += nums[i] % 2;
            if (current >= k) {
                total += freq_map[current - k];
            }
            freq_map[current]++;
        }
        return total;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().numberOfSubarrays(nums, k) << endl;
}


int main()
{
    test(get_list_int("[1,1,2,1,1]"), 3);
    test(get_list_int("[2,4,6]"), 1);
    test(get_list_int("[2,2,2,1,2,2,1,2,2,2]"), 2);
    test(get_list_int("[2,1,2,2,1,2,2,1,2]"), 2);
}