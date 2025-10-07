#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        const auto n = size(rains);
        vector<int> ans(n, 0);
        map<int, int> lake_index_map;
        set<int> dry_day_set;

        for (int i = 0; i < n; i++) {
            if (rains[i] == 0) {
                dry_day_set.insert(i);
            }
            else {
                ans[i] = -1;
                const auto lake = rains[i];
                auto it = lake_index_map.find(lake);
                if (it == cend(lake_index_map)) {
                    lake_index_map.insert({ lake, i });
                }
                else {
                    auto start = it->second;
                    auto dryit = dry_day_set.lower_bound(start);
                    if (dryit == cend(dry_day_set)) {
                        return {};
                    }
                    ans[*dryit] = lake;
                    dry_day_set.erase(dryit);
                    it->second = i;
                }
            }
        }
        int v = 0;
        if (!lake_index_map.empty()) {
            v = cbegin(lake_index_map)->first;
        }
        for (auto&& remain : dry_day_set) {
            ans[remain] = v;
        }
        return ans;
    }
};

static void test(vector<int>&& rains) {
    output(Solution().avoidFlood(rains));
}

int main() {
    test(get_list_int("[2,3,0,0,3,1,0,1,0,2,2]"));
    test(get_list_int("[1,0,2,0,3,0,2,0,0,0,1,2,3]"));
    test(get_list_int("[1,2,3,4]"));
    test(get_list_int("[1,2,0,0,2,1]"));
    test(get_list_int("[1,2,0,1,2]"));
    return 0;
}