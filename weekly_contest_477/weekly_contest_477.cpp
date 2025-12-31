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
    static vector<int> get_digits_remove0_rev(int n) {
        if (n == 0) {
            return { 0 };
        }
        vector<int> digits;
        int cur(n);
        while (cur > 0) {
            int d = cur % 10;
            if (d != 0) {
                digits.emplace_back(d);
            }
            cur /= 10;
        }
        return digits;
    }
    long long sumAndMultiply(int n) {
        if (n == 0) { return 0LL; }
        const auto digits = get_digits_remove0_rev(n);
        const auto sum = accumulate(cbegin(digits), cend(digits), 0LL);
        long long total = 0;
        long long base = sum;
        for (auto&& d : digits) {
            total += d * base;
            base *= 10LL;
        }
        return total;
    }
};
static void test(int n) {
    cout << Solution().sumAndMultiply(n) << endl;
}

static void run() {
    test(10203004);
    test(1000);
}
}
namespace problem2 {
class Solution {
public:
    static int tle(vector<int>& nums) {
        const int n = size(nums);
        if (n < 2) {
            return 0;
        }
        int max_len = 0;

        vector<int> prefix_xors(n + 1);
        vector<int> prefix_evens(n + 1);
        vector<int> prefix_odds(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_xors[i + 1] = prefix_xors[i] ^ nums[i];
            prefix_evens[i + 1] = prefix_evens[i] + ((nums[i] % 2 == 0) ? 1 : 0);
            prefix_odds[i + 1] = prefix_odds[i] + ((nums[i] % 2 == 0) ? 0 : 1);
        }
        for (int len = (n / 2) * 2; len > 0; len -= 2) {
            for (int i = 0; i + len <= n; i++) {
                const auto x1 = prefix_xors[i];
                const auto x2 = prefix_xors[i + len];
                const auto xors = x2 ^ x1;
                const auto evens = prefix_evens[i + len] - prefix_evens[i];
                const auto odds = prefix_odds[i + len] - prefix_odds[i];
                if (xors == 0 && evens == odds) {
                    return len;
                }
            }
        }
        return 0;
        return max_len;
    }


    int maxBalancedSubarray(vector<int>& nums) {
        const int n = size(nums);
        if (n < 2) {
            return 0;
        }
        int max_len = 0;

        map<pair<int, int>, int> index_map{ {{0,0}, 0 } };

        int cur_xor = 0;
        int cur_even_count = 0;
        int cur_odd_count = 0;

        for (int i = 0; i < n; i++) {
            cur_xor = cur_xor ^ nums[i];
            cur_even_count += (nums[i] % 2 == 0) ? 1 : 0;
            cur_odd_count += (nums[i] % 2 == 0) ? 0 : 1;
            const auto cur_diff = cur_even_count - cur_odd_count;
            const auto cur_expected = make_pair(cur_xor, cur_diff);
            auto it = index_map.find(cur_expected);
            if (it != cend(index_map)) {
                max_len = max(max_len, i - it->second + 1);
            }
            index_map.insert({ {cur_xor, cur_diff}, i + 1 });
        }
        return max_len;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maxBalancedSubarray(nums) << endl;
}
static void run() {
    test(get_list_int("[3,1,3,2,0]"));
    test(get_list_int("[3,2,8,5,4,14,9,15]"));
    test(get_list_int("[0]"));
}
}
namespace problem3 {
class Solution {
public:

    long long modpow(long long a, long long e, long long M) {
        long long r = 1;
        while (e > 0) {
            if (e & 1) r = r * a % M;
            a = a * a % M;
            e >>= 1;
        }
        return r;
    }

    long long modinv(long long a, long long M) {
        return modpow(a, M - 2, M);
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(s);
        vector<long long> prefix_sums_digits(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums_digits[i + 1] = prefix_sums_digits[i] + static_cast<long long>(s[i] - '0');
        }
        vector<long long> prefix_nums(n + 1);
        vector<long long> bases(n + 1);
        bases[n] = 1LL;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                bases[i] = bases[i + 1];
                prefix_nums[i] = prefix_nums[i + 1];
            }
            else {
                const long long v = static_cast<long long>(s[i] - '0');
                bases[i] = bases[i + 1] * 10;
                bases[i] %= MODULO;
                prefix_nums[i] = prefix_nums[i + 1] + bases[i + 1] * v;
                prefix_nums[i] %= MODULO;
            }
        }
        const auto m = size(queries);
        vector<int> ans;
        ans.reserve(m);

        for (auto&& query : queries) {
            const auto l = query[0];
            const auto r = query[1];

            long long sum = prefix_sums_digits[r + 1] - prefix_sums_digits[l];
            if (sum < 0) { sum += MODULO; }
            
            long long x1 = prefix_nums[l] - prefix_nums[r + 1];
            if (x1 < 0) {
                x1 += MODULO;
            }
            long long inv = modinv(bases[r + 1], MODULO);
            long long x2 = (x1 * inv) % MODULO;
            long long v = (x2 * sum) % MODULO;
            ans.emplace_back(v);
        }


        return ans;
    }
};
static void test(string&& s, vector<vector<int>>&& queries) {
    output(Solution().sumAndMultiply(s, queries));
}
static void run() {
    test("56225714134", get_matrix_int("[[0,1],[0,2],[0,3],[0,4],[0,5],[0,8],[0,9],[1,3],[1,5],[1,6],[1,7],[1,9],[1,10],[2,2],[2,3],[2,4],[2,6],[2,7],[2,9],[2,10],[3,3],[3,4],[3,5],[3,7],[3,8],[3,9],[3,10],[4,5],[4,6],[4,7],[4,8],[4,9],[4,10],[5,5],[5,6],[5,7],[5,8],[5,9],[6,7],[6,8],[6,9],[6,10],[7,7],[7,8],[7,9],[7,10],[8,8],[8,9],[8,10],[9,10],[10,10]]"));
    test("10203004", get_matrix_int("[[0,7],[1,3],[4,6]]"));
    test("1000", get_matrix_int("[[0,3],[1,1]]"));
    test("9876543210", get_matrix_int("[[0,9]]"));
}
}
namespace problem4 {

class Solution {
public:
    int countEffective(vector<int>& nums) {
        map<int, int> freqs;
        int total_or = 0;
        for (auto&& num : nums) {
            freqs[num]++;
            total_or |= num;
        }
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().countEffective(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"));
    test(get_list_int("[7,4,6]"));
    test(get_list_int("[8,8]"));
    test(get_list_int("[2,2,1]"));
}
}
int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}