#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static int get_height(int i, int heighti, int j, int heightj) {
        const auto wdiff = abs(i - j);
        const auto arrival = min(heightj, heighti + wdiff);
        return arrival;
    }
    static int get_peak(int i, int heighti, int j, int heightj) {
        const auto wdiff = abs(i - j) - 1;
        const auto low = min(heighti, heightj);
        const auto high = max(heighti, heightj);
        const auto hdiff = high - low;
        if (wdiff <= hdiff) {
            return high;
        }
        else {
            const auto remain = wdiff - hdiff;
            return high + remain / 2 + remain % 2;
        }
    }
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        vector<pair<int, int>> work{ {1,0} };
        for (auto&& r : restrictions) {
            work.push_back({ r[0], r[1] });
        }
        sort(begin(work), end(work));
        const int m = size(work);
        vector<int> ltor(m);
        ltor[0] = 0;
        for (int i = 1; i < m; i++) {
            ltor[i] = get_height(work[i - 1].first, ltor[i - 1], work[i].first, work[i].second);
        }
        vector<int> rtol(m);
        rtol[m - 1] = work.back().second;
        for (int i = m - 2; i >= 0; i--) {
            rtol[i] = get_height(work[i + 1].first, rtol[i + 1], work[i].first, work[i].second);
        }

        int max_height = n - work.back().first + min(ltor[m - 1], rtol[m - 1]);
        for (int i = 0; i < m - 1; i++) {
            const auto peak = get_peak(work[i].first, min(ltor[i], rtol[i]), work[i + 1].first, min(ltor[i + 1], rtol[i + 1]));
            max_height = max(max_height, peak);
        }

        return max_height;
    }
};

static void test(int n, vector<vector<int>>&& restrictions) {
    cout << Solution().maxBuilding(n, restrictions) << endl;
}

int main() {
    //test(10, get_matrix_int("[[5,3],[2,5],[7,4],[10,3]]"));
    //test(4, get_matrix_int("[[2,4],[3,4],[4,0]]"));
    //test(10, get_matrix_int("[[6,0],[5,2],[7,0],[9,1],[2,4],[3,4],[4,0],[8,2],[10,0]]"));
    //test(5, get_matrix_int("[[2,1],[4,1]]"));
    test(10, get_matrix_int("[[8,5],[9,0],[6,2],[4,0],[3,2],[10,0],[5,3],[7,3],[2,4]]"));
    //test(6, get_matrix_int("[]"));
    return 0;
}
