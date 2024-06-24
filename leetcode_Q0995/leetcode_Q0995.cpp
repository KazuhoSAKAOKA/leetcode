// leetcode_Q0995.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int count = 0;
        vector<bool> end_flip(nums.size(), false);

        bool fliped = false;
        for (int i = 0; i < nums.size() - k + 1; i++) {
            if ((nums[i] == 0 && !fliped) || (nums[i] != 0 && fliped)) {
                count++;
                fliped = !fliped;
                end_flip[i + k - 1] = true;
            }
            if (end_flip[i]) {
                fliped = !fliped;
            }
        }

        for (int i = nums.size() - k + 1; i < nums.size(); i++) {
            if ((nums[i] == 0 && !fliped) || (nums[i] != 0 && fliped)) {
                return -1;
            }
            if (end_flip[i]) {
                fliped = !fliped;
            }
        }
        return count;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().minKBitFlips(nums, k) << endl;
}

int main()
{
    test(get_list_int("[0,1,0]"), 1);
    test(get_list_int("[1,1,0]"), 2);
    test(get_list_int("[0,0,0,1,0,1,1,0]"), 3);
}