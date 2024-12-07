// leetcode_Q1760.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

template <typename T = long long>
T bs(T ok, T ng, std::function<bool(T)> check) {
    while (abs(ng - ok) > 1) {
        const auto mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        }
        else {
            ng = mid;
        }
    }
    return ok;
}
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        sort(begin(nums), end(nums), std::greater<>());

        const auto ok = bs<int>(nums[0], 0, [&](auto v) {
            int op_count = 0;
            int index = 0;
            while (index< size(nums) && nums[index] > v && op_count <= maxOperations) {
                op_count += nums[index] / v - 1 + (nums[index] % v != 0 ? 1 : 0);
                index++;
            }
            return op_count <= maxOperations;
            });

        return ok;
    }
};

void test(vector<int>&& nums, int maxOperations) {
    cout << Solution().minimumSize(nums, maxOperations) << endl;
}
int main()
{
    test(get_list_int("[9]"), 2);
    test(get_list_int("[2,4,8,2]"), 4);
    return 0;
}