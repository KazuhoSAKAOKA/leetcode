// leetcode_Q0040.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;


class Solution {
public:

    void combinationSum2_rec(const map<int,int>::const_iterator& mapit, const map<int, int>::const_iterator& end, int target, vector<int>& current, int currentTotal, set<vector<int>>& ans) {
        if (currentTotal == target) {
            ans.insert(current);
            return;
        }
        if (mapit == end) { return; }
        auto [key, count] = *mapit;
        auto temp1(current);
        for (auto i = 0; i < count + 1; i++) {
            const auto newTotal = currentTotal + key * i;
            if (newTotal <= target) {
                if (0 < i) {
                    temp1.push_back(key);
                }
                combinationSum2_rec(next(mapit),end, target, temp1, newTotal, ans);
            }
            else {
                break;
            }
        }
    }


    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        map<int, int> map;
        set<vector<int>> set;
        for (auto&& v : candidates) {
            map[v]++;
        }
        vector<int> temp;
        combinationSum2_rec(cbegin(map),cend(map), target, temp, 0, set);
        vector<vector<int>> ans;
        for (auto&& list : set) {
            ans.emplace_back(list);
        }
        return ans;
    }
};


void test(vector<int>&& candidates, int target) {
    const auto ret = Solution().combinationSum2(candidates, target);
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
    test({ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, 30);


    test({ 10,1,2,7,6,1,5 }, 8);
    test({ 2,5,2,1,2 }, 5);
    test({ 2 }, 1);
}
