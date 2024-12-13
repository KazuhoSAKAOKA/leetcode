// leetcode_Q2593.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    long long findScore(vector<int>& nums) {
        vector<size_t> indexes(size(nums));
        for (size_t i = 0; i < size(nums); i++) { indexes[i] = i; }
        stable_sort(begin(indexes), end(indexes), [&](auto a, auto b) { return nums[a] < nums[b]; });

        vector<bool> used(size(nums));
        long long score = 0;
        for (auto&& index : indexes) {
            if (!used[index]) {
                score += nums[index];
                used[index] = true;
                if (index > 0) {
                    used[index - 1] = true;
                }
                if (index < size(nums) - 1) {
                    used[index + 1] = true;
                }
            }
        }
        return score;
    }
};

using namespace std;

void test(vector<int>&& nums) {
    cout << Solution().findScore(nums) << endl;
}
int main()
{
    test(get_list_int("[2,1,3,4,5,2]"));
    test(get_list_int("[2,3,5,1,3,2]"));
    return 0;
}