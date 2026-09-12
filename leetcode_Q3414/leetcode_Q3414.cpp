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
#include <bitset>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        const auto n = size(intervals);
        vector<size_t> indexes(n);
        for (size_t i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](auto a, auto b) {return intervals[a][1] < intervals[b][1]; });
        vector<vector<long long>> dp(4, vector<long long>(n));
        vector<vector<set<int>>> froms(4, vector<set<int>>(n));

        dp[0][0] = intervals[indexes[0]][2];
        froms[0][0].insert(indexes[0]);
        for (size_t i = 1; i < n; i++) {
            if (dp[0][i - 1] < intervals[indexes[i]][2] || 
                (dp[0][i - 1] == intervals[indexes[i]][2] && indexes[i] < *cbegin(froms[0][i - 1]))) {
                dp[0][i] = intervals[indexes[i]][2];
                froms[0][i].insert(indexes[i]);
            }
            else {
                dp[0][i] = dp[0][i - 1];
                froms[0][i] = froms[0][i - 1];
            }
        }

        for (size_t j = 1; j < 4; j++) {
            for (size_t i = j; i < n; i++) {
                auto check = [&](int index)->bool {
                    return intervals[indexes[index]][1] < intervals[indexes[i]][0];
                    };
                if (!check(0)) {
                    dp[j][i] = dp[j][i - 1];
                    froms[j][i] = froms[j][i - 1];
                    continue;
                }
                int ok = 0;
                int ng = i;
                const auto index = binary_search_meguru<int>(ok, ng, check);

                const auto new_val = dp[j - 1][index] + intervals[indexes[i]][2];

                if (dp[j][i - 1] == new_val) {
                    dp[j][i] = new_val;
                    set<int> temp = froms[j - 1][index];
                    temp.insert(indexes[i]);
                    if (temp < froms[j][i - 1]) {
                        froms[j][i] = temp;
                    }
                    else {
                        froms[j][i] = froms[j][i - 1];
                    }
                }else if (dp[j][i - 1] < new_val) {
                    dp[j][i] = new_val;
                    froms[j][i] = froms[j - 1][index];
                    froms[j][i].insert(indexes[i]);
                }
                else {
                    dp[j][i] = dp[j][i - 1];
                    froms[j][i] = froms[j][i - 1];
                }
            }
        }
        int best_score = 0;
        set<int> best_ans;
        for (int j = 0; j < 4; j++) {
            if (best_score <dp[j].back() || (best_score == dp[j].back() && froms[j].back() < best_ans)) {
                best_score = dp[j].back();
                best_ans = froms[j].back();
            }
        }

        return vector<int>(cbegin(best_ans), cend(best_ans));
    }
};

static void test(vector<vector<int>>&& intervals) {
    output(Solution().maximumWeight(intervals));
}
int main() {
#include <filesystem>
    test(get_matrix_int(get_text_from_file(std::filesystem::path("./test_case.txt"))));
    test(get_matrix_int("[[1,1,1000000000],[1,1,1000000000],[1,1,1000000000],[1,1,1000000000]]"));
    test(get_matrix_int("[[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]"));
    test(get_matrix_int("[[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]"));
    return 0;
}
