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

    static vector<int> manacher(const string& s) {
        vector< int > radius(s.size());
        int i = 0, j = 0;
        while (i < s.size()) {
            while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
                ++j;
            }
            radius[i] = j;
            int k = 1;
            while (i - k >= 0 && i + k < s.size() && k + radius[i - k] < j) {
                radius[i + k] = radius[i - k];
                ++k;
            }
            i += k;
            j -= k;
        }
        return radius;
    }

    int maxPalindromes(string s, int k) {
        const auto n = size(s);
        if (k <= 1) { return n; }
        vector<vector<int>> steps(n);
        const vector<int> radius_odd = manacher(s);
        for (int i = 0; i < n; i++) {
            int r = (radius_odd[i] - 1) * 2 + 1;
            if (r >= k) {
                for (;  r >= k; r-=2) {
                    steps[i - (r - 1) / 2].push_back(r);
                }
            }
        }
        string sdash;
        sdash.reserve(n * 2 + 1);
        for (auto&& c : s) {
            sdash += c;
            sdash += '.';
        }
        sdash.pop_back();
        const vector<int> radius_even = manacher(sdash);
        for (int i = 0; i < n - 1; i++) {
            auto r = (radius_even[i * 2 + 1] / 2) * 2;
            if (r >= k) {
                for (; r >= k; r -= 2) {
                    steps[i - (r / 2) + 1].push_back(r);
                }
            }
        }
        vector<int> dp(n + 1);
        for (int i = 0; i < n; i++) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            for (auto&& s : steps[i]) {
                dp[i + s] = max(dp[i + s], dp[i] + 1);
            }
        }
        return dp.back();
    }
};

static void test(string s, int k) {
    cout << Solution().maxPalindromes(s, k) << endl;
}
int main() {
    test("fttfjofpnpfydwdwdnns", 2);

    test("abaccdbbd", 3);
    test("adbcda", 2);
    return 0;
}
