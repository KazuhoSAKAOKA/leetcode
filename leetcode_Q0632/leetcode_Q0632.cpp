// leetcode_Q0632.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>


#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<pair<int, set<int>>> works;
        vector<int> indexes(size(nums));

        auto get_min_vals = [](vector<vector<int>>& nums, vector<int>& indexes)-> pair<int, set<int>> {
            int min_value = 1e5 + 1;
            set<int> min_set;
            for (int i = 0; i < size(nums); i++) {
                if (indexes[i] < size(nums[i])) {
                    if (nums[i][indexes[i]] < min_value) {
                        min_value = nums[i][indexes[i]];
                        min_set.clear();
                        min_set.insert(i);
                    }
                    else if (nums[i][indexes[i]] == min_value) {
                        min_set.insert(i);
                    }
                }
            }
            for (auto&& ind : min_set) {
                indexes[ind]++;
            }
            return { min_value, min_set };
            };

        for (;;) {
            const auto p = get_min_vals(nums, indexes);
            if (p.second.empty()) {
                break;
            }
            works.emplace_back(p);
        }

        int min_range = INT_MAX;
        pair<int, int> cur_min_range(0, INT_MAX);

        map<int, int> current_map;
        int l = 0;
        for (int r = 0; r < size(works); r++) {
            const auto& [value, indexes] = works[r];
            for (auto&& index : indexes) {
                current_map[index]++;
            }
            if (size(current_map) == size(nums)) {
                while (l <= r && size(current_map) == size(nums)) {
                    const auto& [value_l, indexes_l] = works[l];
                    if (any_of(cbegin(indexes_l), cend(indexes_l), [&](const auto& a) { return current_map[a] == 1; })) {
                        break;
                    }
                    for (auto&& index : indexes_l) {
                        if (current_map[index] == 1) {
                            current_map.erase(index);
                        }
                        else {
                            current_map[index]--;
                        }
                    }
                    l++;
                }
                const int cur_range = works[r].first - works[l].first;
                if (cur_range < min_range) {
                    min_range = cur_range;
                    cur_min_range = { works[l].first, works[r].first };
                }
            }
        }
        return vector<int>{ cur_min_range.first,cur_min_range.second };
    }
};

void test(vector<vector<int>>&& nums) {
    output(Solution().smallestRange(nums));
}
int main()
{
    test(get_matrix_int("[[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]"));
    test(get_matrix_int("[[1,2,3],[1,2,3],[1,2,3]]"));
    return 0;
}