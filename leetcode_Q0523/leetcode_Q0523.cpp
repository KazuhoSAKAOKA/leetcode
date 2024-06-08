// leetcode_Q0523.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static bool tle(const vector<int>& nums, int k) {
        unordered_set<int> before;
        before.insert(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            unordered_set<int> current;
            for (auto&& before_value : before) {
                const auto value = before_value + nums[i];
                if (value % k == 0) {
                    return true;
                }
                current.insert(value);
            }
            current.insert(nums[i]);
            before = current;
        }
        return false;
    }


    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefix_mod_map;
        prefix_mod_map[0] = -1;
        int prefix_mod = 0;
        for (int i = 0; i < nums.size(); i++) {
            prefix_mod = (prefix_mod + nums[i]) % k;
            const auto it = prefix_mod_map.find(prefix_mod);
            if (it == cend(prefix_mod_map)) {
                prefix_mod_map[prefix_mod] = i;
            }
            else {
                if (i - it->second > 1) {
                    return true;
                }
            }
        }

        return false;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().checkSubarraySum(nums, k) << endl;
}


int main()
{
    test(get_list_int("[23,2,4,6,6]"), 7);
    test(get_list_int("[23,2,4,6,7]"), 6);
    test(get_list_int("[23,2,6,4,7]"), 6);
    test(get_list_int("[23,2,6,4,7]"), 13);
}