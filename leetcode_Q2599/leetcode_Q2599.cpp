// leetcode_Q2599.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int tle(const vector<int>& nums) {
        map<int, long long> before;
        if (nums[0] < 0) {
            before.insert({ 1, 0 });
        }
        else {
            before.insert({ 0, nums[0] });
        }

        for (int i = 1; i < size(nums); i++) {
            if (nums[i] < 0) {
                map<int, long long> current;
                auto it = cbegin(before);
                const auto min_op = it->first;
                const auto no_op_value = it->second + nums[i];
                if (no_op_value >= 0) {
                    current.insert({ min_op, no_op_value });
                }
                current.insert({ min_op + 1, it->second });
                ++it;
                while (it != cend(before)) {
                    current[it->first] = max(current[it->first], it->second + nums[i]);
                    const auto no_op_value_i = it->second + nums[i];
                    current.insert({ it->first + 1, it->second });
                    ++it;
                }
                swap(before, current);
            }
            else {
                for (auto&& [_, v] : before) {
                    v += nums[i];
                }
            }
        }
        return cbegin(before)->first;
    }


    int makePrefSumNonNegative(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> q;
        long long cur_sum = 0;
        int op_count = 0;
        for (int i = 0; i < size(nums); i++) {
            cur_sum += static_cast<long long>(nums[i]);
            if (nums[i] < 0) {
                q.push(nums[i]);
                if (cur_sum < 0) {
                    cur_sum -= q.top();
                    q.pop();
                    op_count++;
                }
            }
        }
        return op_count;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().makePrefSumNonNegative(nums) << endl;
}
int main()
{
    test(get_list_int("[2,3,-5,4]"));
    test(get_list_int("[3,-5,-2,6]"));
    test(get_list_int("[10,-10,5,-1,-1,-1,-1,-1]"));
    return 0;
}