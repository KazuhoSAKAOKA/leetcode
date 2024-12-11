// leetcode_Q2779.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));

        int l = 0;
        int max_len = 0;
        for (int r = 0; r < size(nums); r++) {
            while (l < r && nums[r] - nums[l] > 2 * k) {
                l++;
            }
            max_len = max(max_len, r - l + 1);
        }
        return max_len;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maximumBeauty(nums, k) << endl;
}
int main()
{
    test(get_list_int("[4,6,1,2]"), 2);
    test(get_list_int("[1,1,1,1]"), 2);
    return 0;
}