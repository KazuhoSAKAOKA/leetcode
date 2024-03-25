// leetcode_Q0442.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;


class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        unordered_map<int, size_t> counts;
        for (auto&& value : nums) {
            counts[value]++;
        }
        vector<int> ans;
        for (auto&& [k, v] : counts) {
            if (v > 1) {
                ans.emplace_back(k);
            }
        }
        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().findDuplicates(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test({ 4,3,2,7,8,2,3,1 });
    test({ 1,1,2 });
    test({ 1 });
}