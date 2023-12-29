// leetcode_Q0090.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:

    void subsets_bt(map<int, int>::const_iterator iterator, map<int, int>::const_iterator end_it, int remain, vector<int>& current, vector<vector<int>>& ans) {
        if (remain < 0) {
            return;
        }
        if (remain == 0) {
            ans.emplace_back(current);
            return;
        }
        for (auto it = iterator; it != end_it; ++it) {
            for (auto i = 0; i < it->second; i++) {
                current.emplace_back(it->first);
                subsets_bt(next(it), end_it, remain - i - 1, current, ans);
            }
            for (auto i = 0; i < it->second; i++) { current.pop_back(); }
        }
    }

    void subsets_nums(int size, const map<int, int>& nums_map, vector<vector<int>>& ans) {
        for (int i = 0; i <= size; i++) {
            vector<int> current;
            subsets_bt(cbegin(nums_map), cend(nums_map), i, current, ans);
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        map<int, int> map;
        for (auto&& value : nums) {
            map[value]++;
        }
        vector<vector<int>> ans;
        subsets_nums(nums.size(), map, ans);
        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto listlist = Solution().subsetsWithDup(nums);
    for (auto&& list : listlist) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
}

int main()
{
    test({ 1,2,2 });
    test({0});
}

