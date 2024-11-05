// leetcode_Q1671.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        const size_t N = size(nums);

        vector<int> dpleft2right(N);
        map<int, int> index_mapl;
        index_mapl[nums[0]] = 0;
        for (int index = 1; index < N; index++) {

            int min_skips = index;
            for (auto&& [num, ind] : index_mapl) {
                if (num >= nums[index]) { break; }
                min_skips = min(min_skips, dpleft2right[ind] + (index - ind - 1));
            }
            dpleft2right[index] = min_skips;
            index_mapl[nums[index]] = index;
        }

        vector<int> dpright2left(N);
        map<int, int> index_mapr;
        index_mapr[nums[N - 1]] = N - 1;
        for (int index = N - 2; index >= 0; index--) {
            int min_skips = N - index - 1;
            for (auto&& [num, ind] : index_mapr) {
                if (num >= nums[index]) { break; }
                min_skips = min(min_skips, dpright2left[ind] + (ind - index - 1));
            }
            dpright2left[index] = min_skips;
            index_mapr[nums[index]] = index;
        }

        int total_min_skips = INT_MAX;
        for (int i = 1; i < N - 1; i++) {
            const auto left_size = i;
            const auto right_size = static_cast<int>(N) - 1 - i;
            const auto left_valid_size = left_size - dpleft2right[i];
            const auto right_valid_size = right_size - dpright2left[i];
            const auto current_size = min(left_valid_size, right_valid_size);
            if(current_size > 0){
                total_min_skips = min(total_min_skips, static_cast<int>(N) - (current_size * 2 + 1));
            }
        }
        return total_min_skips;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minimumMountainRemovals(nums) << endl;
}


int main()
{
    test(get_list_int("[4,3,2,1,1,2,3,1]"));
    test(get_list_int("[100,92,89,77,74,66,64,66,64]"));

    test(get_list_int("[1,3,1]"));
    test(get_list_int("[2,1,1,5,6,2,3,1]"));
    return 0;
}