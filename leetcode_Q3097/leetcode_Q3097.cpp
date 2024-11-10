// leetcode_Q3097.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int get_add_num(vector<int>& bit_freqs, int num) {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            const auto bit = (1 << i);
            if ((num & bit) != 0) {
                bit_freqs[i]++;
            }
            if (bit_freqs[i] > 0) {
                ret |= bit;
            }
        }
        return ret;
    }
    static bool check(const vector<int>& bit_freqs, int num, int k) {
        int val = 0;
        for (int i = 0; i < 32; i++) {
            const auto bit = (1 << i);
            if ((num & bit) != 0 && bit_freqs[i] == 1) {
            }
            else {
                if (bit_freqs[i] > 0) {
                    val |= bit;
                }

            }
        }
        return val >= k;
    }
    static int get_remove_num(vector<int>& bit_freqs, int num) {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            const auto bit = (1 << i);
            if ((num & bit) != 0) {
                bit_freqs[i]--;
            }
            if (bit_freqs[i] > 0) {
                ret |= bit;
            }
        }
        return ret;
    }


    int minimumSubarrayLength(vector<int>& nums, int k) {
        vector<int> bit_freqs(32);
        int min_length = INT_MAX;

        int current_or = 0;

        size_t l = 0;
        for (size_t r = 0; r < size(nums); r++) {
            current_or = get_add_num(bit_freqs, nums[r]);

            while (l < r && check(bit_freqs, nums[l], k)) {
                current_or = get_remove_num(bit_freqs, nums[l]);
                l++;
            }
            if (current_or >= k) {
                min_length = min(min_length, static_cast<int>(r - l + 1));
            }
        }
        if (min_length == INT_MAX) { return -1; }
        return min_length;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().minimumSubarrayLength(nums, k) << endl;
}
int main()
{
    test(get_list_int("[1,2,32,21]"), 55);
    test(get_list_int("[1,2,3]"), 2);
    test(get_list_int("[2,1,8]"), 10);
    test(get_list_int("[1,2]"), 0);
    return 0;
}