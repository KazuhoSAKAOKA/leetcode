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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        map<int, int> subarrmap;

        map<int, int> fmap;

        for (int i = 0; i < k; i++) {
            fmap[nums[i]]++;
        }

        auto update = [](map<int, int>& target_map,const map<int, int>& mp) {
            for (auto&& [v, c] : mp) {
                if (c > 0) {
                    target_map[v]++;
                }
            }
            };

        update(subarrmap, fmap);

        for (int i = k; i < size(nums); i++) {
            fmap[nums[i]]++;
            fmap[nums[i-k]]--;
            update(subarrmap, fmap);
        }

        for (auto it = crbegin(subarrmap); it != crend(subarrmap); ++it) {
            if (it->second == 1) {
                return it->first;
            }
        }
        return -1;

    }
}; 
void test(vector<int>&& nums, int k) {
    cout << Solution().largestInteger(nums, k) << endl;
}
static void run() {
    test(get_list_int("[3,9,7,2,1,7]"), 4);
    test(get_list_int("[0,0]"), 2);
    test(get_list_int("[3,9,2,1,7]"), 3);
    test(get_list_int("[0,0]"), 0);
}
}
namespace problem2 {
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

    static int get_distance(char a, char b) {
        const auto s = min(a, b);
        const auto l = max(a, b);
        const int dis1 = l - s;
        const int dis2 = s + 26 - l;
        return min(dis1, dis2);
    }

    static bool check1(const string& s, int first, int last, int max_dist, int count) {
        if (count == 0) {
            return true;
        }
        if (count == 1) {
            return last - first >= 0;
        }
        const auto remain = last - first + 1;
        if (count > remain) {
            return false;
        }
        for (int i = first; i < first + count / 2; i++) {
            for (int j = last; (j - i + 1) - count / 2 >= 0; j--) {
                const auto remain1 = j - i + 1;
                if (count > remain1) {
                    break;
                }
                const int dist = get_distance(s[i], s[j]);
                if (dist <= max_dist) {
                    if (check1(s, i + 1, j - 1, max_dist - dist, count - 2)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    static int tle(string&& s, int k) {
        auto check = [&](int len)->bool {
            return check1(s, 0, size(s) - 1, k, len);
            };
        return binary_search_meguru<int>(1, size(s) + 1, check);
    }

    static void max_opt(int& max_value, int cur_value, int l, int r) {
        int v = cur_value;
        if (r - l > 1) {
            v++;
        }
        max_value = max(max_value, v);
    }

    static int wa(string&& s, int k) {
        const int N = size(s);
        int max_len = 1;
        vector<vector<map<int, int>>> dp(N, vector<map<int, int>>(N, map<int, int>()));
        for (int r = N - 1; r > 0; r--) {
            dp[0][r][k] = 0;
            const auto dist = get_distance(s[0], s[r]);
            if (dist <= k) {
                dp[0][r][k - dist] = 2;
                max_opt(max_len, dp[0][r][k - dist], 0, r);
            }
        }
        for (int l = 1; l < N; l++) {
            dp[l][N - 1][k] = 0;
            const auto dist = get_distance(s[l], s[N - 1]);
            if (dist <= k) {
                dp[l][N - 1][k - dist] = 2;
                max_opt(max_len, dp[l][N - 1][k - dist], l, N - 1);
            }
        }
        for (int l = 1; l < N; l++) {
            for (int r = N - 2; r > l; r--) {
                dp[l][r][k] = dp[l - 1][r + 1][k];
                const auto dist = get_distance(s[l], s[r]);
                if (dist <= k) {
                    dp[l][r][k - dist] = dp[l - 1][r + 1][k] + 2;
                    max_opt(max_len, dp[l][r][k - dist], l, r);
                }
                for (auto&& [op, count] : dp[l - 1][r + 1]) {
                    dp[l][r][op] = max(dp[l][r][op], count);
                    if (dist <= op) {
                        dp[l][r][op - dist] = max(dp[l][r][op - dist], count + 2);
                        max_opt(max_len, dp[l][r][op - dist], l, r);
                    }
                }
            }
        }
        return max_len;
    }

    static int rec(const string& s, int left, int right, int k, vector<vector<vector<int>>>& memo) {
        if (left > right) {
            return 0;
        }
        if (left == right) {
            return 1;
        }
        if (memo[left][right][k] >= 0) {
            return memo[left][right][k];
        }

        int max_length = rec(s, left + 1, right, k, memo);
        max_length = max(max_length, rec(s, left, right - 1, k, memo));
        const int dist = get_distance(s[left], s[right]);
        if (dist <= k) {
            max_length = max(max_length, rec(s, left + 1, right - 1, k - dist, memo) + 2);
        }
        memo[left][right][k] = max_length;
        return max_length;
    }
    int longestPalindromicSubsequence(string s, int k) {
        const int N = size(s);
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(k + 1, -1)));
        return rec(s, 0, N - 1, k, dp);
    }
};
void test(string&& s, int k) {
    cout << Solution().longestPalindromicSubsequence(s, k) << endl;
}
static void run() {
    test("kdnssvxkbapiwwsagzfbimlwfohpjuyteglbyoxrxrtoiq", 21);
    test("abced", 2);
    test("aaazzz", 4);
    test("wehzr", 3);
    test("lbg", 15);
    test("vd", 10);
}
}
namespace problem3 {

class Solution {
public:

    int maxSum(vector<int>& nums, int k, int m) {
        const int n = size(nums);
        vector<int> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }

        vector<vector<int>> dp(k, vector<int>(n, -1));
        dp[0][0] = 0;
        for (int j = 1; j < n; j++) {
            dp[0][j] = max(dp[0][j - 1], prefix_sums[j] - prefix_sums[j - 1]);
        }

        for (int i = 0; i < k; i++) {
            dp[i][0] = 0;
            for (int j = 1; j < n; j++) {
                dp[i][j] = max(dp[i][j - 1], prefix_sums[i + j] - prefix_sums[i]);
            }
        }
        /*
        int n = nums.size();
        vector<int> prefix(n + 1, 0);

        partial_sum(nums.begin(), nums.end(), prefix.begin() + 1);

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, -1e9));

        for (int j = 0; j <= n; j++) {
            dp[0][j] = 0;
        }

        for (int i = 0; i < k; i++) {
            int best = -1e9;
            for (int j = 0; j <= n; j++) {
                if (j > 0)
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i + 1][j - 1]);

                if (j - m >= 0)
                    best = max(best, dp[i][j - m] - prefix[j - m]);

                if (best != -1e9)
                    dp[i + 1][j] = max(dp[i + 1][j], prefix[j] + best);
            }
        }

        return dp[k][n];
        */
    }
};

void test(vector<int>&& nums, int k, int m) {
    cout << Solution().maxSum(nums, k, m) << endl;
}

static void run() {
    test(get_list_int("[-2,-10,15,12,8,11,5]"), 3, 2);
    test(get_list_int("[1,2,-1,3,3,4]"), 2, 2);
    test(get_list_int("[-10,3,-1,-2]"), 4, 1);
}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}