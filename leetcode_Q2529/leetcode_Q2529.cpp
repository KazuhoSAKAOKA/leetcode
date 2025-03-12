// leetcode_Q2529.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int maximumCount(vector<int>& nums) {
        const auto lower_it = lower_bound(cbegin(nums), cend(nums), 0);
        const auto upper_it = upper_bound(cbegin(nums), cend(nums), 0);
        const auto minuses = distance(cbegin(nums), lower_it);
        const auto pluses = upper_it == cend(nums) ? 0 : distance(upper_it, cend(nums));
        return max(minuses, pluses);
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maximumCount(nums) << endl;
}

int main()
{
    test(get_list_int("[-2,-1,-1,1,2,3]"));
    test(get_list_int("[-3,-2,-1,0,0,1,2]"));
    test(get_list_int("[5,20,66,1314]"));
    return 0;
}