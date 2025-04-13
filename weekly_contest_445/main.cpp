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
    int findClosest(int x, int y, int z) {
        const auto p1dist = abs(x - z);
        const auto p2dist = abs(y - z);
        if (p1dist == p2dist) { return 0; }
        return p1dist < p2dist ? 1 : 2;
    }
};

static void run() {
    
}

}
namespace problem2 {
class Solution {
public:
    string smallestPalindrome(string s) {
        const auto n = size(s);
        map<char, int> freqs;
        for (auto&& c : s) {
            freqs[c]++;
        }
        string ans(n, ' ');
        int index = 0;
        char center = -1;
        for (auto&& [c, count] : freqs) {
            if ((count % 2) == 1) {
                if (center >= 0) { throw exception(); }
                center = c;
            }
            for (int i = 0; i < count / 2; i++) {
                ans[index] = c;
                ans[n - index - 1] = c;
                index++;
            }
        }
        if (center >= 0) {
            ans[n / 2] = center;
        }
        return ans;
    }
};
void test(string&& s) {
    cout << Solution().smallestPalindrome(s) << endl;
}
static void run() {
    test("z");
    test("babab");
    test("daccad");
}

}
namespace problem3 {
class Solution {
public:


    static string tle(string s, int k) {
        const auto n = size(s);
        map<char, int> freqs;
        for (auto&& c : s) {
            freqs[c]++;
        }
        int index = 0;
        string first_half;
        first_half.reserve(n / 2);
        char center = -1;
        for (auto&& [c, count] : freqs) {
            if ((count % 2) == 1) {
                if (center >= 0) { throw exception(); }
                center = c;
            }
            if (count > 1) {
                first_half.append(count / 2, c);
            }
        }

        string ans;
        ans.reserve(n);
        ans += first_half;
        if (center >= 0) {
            ans += center;
        }
        ans.insert(end(ans), crbegin(first_half), crend(first_half));
        return ans;
    }


    static long long binomial_coefficient_capped(int n, int r, long long cap) {
        if (r < 0 || r > n) { return 0; }
        r = min(r, n - r);
        long long res = 1LL;
        for (int i = 1; i <= r; ++i) {
            if (res > (cap * i) / (n - r + i)) {
                return cap + 1;
            }
            res = res * (n - r + i) / i;
        }
        return res;
    }

    static long long P_capped(const vector<int>& freqs, long long cap) {
        long long ways = 1;
        int cur = accumulate(cbegin(freqs), cend(freqs), 0);
        for (int c : freqs) {
            if (c == 0) { continue; }
            long long b = binomial_coefficient_capped(cur, c, cap);
            if (b > cap) { return cap + 1; }
            if (ways > cap / b) { return cap + 1; }
            ways *= b;
            cur -= c;
        }
        return ways;
    }


    string nth_permutation(string& s, int k) {
        map<char, int> freqs;
        for (auto&& c : s) {
            freqs[c]++;
        }
        const auto n = size(s);

        vector<char> char_list;
        vector<int> freq_list;
        char_list.reserve(size(freqs));
        freq_list.reserve(size(freqs));
        for (auto&& [c, count] : freqs) {
            freq_list.emplace_back(count);
            char_list.emplace_back(c);
        }
        int index = 0;
        string ans;

        int remain = k;

        auto search_next = [&]()->bool {
            int i = 0;
            while (i < size(freq_list)) {
                if (freq_list[i] == 0) {
                    i++;
                    continue;
                }
                freq_list[i]--;
                const auto count = P_capped(freq_list, remain);
                if (remain <= count) {
                    ans += char_list[i];
                    index++;
                    return true;
                }
                else {
                    remain -= count;
                    freq_list[i]++;
                    i++;
                }
            }
            return false;
            };

        while (index < size(s)) {
            if (!search_next()) {
                return "";
            }
        }

        return ans;
    }


    string smallestPalindrome(string s, int k) {
        const auto n = size(s);
        if (n == 1) {
            return k == 1 ? s : "";
        }
        map<char, int> freqs;
        for (auto&& c : s) {
            freqs[c]++;
        }
        
        int index = 0;

        string first_half;
        first_half.reserve(n / 2);
        char center = -1;
        for (auto&& [c, count] : freqs) {
            if ((count % 2) == 1) {
                if (center >= 0) { throw exception(); }
                center = c;
            }
            if (count > 1) {
                first_half.append(count / 2, c);
            }
        }

        string sorted = nth_permutation(first_half, k);
        if (sorted.empty()) {
            return "";
        }
        string ans;
        ans.reserve(n);
        ans += sorted;
        if (center >= 0) {
            ans += center;
        }
        ans.insert(end(ans), crbegin(sorted), crend(sorted));
        return ans;
    }
};
void test(string&& s, int k) {
    cout << Solution().smallestPalindrome(s, k) << endl;
}
static void run() {
    test("baab", 2);
    test("bacab", 1);
    test("aa", 2);
}

}
namespace problem4 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    static string get_div_modulo(const string& val, int b, int& mod) {
        long long prev = 0;
        string dived;
        for (int i = 0; i < size(val); i++) {
            prev *= 10;
            const auto cur = static_cast<int>(val[i] - '0') + prev;
            const auto d = cur / b;
            if (!dived.empty() || d != 0) {
                dived += static_cast<char>(d + '0');
            }
            prev = cur % b;
        }
        mod = prev;
        return dived;
    }

    static vector<int> convert_base(const string& val, int b) {
        if (val == "0") { return { 0 }; }
        vector<int> digits;
        long long active_vals = 0;
        string current(val);
        while (!current.empty()) {
            int mod = 0;
            current = get_div_modulo(current, b, mod);
            digits.emplace_back(mod);
        }
        return vector<int>(crbegin(digits), crend(digits));
    }

    static long long digitdp(const string& val, int b) {
        if (val == "0") { return 0; }
        const vector<int> digits = convert_base(val, b);
        const auto n = size(digits);
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(b, vector<long long>(2, 0LL)));
        dp[0][digits[0]][1] = 1LL;
        for (int i = 1; i < digits[0]; i++) {
            dp[0][i][0] = 1LL;
        }
        for (int i = 1; i < n; i++) {
            if (digits[i - 1] <= digits[i]) {
                dp[i][digits[i]][1] = dp[i - 1][digits[i - 1]][1];
                dp[i][digits[i]][1] %= MODULO;
            }
            dp[i][0][0] = dp[i - 1][0][0];
            long long tot1 = dp[i - 1][0][0];
            
            for (int j = 1; j < b; j++) {
                tot1 += dp[i - 1][j][0];
                tot1 %= MODULO;
                dp[i][j][0] += tot1;
                dp[i][j][0] += 1;
                dp[i][j][0] %= MODULO;
            }
            long long tot2 = dp[i - 1][0][1];
            for (int j = 1; j < digits[i]; j++) {
                tot2 += dp[i - 1][j][1];
                tot2 %= MODULO;
                dp[i][j][0] += tot2;
                dp[i][j][0] %= MODULO;
            }
        }
        long long total = 0;
        for (int i = 0; i < b; i++) {
            total += dp[n - 1][i][0];
            total %= MODULO;
            total += dp[n - 1][i][1];
            total %= MODULO;
        }

        return total;
    }
    static string dec(const string& r) {
        string v(r);
        for (int i = size(r) - 1; i >= 0; i--) {
            if (v[i] != '0') {
                v[i]--;
                return v;
            }
            v[i] = '9';
        }
        return v;
    }
    int countNumbers(string l, string r, int b) {
        auto v = digitdp(r, b) - digitdp(dec(l), b);
        if (v < 0) {
            v = (v + MODULO) % MODULO;
        }
        return static_cast<int>(v);
    }
};
void test(string&& l, string&& r, int b) {
    cout << Solution().countNumbers(l, r, b) << endl;
}

static void run() {
    test("1", "1", 2);
    test("2", "7", 2);
    test("23", "28", 8);
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    //problem4::run();
    return 0;
}