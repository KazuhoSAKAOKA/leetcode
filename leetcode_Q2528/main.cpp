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

    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
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
    long long maxPower(vector<int>& stations, int r, int k) {
        const long long n = size(stations);
        vector<long long> prefix_sums(n + 1);
        long long min_pow = INT_MAX;
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] += prefix_sums[i] + stations[i];
            min_pow = min(min_pow, static_cast<long long>(stations[i]));
        }

        vector<long long> diffs(n + 1);
        const auto ans = binary_search_meguru<long long>(min_pow, prefix_sums.back() + k + 1,
            [&](long long v)->bool {
                fill(begin(diffs), end(diffs), 0LL);
                long long remain = k;
                long long current = 0;
                for (long long i = 0; i < n; i++) {
                    current += diffs[i];
                    const long long base_val = prefix_sums[min(n, i + r + 1)] - prefix_sums[max(0LL, i - r)];
                    if ((current + base_val) < v) {
                        const auto shortages = v - (current + base_val);
                        if (remain < shortages) {
                            return false;
                        }
                        current += shortages;
                        remain -= shortages;
                        diffs[min(n, i + 2 * r + 1)] = -shortages;
                    }
                }

                return true;
            });

        return ans;
    }
};
static void test(vector<int>&& stations, int r, int k) {
    cout << Solution().maxPower(stations, r, k) << endl;
}
int main() {
    test(get_list_int("[13,12,8,14,7]"), 2, 23);
    test(get_list_int("[1,2,4,5,0]"), 1, 2);
    test(get_list_int("[4,4,4,4]"), 0, 3);

	return 0;
}