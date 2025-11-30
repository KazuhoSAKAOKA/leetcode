// leetcode_Q1590.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <fstream>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        const long long total = accumulate(cbegin(nums), cend(nums), 0LL, [](long long t, int v)->long long {  return t + v; });
        if (total < p) {
            return -1;
        }
        const long long total_mod = total % p;
        if (total_mod == 0) {
            return 0;
        }
        long long prefix_sum = 0LL;
        map<int, int> mp{ { 0,0 } };
        int min_len = static_cast<int>(size(nums));
        for (int i = 0; i < size(nums); i++) {
            if (nums[i] == total_mod) {
                min_len = 1;
                break;
            }
            prefix_sum += nums[i];
            const auto r = prefix_sum % p;
            const auto target = (r - total_mod + p) % p;
            const auto it = mp.find(target);
            if (it != cend(mp)) {
                min_len = min(min_len, i + 1 - it->second);
            }
            mp[r] = i + 1;
        }

        if (min_len == static_cast<int>(size(nums))) {
            return -1;
        }
        return min_len;
    }
};

void test(vector<int>&& nums, int p) {
    cout << Solution().minSubarray(nums, p) << endl;
}
int main()
{
    test(get_list_int("[3,6,8,1]"), 8);
    test(get_list_int("[4,4,2]"), 7);
    test(get_list_int("[6,3,5,2]"), 9);
    test(get_list_int("[3,1,4,2]"), 6);
    test(get_list_int("[1,2,3]"), 3);
    return 0;
}