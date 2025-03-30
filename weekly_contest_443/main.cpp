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
    vector<int> minCosts(vector<int>& cost) {
        vector<int> ans(size(cost));
        int cur_min_cost = INT_MAX;
        for (int i = 0; i < size(cost); i++) {
            cur_min_cost = min(cur_min_cost, cost[i]);
            ans[i] = cur_min_cost;
        }
        return ans;
    }
};
void test(vector<int>&& cost) {
    output(Solution().minCosts(cost));
}
static void run() {
test(get_list_int("[5,3,4,1,3,2]"));
test(get_list_int("[1,2,4,6,7]"));
}

}
namespace problem2 {
class Solution {
public:

    //static int get_len(const string& v, int index) {
    //    const int len = size(v) - index;
    //    for (int i = 0; i < len / 2; i++) {
    //        if (v[index + i] != v[size(v) - 1 - i]) {
    //            return i * 2;
    //        }
    //    }
    //    return len;
    //}

    //static int get_len_rev(const string& v, int index) {
    //    const int len = index + 1;
    //    for (int i = 0; i < len / 2; i++) {
    //        if (v[i] != v[len - i - 1]) {
    //            return i * 2;
    //        }
    //    }
    //    return len;
    //}
    //static int rec(const string& s, const string& t, int s_index, int t_index) {
    //    if (size(s) == s_index && -1 == t_index) {
    //        return 0;
    //    }
    //    if (size(s) == s_index) {
    //        return get_len_rev(t, t_index);
    //    }
    //    else if (-1 == t_index) {
    //        return get_len(s, s_index);
    //    }
    //    int max_len = 0;

    //    if (s[s_index] == t[t_index]) {
    //        max_len = max(max_len, rec(s, t, s_index + 1, t_index - 1) + 2);
    //    }
    //    max_len = max(max_len, rec(s, t, s_index, t_index - 1));
    //    max_len = max(max_len, rec(s, t, s_index + 1, t_index));
    //    return max_len;
    //}
    static bool is_palindrome(const string& s) {
        for (int i = 0; i < size(s) / 2; i++) {
            if (s[i] != s[size(s) - 1 - i]) {
                return false;
            }
        }
        return true;
    }
    int longestPalindrome(string s, string t) {
//        int longest = rec(s, t, 0, size(t) - 1);
        size_t longest = 0;
        for (int i = 0; i < size(s); i++) {
            for (int j = 0; j < size(t); j++) {
                for (int ilen = 0; ilen + i <= size(s); ilen++) {
                    for (int jlen = 0; jlen + j <= size(t); jlen++) {
                        const auto comb = s.substr(i, ilen) + t.substr(j, jlen);
                        if (is_palindrome(comb)) {
                            longest = max(longest, comb.size());
                        }
                    }
                }
            }
        }
        return static_cast<int>(longest);
    }
};

void test(string&& s, string&& t) {
    cout << Solution().longestPalindrome(s, t) << endl;
}
static void run() {
    test("abcde", "ecdba");
    test("b", "aaaa");
    test("a", "a");
    test("abc", "def");
}
}
namespace problem3 {
class Solution {
public:
    //auto trev = string(crbegin(t), crend(t));
//vector<vector<int>> dp(size(s), vector<int>(size(t), -1));
//for (int i = 0; i < size(t); i++) {
//    dp[0][i] = s[0] == trev[i] ? 1 : 0;
//}
//for (int i = 1; i < size(t); i++) {
//    dp[i][0] = s[i] == trev[0] ? 1 : 0;
//}

//for (int i = 1; i < size(s); i++) {
//    for (int j = 1; j < size(t); j++) {
//        if (s[i] == trev[j]) {
//            dp[i][j] = dp[i - 1][j - 1] + 1;
//        }
//        else {
//            dp[i][j] = 0;
//        }
//    }
//}


    static vector<int> manacher_even(const string& original) {
        const auto n_original = size(original);
        string s(2 * n_original + 1, '#');
        for (int i = 0; i < n_original; i++) { s[2 * i + 1] = original[i]; }
        const auto n = 2 * n_original + 1;
        vector<int> rad(n);
        int c = 0, r = 0;
        while (c < n) {
            while (0 <= c - r && c + r < n && s[c - r] == s[c + r]) r++;
            rad[c] = r;
            int k = 1;
            while (0 <= c - k && k + rad[c - k] < r) {
                rad[c + k] = rad[c - k];
                k++;
            }
            c += k;
            r -= k;
        }
        vector<int> radeven(size(original));

        for (int i = 0; i < n_original; i++) {
            radeven[i] = (rad[i * 2] - 1) / 2;
        }
        return radeven;
    }

    static vector<int> manacher_odd(const string& original) {
        int n = size(original);
        vector<int> rad(n);
        int c = 0, r = 0;

        while (c < n) {
            while (0 <= c - r && c + r < n && original[c - r] == original[c + r]) { r++; }
            rad[c] = r;
            int k = 1;
            while (0 <= c - k && k + rad[c - k] < r) {
                rad[c + k] = rad[c - k];
                k++;
            }
            c += k;
            r -= k;
        }
        return rad;
    }
    static vector<int> get_len_palindrome(const string& s) {
        const vector<int> s_rad_odd = manacher_odd(s);
        vector<int> after_len_s(size(s), 1);
        for (int i = 0; i < size(s); i++) {
            if (s_rad_odd[i] > 1) {
                after_len_s[i - (s_rad_odd[i] - 1)] = max(after_len_s[i - (s_rad_odd[i] - 1)], s_rad_odd[i] * 2 - 1);
            }
        }
        const vector<int> s_rad_even = manacher_even(s);
        for (int i = 0; i < size(s); i++) {
            if (s_rad_even[i] > 0) {
                after_len_s[i - s_rad_even[i]] = max(after_len_s[i - s_rad_even[i]], s_rad_even[i] * 2);
            }
        }
        return after_len_s;
    }

    static int rec(const string& s, const string& t, int s_index, int t_index, const vector<int>& s_singles, const vector<int>& t_singles, vector<vector<int>>& memo) {
        if (size(s) == s_index && size(t) == t_index) {
            return 0;
        }
        if (size(s) == s_index) {
            return t_singles[t_index];
        }
        else if (size(t) == t_index) {
            return s_singles[s_index];
        }

        if (memo[s_index][t_index] >= 0) {
            return memo[s_index][t_index];
        }


        int max_len = 0;

        if (s[s_index] == t[t_index]) {
            max_len = max(max_len, rec(s, t, s_index + 1, t_index + 1, s_singles, t_singles, memo) + 2);
        }
        max_len = max(max_len, t_singles[t_index]);
        max_len = max(max_len, s_singles[s_index]);
        memo[s_index][t_index] = max_len;
        return max_len;
    }


    int longestPalindrome(string s, string t) {
        const auto s_after = get_len_palindrome(s);
        const string trev = string(crbegin(t), crend(t));
        const auto t_after = get_len_palindrome(trev);
        vector<vector<int>> memo(size(s), vector<int>(size(t), -1));
        int longest = 0;
        for (int i = 0; i < size(s); i++) {
            for (int j = 0; j < size(t); j++) {
                longest = max(longest, rec(s, trev, i, j, s_after, t_after, memo));
            }
        }
        return longest;
    }
};
void test(string&& s, string&& t) {
    cout << Solution().longestPalindrome(s, t) << endl;
}
static void run() {
    test("jjh", "g");
    test("a", "a");
    test("abc", "def");
    test("b", "aaaa");
    test("abcde", "ecdba");
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