// leetcode_Q0034.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        const auto begin_it = cbegin(nums);
        const auto end_it = cend(nums);
        const auto lower_it = lower_bound(begin_it, end_it, target);
        const auto upper_it = upper_bound(begin_it, end_it, target);
        if (lower_it == end_it || *lower_it != target) { return { -1,-1 }; }
        auto l = static_cast<int>(distance(begin_it, lower_it));
        auto r = static_cast<int>(distance(begin_it, upper_it)) - 1;
        return { l,r };
    }
};


void test(vector<int>&& nums, int target) {
    const auto ret = Solution().searchRange(nums, target);
    for (auto&& val : ret) {
        cout << val << ",";
    }
    cout << endl;
}


int main()
{
    test({ 5,7,7,8,8,10 }, 8);
    test({ 5,7,7,8,8,10 }, 6);
    test({}, 0);
    test({ 1 }, 1);
}
