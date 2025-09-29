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
    using memo_key_t = pair<int, int>;
    using memo_t = map<memo_key_t, int>;


    static int div(const vector<int>& values, int index1, int index2, memo_t& memo) {
        const auto n = size(values);
        if (index1 == index2) {
            return 0;
        }
        if (index2 - index1 == 1) {
            return 0;
        }
        if (index2 - index1 == 2) {
            return values[index1] * values[index2] * values[index1 + 1];
        }
        const auto key = make_pair(index1, index2);
        auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int min_score = INT_MAX;
        for (int i = index1 + 1; i <= index2 - 1; i++) {
            const auto v1 = div(values, index1, i, memo);
            const auto v2 = values[index1] * values[index2] * values[i];
            const auto v3 = div(values, i, index2, memo);;
            const auto score = v1 + v2 + v3;
            min_score = min(min_score, score);
        }
        memo[key] = min_score;
        return min_score;
    }


    int minScoreTriangulation(vector<int>& values) {
        memo_t memo;
        return div(values, 0, size(values) - 1, memo);
    }
};
static void test(vector<int>&& values) {
    cout << Solution().minScoreTriangulation(values) << endl;
}
int main() {
    test(get_list_int("[3,7,4,5]"));
    test(get_list_int("[1,3,1,4,1,5]"));
    test(get_list_int("[1,2,3]"));
    return 0;
}