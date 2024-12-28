// leetcode_Q0689.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"


using namespace std;


class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const auto N = size(nums);
        vector<long long> sums(N - k + 1);
        long long cur_sum = 0;
        for (int i = 0; i < k; i++) {
            cur_sum += nums[i];
        }
        sums[0] = cur_sum;
        for (int i = 1; i <= N - k; i++) {
            cur_sum += nums[i + k - 1];
            cur_sum -= nums[i - 1];
            sums[i] = cur_sum;
        }

        long long max_sum = 0;
        int left_part_index = -1;
        int middle_part_index = -1;
        int right_part_index = -1;

        long long right_part_max = 0;
        int right_part_max_index = -1;

        long long middle_to_right_part_max = 0;
        int middle_part_pair_right_index = -1;
        int middle_part_max_index = -1;

        for (int i = N - (3 * k); i >=0 ; i--) {
            if (right_part_max <= sums[i + 2 * k]) {
                right_part_max = sums[i + 2 * k];
                right_part_max_index = i + 2 * k;
            }
            const auto current_mid = sums[i + k] + right_part_max;
            if (middle_to_right_part_max <= current_mid) {
                middle_to_right_part_max = current_mid;
                middle_part_pair_right_index = right_part_max_index;
                middle_part_max_index = i + k;
            }

            const auto current_sum = sums[i] + middle_to_right_part_max;
            if (max_sum <= current_sum) {
                max_sum = current_sum;
                left_part_index = i;
                right_part_index = middle_part_pair_right_index;
                middle_part_index = middle_part_max_index;
            }
        }
        return vector<int>{left_part_index, middle_part_index, right_part_index};
    }
};

void test(vector<int>&& nums, int k) {
    output(Solution().maxSumOfThreeSubarrays(nums, k));
}
int main()
{
    test(get_list_int("[1,2,1,2,6,7,5,1]"), 2);
    test(get_list_int("[1,2,1,2,1,2,1,2,1]"), 2);
    test(get_list_int("[1,2,3]"), 1);
    return 0;
}