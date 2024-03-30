// leetcode_Q0992.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        vector<unordered_set<int>> before;
        vector<unordered_set<int>> current;
        int total = 0;
        for (int i = 0; i < nums.size(); i++) {
            int c = 0;
            for (auto&& before_subarr_kinds : before) {
                before_subarr_kinds.insert(nums[i]);
                if (before_subarr_kinds.size() <= k) {
                    if (before_subarr_kinds.size() == k) {
                        c++;
                    }
                    current.emplace_back(before_subarr_kinds);
                }
            }
            unordered_set<int> append{ nums[i] };
            if (k == 1) {
                c++;
            }
            current.emplace_back(append);

            total += c;

            swap(before, current);
            current.clear();
        }

        return total;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().subarraysWithKDistinct(nums, k) << endl;
}

int main()
{
    test({ 1,2,1,2,3, }, 2);
    test({ 1,2,1,3,4, }, 3);
}