// leetcode_Q2501.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        sort(begin(nums), end(nums));
        unordered_map <long long, int> prev_map;
        int max_streak = -1;
        for(auto&& num : nums){
            const long long n2 = static_cast<long long>(num) * static_cast<long long>(num);
            auto it = prev_map.find(num);
            if (it != end(prev_map)) {
                const auto streak = it->second + 1;
                max_streak = max(max_streak, streak);
                prev_map[n2] = max(prev_map[n2], streak);
            }
            else {
                prev_map[n2] = 1;
            }
        }
        return max_streak;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().longestSquareStreak(nums) << endl;
}

int main()
{
    test(get_list_int("[4,3,6,16,8,2]"));
    test(get_list_int("[2,3,5,6,7]"));
    return 0;
}