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

    static bool check(const vector<pair<int, int>>& events, int n) {
        int detect_count = 0;
        auto it = cbegin(events);
        int cur_rectangles = 1;
        ++it;
        while (it != cend(events)) {
            if (it->second == 0) {
                cur_rectangles--;
            }
            else {
                cur_rectangles++;
            }
            if (cur_rectangles == 0) {
                detect_count++;
                if (detect_count > 1) {
                    if (it->first == n || next(it) == cend(events)) {
                        return false;
                    }
                    return true;
                }
            }
            ++it;
        }
        return false;
    }

    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        const auto m = size(rectangles);
        vector<pair<int, int>> events_horizontal;
        events_horizontal.reserve(m * 2);
        for (auto&& rectangle : rectangles) {
            events_horizontal.emplace_back(make_pair(rectangle[0], 1));
            events_horizontal.emplace_back(make_pair(rectangle[2], 0));
        }

        sort(begin(events_horizontal), end(events_horizontal));
        if (check(events_horizontal, n)) {
            return true;
        }

        vector<pair<int, int>> events_vertical;
        events_vertical.reserve(m * 2);
        for (auto&& rectangle : rectangles) {
            events_vertical.emplace_back(make_pair(rectangle[1], 1));
            events_vertical.emplace_back(make_pair(rectangle[3], 0));
        }
        sort(begin(events_vertical), end(events_vertical));
        return check(events_vertical, n);
    }
};

void test(int n, vector<vector<int>>&& rectangles) {
    cout << Solution().checkValidCuts(n, rectangles) << endl;
}

int main() {
    test(5, get_matrix_int("[[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]"));
    test(4, get_matrix_int("[[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]"));
    test(4, get_matrix_int("[[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]"));
    return 0;
}