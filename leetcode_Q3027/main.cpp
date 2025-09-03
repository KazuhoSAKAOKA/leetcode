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
    int numberOfPairs(vector<vector<int>>& points) {
        map<int, set<int>, std::greater<int>> point_map;
        for (auto&& point : points) {
            point_map[point[0]].insert(point[1]);
        }

        int count = 0;
        for (auto it = cbegin(point_map); it != cend(point_map); ++it) {
            const auto& xset = it->second;

            for (auto xit = cbegin(xset); xit != cend(xset); ++xit) {
                const auto& left_top = *xit;
                int most_left = INT_MAX;
                const auto nextxit = next(xit);
                if (nextxit != cend(xset)) {
                    count++;
                    most_left = *nextxit;
                }

                for (auto cur_yit = next(it); cur_yit != cend(point_map); ++cur_yit) {
                    const auto& cur_xset = cur_yit->second;
                    const auto candidate_it = cur_xset.lower_bound(left_top);
                    if (candidate_it != cend(cur_xset)) {
                        if (*candidate_it < most_left) {
                            count++;
                            most_left = *candidate_it;
                        }
                    }
                }
            }
        }
        return count;
    }
};

static void test(vector<vector<int>>&& points) {
    cout << Solution().numberOfPairs(points) << endl;
}

int main() {
    test(get_matrix_int("[[1,1],[2,2],[3,3]]"));
    test(get_matrix_int("[[6,2],[4,4],[2,6]]"));
    test(get_matrix_int("[[3,1],[1,3],[1,1]]"));
    return 0;
}