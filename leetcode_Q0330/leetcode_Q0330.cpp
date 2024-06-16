// leetcode_Q0330.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    static set<int> judge(const vector<int>& nums, int n) {
        set<int> missings;
        for (int i = 1; i < n; i++) {
            missings.insert(i);
        }
        unordered_set<int> before;
        before.insert(nums[0]);
        missings.erase(nums[0]);

        for (int i = 1; i < nums.size(); i++) {
            unordered_set<int> current(before);
            current.insert(nums[i]);
            missings.erase(nums[i]);
 
            for (auto&& v : before) {
                const auto sum1 = v + nums[i];
                current.insert(sum1);
                missings.erase(sum1);
            }
            before = current;
        }
        return missings;
    }
    static int tle(vector<int>& nums, int n) {

        struct state {
            vector<int> patches;
        };

        state s;
        for (;;) {
            const auto missings = judge(nums, n);
            if (missings.empty()) {
                break;
            }
            auto missing_top = *missings.cbegin();
            s.patches.emplace_back(missing_top);
            nums.emplace_back(missing_top);
        }
        return static_cast<int>(s.patches.size());
    }

    int minPatches(vector<int>& nums, int n) {
        int patch_count = 0;
        long long nl = n;
        long long first_missing = 1;
        int i = 0;
        while(first_missing <= nl){
            if (i < nums.size() && nums[i] <= first_missing) {
                first_missing += nums[i];
                i++;
            }
            else {
                patch_count++;
                first_missing += first_missing;
            }
        }
        return patch_count;
    }
};

void test(vector<int>&& nums, int n) {
    cout << Solution().minPatches(nums, n) << endl;
}

int main()
{
    test(get_list_int("[1,2,31,33]"), 2147483647);
    test(get_list_int("[1,5,10]"), 20);

    test(get_list_int("[1,3]"), 6);
    test(get_list_int("[1,2,2]"), 5);
}