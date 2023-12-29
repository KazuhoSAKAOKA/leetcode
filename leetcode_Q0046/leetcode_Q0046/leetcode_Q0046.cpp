// leetcode_Q0046.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:

    void permute_rec(const vector<int>& nums, const unordered_set<size_t>& used, vector<int>& current, vector<vector<int>>& ret) {
        if (nums.size() <= used.size()) {
            ret.emplace_back(current);
        }
        unordered_set<size_t> my(used);
        for (size_t i = 0; i < nums.size(); i++) {
            if (used.find(i) != cend(used)) { continue; }
            current.emplace_back(nums[i]);
            my.insert(i);
            permute_rec(nums, my, current, ret);
            my.erase(i);
            current.pop_back();
        }
    }


    vector<vector<int>> permute(vector<int>& nums) {
        unordered_set<size_t> used;
        vector<vector<int>> ret;
        vector<int> buffer;
        permute_rec(nums, used, buffer, ret);
        return ret;
    }
};

void test(vector<int>&& nums) {
    const auto ret = Solution().permute(nums);
    for (auto&& list : ret) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
}

int main()
{
    test({ 1,2,3 });
    test({ 0,1 });
    test({1});
}

