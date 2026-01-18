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

    static double binary_search_meguru(double ok, double ng, std::function<bool(double)> check) {
        constexpr double limit = 1e-5;
        while (abs(ng - ok) > limit) {
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

    double separateSquares(vector<vector<int>>& squares) {
        long long total = 0LL;
        long long min_value = LLONG_MAX;
        long long max_value = LLONG_MIN;
        for (auto&& sq : squares) {
            total += static_cast<long long>(sq[2]) * sq[2];
            min_value = min(min_value, static_cast<long long>(sq[1]));
            max_value = max(max_value, static_cast<long long>(sq[1]) + sq[2]);
        }
        const double half = static_cast<double>(total) / 2.0;

        const auto ans = binary_search_meguru(max_value, min_value,
            [&](double y)->bool {
                double under_area = 0;
                for (auto&& sq : squares) {
                    if (sq[1] + sq[2] <= y) {
                        under_area += static_cast<double>(static_cast<long long>(sq[2]) * sq[2]);
                    }
                    else if (sq[1] < y) {
                        under_area += (y - static_cast<double>(sq[1])) * sq[2];
                    }
                }
                return half <= under_area;
            });
        return ans;
    }
};

static void test(vector<vector<int>>&& squares) {
    cout << Solution().separateSquares(squares) << endl;
}
int main() {
    test(get_matrix_int("[[0,0,1],[2,2,1]]"));
    test(get_matrix_int("[[0,0,2],[1,1,1]]"));
    return 0;
}