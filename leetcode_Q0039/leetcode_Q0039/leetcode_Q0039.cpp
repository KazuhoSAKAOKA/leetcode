// leetcode_Q0039.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:

    void combinationSum1(const vector<int>& candidates, int target, int beginIndex, vector<int>& current, int currentTotal,vector<vector<int>>& ans) {
        if (currentTotal == target) {
            ans.push_back(current);
            return;
        }
        if (target < currentTotal) {
            return;
        }

        for (auto i = beginIndex; i < candidates.size(); i++) {
            const auto v = candidates[i];
            const auto newTotal = currentTotal + v;
            if (newTotal <= target) {
                current.push_back(v);
                combinationSum1(candidates, target, i, current, newTotal, ans);
                current.pop_back();
            }
        }
    }


    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> temp;
        vector<vector<int>> ans;
        combinationSum1(candidates, target, 0, temp, 0, ans);
        return ans;
    }
};


void test(vector<int>&& candidates, int target) {
    const auto ret = Solution().combinationSum(candidates, target);
    for (auto&& v : ret)
    {
        for (auto&& vv : v) {
            std::cout << vv << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    test({ 2,3,6,7 }, 7);
    test({ 2,3,5 }, 8);
    test({ 2 }, 1);
}
