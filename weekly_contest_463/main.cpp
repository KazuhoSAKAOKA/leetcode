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
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        const auto n = size(prices);
        vector<long long> prefix_sums(n + 1);
        vector<long long> sell_prefix_sums(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] += prefix_sums[i] + static_cast<long long>(prices[i]) * static_cast<long long>(strategy[i]);
            sell_prefix_sums[i + 1] += sell_prefix_sums[i] + static_cast<long long>(prices[i]);
        }
        long long max_prof = prefix_sums.back();

        for (int i = 0; i + k <= n; i++) {
            const long long part1 = prefix_sums[i] - prefix_sums[0];
            const long long part2 = sell_prefix_sums[i + k] - sell_prefix_sums[i + k / 2];
            const long long part3 = prefix_sums[n] - prefix_sums[i + k];
            const long long cur_prof = part1 + part2 + part3;
            max_prof = max(max_prof, cur_prof);
        }

        return max_prof;
    }
};
static void   test(vector<int>&& prices, vector<int>&& strategy, int k) {
    cout << Solution().maxProfit(prices, strategy, k) << endl;
}
static void run() {
    test(get_list_int("[4,2,8]"), get_list_int("[-1,0,1]"), 2);
    test(get_list_int("[5,4,3]"), get_list_int("[1,1,0]"), 2);
}
}
namespace problem2 {
class Solution {
public:

    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(nums);
        const auto q = size(queries);
        for (auto&& query : queries) {
            const auto l = query[0];
            const auto r = query[1];
            const auto k = query[2];
            const auto v = query[3];
            auto idx = l;
            while (idx <= r) {
                const long long temp = static_cast<long long>(nums[idx]) * static_cast<long long>(v);
                nums[idx] = static_cast<int>(temp % MODULO);
                idx += k;
            }
        }
        int x = 0;
        for (auto&& num : nums) {
            cout << num << " ";
            x ^= num;
        }
        cout << endl;
        return x;
    }
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().xorAfterQueries(nums, queries) << endl;
}
static void run() {
    test(get_list_int("[798,364,542,363]"), get_matrix_int("[[0,3,2,18],[2,2,1,16],[1,3,1,18],[2,2,4,3],[1,2,2,10],[0,2,4,6],[2,3,1,3],[2,3,2,19],[3,3,4,15],[3,3,3,16],[0,2,3,2],[0,1,3,18],[1,2,3,12],[1,3,1,3],[3,3,4,5],[3,3,1,8],[3,3,3,12]]"));
    //test(get_list_int("[1,1,1]"), get_matrix_int("[[0,2,1,4]]"));
    //test(get_list_int("[2,3,1,5,4]"), get_matrix_int("[[1,4,2,3],[0,2,1,2]]"));
}
}
namespace problem3 {
class Solution {
public:
    long long minArraySum(vector<int>& nums, int k) {
        const auto n = size(nums);
        unordered_map<int, int> remainder{ {0,0} };
        int current_sum = 0;
        vector<long long> dp(n + 1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            current_sum = (current_sum + nums[i]) % k;
            auto it = remainder.find(current_sum);
            if (it == cend(remainder)) {
                dp[i + 1] = nums[i] + dp[i];
                remainder.insert({ current_sum, i + 1 });
            }
            else {
                dp[i + 1] = min(nums[i] + dp[i], dp[it->second]);
                it->second = i + 1;
            }
        }
        return dp[n];
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().minArraySum(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,1,1]"), 2);
    test(get_list_int("[58,68,57,71,52,6,40,22,13,29,26,17,47,31,51,73,59,69,37,14]"), 34);
    test(get_list_int("[3,1,4,1,5]"), 3);
}
}
namespace problem4 {
class Solution {
public:


    long long pow_mod(long long base, long long e, long long modulo) {
        long long r = 1;
        while (e > 0) {
            if (e & 1) { r = (r * base) % modulo; }
            base = (base * base) % modulo;
            e >>= 1;
        }
        return r;
    }

    long long modinv(long long a, long long modulo) {
        long long b = modulo, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        u %= modulo;
        if (u < 0) u += modulo;
        return u;
    }

    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(nums);
        const auto q = size(queries);
        const auto B = static_cast<size_t>(sqrt(n));
        vector<vector<tuple<int, int, int, int>>> buckets(B + 1);

        for (auto&& query : queries) {
            const auto l = query[0];
            const auto r = query[1];
            const auto k = query[2];
            const auto v = query[3];
            if (k <= B) {
                buckets[k].emplace_back(make_tuple(l, r, k, v));
            }
            else {
                auto idx = l;
                while (idx <= r) {
                    const long long temp = static_cast<long long>(nums[idx]) * static_cast<long long>(v);
                    nums[idx] = static_cast<int>(temp % MODULO);
                    idx += k;
                }
            }
        }
        for (int k = 0; k <= B; k++) {
            if (buckets[k].empty()) { continue; }
            
            //offset, diff;
            using MULLISTS = vector<long long>;
            unordered_map<int, MULLISTS> mp;
            const auto len = (n + k - 1) / k + 2;

            for (auto&& vals : buckets[k]) {
                const auto& [l, r, _, v] = vals;
                const auto offset = l % k;
                auto get_diff_list = [&]()->MULLISTS& {
                    auto it = mp.find(offset);
                    if (it == end(mp)) {
                        auto [new_it, _] = mp.insert({ offset, vector<long long>(len,1) });
                        return new_it->second;
                    }
                    else {
                        return it->second;
                    }};
                auto& lists = get_diff_list();
                const auto s = (l - offset) / k;
                const auto e = (r - offset) / k + 1;
                lists[s] *= v;
                lists[s] %= MODULO;
                lists[e] *= modinv(v, MODULO);
                lists[e] %= MODULO;
            }

            for (auto&& [offset, lists] : mp) {
                long long current = 1LL;
                int index = 0;
                for (int i = offset; i < n; i += k) {
                    current *= lists[index++];
                    current %= MODULO;
                    nums[i] = static_cast<int>((static_cast<long long>(nums[i]) * current) % MODULO);
                }
            }
        }
        int x = 0;
        for (auto&& num : nums) {
            cout << num << " ";
            x ^= num;
        }
        cout << endl;

        return x;
    }
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().xorAfterQueries(nums, queries) << endl;
}
static void run() {
    test(get_list_int("[798,364,542,363]"), get_matrix_int("[[0,3,2,18],[2,2,1,16],[1,3,1,18],[2,2,4,3],[1,2,2,10],[0,2,4,6],[2,3,1,3],[2,3,2,19],[3,3,4,15],[3,3,3,16],[0,2,3,2],[0,1,3,18],[1,2,3,12],[1,3,1,3],[3,3,4,5],[3,3,1,8],[3,3,3,12]]"));
    //test(get_list_int("[2,3,1,5,4]"), get_matrix_int("[[1,4,2,3],[0,2,1,2]]"));
    //test(get_list_int("[1,1,1]"), get_matrix_int("[[0,2,1,4]]"));
}

}
int main()
{
    //problem1::run();
    problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}