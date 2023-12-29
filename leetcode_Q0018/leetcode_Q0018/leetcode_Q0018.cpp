// leetcode_Q0018.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:


    vector<vector<int>> fourSum1(const vector<int>& nums, int target) {
        vector<vector<int>> list;
        unordered_map<int64_t, int> map;
        set<tuple<int,int,int>> exists;

        for (int i = nums.size() - 1; i >= 0; i--) {
            map.insert(make_pair(nums[i], i));
        }

        for (int i = 0; i < nums.size() - 3; i++) {
            for (int j = i + 1; j < nums.size() - 2; j++) {
                for (int k = j + 1; k < nums.size() - 1; k++) {
                    const auto key = make_tuple(nums[i], nums[j], nums[k]);
                    if (exists.find(key) != cend(exists)) { continue; }
                    const auto remain = static_cast<int64_t>(target) - (static_cast<int64_t>(nums[i]) + static_cast<int64_t>(nums[j]) + static_cast<int64_t>(nums[k]));
                    auto it = map.find(remain);
                    if (it != cend(map) && k < it->second) {
                        exists.insert(key);
                        list.emplace_back(vector<int>{nums[i], nums[j], nums[k], static_cast<int>(it->first)});
                    }
                }
            }
        }
        return list;
    }


    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        if (nums.size() < 4) {
            return vector<vector<int>>();
        }
        if (nums.size() < 5) {
            return fourSum1(nums, target);
        }
        vector<int> working;
        int index = 0;
        for (; index < 4; index++) {
            working.emplace_back(nums[index]);
        }
        for (; index < nums.size(); index++) {
            if (nums[index - 4] != nums[index]) {
                working.emplace_back(nums[index]);
            }
        }
        return fourSum1(working, target);
    }
};


void output(vector<int>&& list, int target) {
    auto ret = Solution().fourSum(list, target);
    cout << "OUTPUT" << endl;
    for (auto&& innerList : ret)
    {
        for (auto&& value : innerList) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    output(vector<int> {1000000000, 1000000000, 1000000000, 1000000000}, -294967296);

    output(vector<int> {1000000000, 1000000000, 1000000000, 1000000000}, 0);

    output(vector<int> {0}, 0);

    output(vector<int> {1, 0, -1, 0, -2, 2}, 0);
    output(vector<int> {2,2,2,2,2,}, 8);
}

