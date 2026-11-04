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
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    template <typename T>
    struct median_state_t {
        size_t total = 0;
        size_t eq = 0;
        size_t gt = 0;
        map<T, size_t> freq_map;
        T median = 0;

        inline T get_median() const { return median; }
        inline size_t get_gt() const { return gt; }
        inline size_t get_eq() const { return eq; }
        inline size_t get_lt() const { return total - eq - gt; }

        void add(T v) {
            // 初回
            if (total == 0) {
                total = 1;
                freq_map.insert({ v, 1 });
                median = v;
                eq = 1;
                gt = 0;
                return;
            }
            if (v == median) {
                total++;
                eq++;
                freq_map[v]++;
                return;
            }
            total++;
            freq_map[v]++;

            if (v < median) {
                if (get_lt() <= get_gt() + get_eq()) {
                    return;
                }
                auto it = prev(freq_map.find(median));
                gt += eq;
                eq = it->second;
                median = it->first;
            }
            else {
                gt++;
                if (get_gt() < get_lt() + get_eq() ) {
                    return;
                }
                auto it = next(freq_map.find(median));
                gt -= it->second;
                eq = it->second;
                median = it->first;
            }
        }

        void remove(T v) {
            if (total == 0) {
                throw runtime_error("");
            }
            auto it = freq_map.find(v);
            if (it == cend(freq_map)) {
                throw runtime_error("");
            }

            total--;
            if (total == 0) {
                freq_map.clear();
                gt = 0;
                eq = 0;
                return;
            }
            if (it->second == 1) {
                freq_map.erase(it);
                if (v == median) {
                    auto it = freq_map.upper_bound(median);
                    if (get_lt() <= get_gt()) {
                        gt -= it->second;
                    }
                    else {
                        --it;
                    }
                    eq = it->second;
                    median = it->first;
                    return;
                }
            }
            else {
                it->second--;
            }

            if (v == median) {
                eq--;
                return;
            }
            if (v < median) {

            }
            else {
                if (v == median) {
                    eq--;
                }
            }
        }
    };

    struct median_ms {
        multiset<long long> low;   // 中央値以下（最大側が中央値）
        multiset<long long> high;  // 中央値より大きい
        long long sum_low;
        long long sum_high;
        int total = 0;

        long long get_median() const {
            return *low.rbegin();
        }

        // バランス調整：low.size() >= high.size() を維持
        void rebalance() {
            while (low.size() < high.size()) {
                auto it = begin(high);
                sum_low += *it;
                sum_high -= *it;
                low.insert(*it);
                high.erase(it);
            }
            while (low.size() > high.size() + 1) {
                auto it = prev(end(low));
                sum_low -= *it;
                sum_high += *it;
                high.insert(*it);
                low.erase(it);
            }
        }

        void add(long long v) {
            total++;

            if (low.empty() || v <= *low.rbegin()) {
                sum_low += v;
                low.insert(v);
            }
            else {
                sum_high += v;
                high.insert(v);
            }

            rebalance();
        }

        void remove(long long v) {
            if (total == 0) { return; }
            total--;

            if (!low.empty() && v <= *low.rbegin()) {
                auto it = low.find(v);
                if (it != low.end()) {
                    sum_low -= v;
                    low.erase(it);
                }
                else {
                    // high にあるはず
                    auto it2 = high.find(v);
                    if (it2 != high.end()) {
                        sum_high -= v;
                        high.erase(it2);
                    }
                }
            }
            else {
                auto it = high.find(v);
                if (it != high.end()) {
                    sum_high -= v;
                    high.erase(it);
                }
                else {
                    // low にあるはず
                    auto it2 = low.find(v);
                    if (it2 != low.end()) {
                        sum_low -= v;
                        low.erase(it2);
                    }
                }
            }

            rebalance();
        }
    };



    long long minOperations(vector<int>& nums, int x, int k) {
        const auto n = size(nums);
        constexpr long long INF = LLONG_MAX / 2;
        vector<vector<long long>> dp(n, vector<long long>(k + 1, INF));
        for (size_t i = 0; i < n; i++) { dp[i][0] = 0LL; }

        median_ms med;
        for (size_t i = 0; i < x; i++) {
            med.add(nums[i]);
        }

        auto get_val = [&](size_t count) {
            return med.sum_high - med.sum_low + med.get_median() * (static_cast<long long>(size(med.low))- static_cast<long long>(size(med.high)));
            };

        dp[x - 1][1] = get_val(x);
        for (size_t i = x; i < n; i++) {
            med.add(nums[i]);
            med.remove(nums[i - x]);
            const auto cur_val = get_val(i + 1);
            for (size_t j = 0; j < k; j++) {
                dp[i][j + 1] = min(dp[i - 1][j + 1], dp[i - x][j] + cur_val);
            }
        }
        return dp[n - 1][k];
    }
};
static void test(vector<int>&& nums, int x, int k) {
	cout << Solution().minOperations(nums, x, k) << endl;
}
static void run() {
    test(get_list_int("[1,1,2,2]"), 2, 2);
    test(get_list_int("[5,-2,1,3,7,3,6,4,-1]"), 3, 2);
    test(get_list_int("[9,-2,-2,-2,1,5]"), 2, 2);
}

int main() {
	run();
	return 0;
}
