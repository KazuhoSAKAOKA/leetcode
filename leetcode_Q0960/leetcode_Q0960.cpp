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
#include <exception>
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

    int minDeletionSize(vector<string>& strs) {
        const auto n = size(strs);
        const auto m = size(strs[0]);
        vector<int> dp(m, 1);

        auto check = [&](int prev, int cur)->bool {
            return all_of(cbegin(strs), cend(strs), [&](const string& s) {
                return s[prev] <= s[cur];
                });
            };

        for (int i = 1; i < m; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (dp[i] < dp[prev] + 1 && check(prev, i)) {
                    dp[i] = dp[prev] + 1;
                }
            }
        }
        
        return m - *max_element(cbegin(dp), cend(dp));
    }
};

static void test(vector<string>&& strs) {
    cout << Solution().minDeletionSize(strs) << endl;
}

int main()
{
    test(get_list_str(R"(["babca","bbazb"])"));
    test(get_list_str(R"(["edcba"])"));
    test(get_list_str(R"(["ghi","def","abc"])"));
    return 0;
}