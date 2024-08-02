// leetcode_Q2134.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        const int N = size(nums);
        vector<int> prefix_sums(N + 1);
        for (int i = 0; i < N; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }
        const int ones_count = prefix_sums[N];
        if (ones_count == N) {
            return 0;
        }
        auto get_ones_count = [&](int l, int r) {
            return prefix_sums[r] - prefix_sums[l];
            };
        int max_ones_count = 0;
        for (int l = 0; l <= N - ones_count; l++) {
            const int count = get_ones_count(l, l + ones_count);
            if (max_ones_count < count) {
                max_ones_count = count;
            }
        }

        //circular
        for (int left_len = 1; left_len < ones_count; left_len++) {
            const int left_count = get_ones_count(0, left_len);
            const int right_count = get_ones_count(N - ones_count + left_len, N);
            if (max_ones_count < left_count + right_count) {
                max_ones_count = left_count + right_count;
            }
        }
        return ones_count - max_ones_count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minSwaps(nums) << endl;
}

int main()
{
    test(get_list_int("[0,0,1,1]"));
    test(get_list_int("[0,1,0,1,1,0,0]"));
    test(get_list_int("[0,1,1,1,0,0,1,1,0]"));
    test(get_list_int("[1,1,0,0,1]"));
    return 0;
}