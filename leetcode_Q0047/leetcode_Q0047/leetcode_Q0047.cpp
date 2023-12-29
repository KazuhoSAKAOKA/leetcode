// leetcode_Q0047.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <vector>
#include <numeric>
#include <unordered_set>
using namespace std;

class Solution {
public:

    void permute_rec(const map<int, size_t>& numsMap, vector<int>& current, vector<vector<int>>& ret) {
        bool existany = false;
        for (auto&&[key,num] : numsMap) {
            if (num == 0) { continue; }
            existany = true;
            map<int, size_t> copymap(numsMap);
            copymap[key]--;
            current.emplace_back(key);
            permute_rec(copymap, current, ret);
            current.pop_back();
        }
        if (!existany) {
            ret.emplace_back(current);
        }
    }


    vector<vector<int>> permuteUnique(vector<int>& nums) {
        map<int, size_t> map;
        for (auto&& value : nums) {
            map[value]++;
        }
        vector<vector<int>> ret;
        vector<int> buffer;
        permute_rec(map, buffer, ret);
        return ret;
    }
};



void test(vector<int>&& nums) {
    const auto ret = Solution().permuteUnique(nums);
    for (auto&& list : ret) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }

    cout << endl;
}

int main()
{
    test({1,1,2,});
    test({1,2,3,});
}

