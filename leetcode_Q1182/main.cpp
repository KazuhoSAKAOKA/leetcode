#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"


using namespace std;
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        unordered_map<int, set<int>> color_pos_map;
        for (int i = 0; i < size(colors); i++) {
            color_pos_map[colors[i]].insert(i);
        }

        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& q : queries) {
            const auto i = q.front();
            const auto c = q.back();
            auto it = color_pos_map.find(c);
            if (it == cend(color_pos_map)) {
                ans.emplace_back(-1);
            }
            else {
                const auto& indexes = it->second;
                const auto it1 = indexes.lower_bound(i);
                int min_dist = INT_MAX;
                if (it1 != cend(indexes)) {
                    min_dist = min(min_dist, *it1 - i);
                }
                if (it1 != cbegin(indexes)) {
                    min_dist = min(min_dist, i - *prev(it1));
                }
                ans.emplace_back(min_dist);
            }
        }
        return ans;
    }
};
static void test(vector<int>&& colors, vector<vector<int>>&& queries) {
    output(Solution().shortestDistanceColor(colors, queries));
}
int main() {
    test(get_list_int("[1,1,2,1,3,2,2,3,3]"), get_matrix_int("[[1,3],[2,2],[6,1]]"));
    test(get_list_int("[1,2]"), get_matrix_int("[[0,3]]"));
    return 0;
}