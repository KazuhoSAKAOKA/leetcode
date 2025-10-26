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
    long long removeZeros(long long n) {
        auto s = to_string(n);
        string converted;
        for (int i = 0; i < size(s); i++) {
            if (s[i] != '0') {
                converted += s[i];
            }
        }
        if (converted.empty()) {
            return 0;
        }
        return stoll(converted);
    }
}; 
static void run() {
}
}
namespace problem2 {
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        const auto n = size(nums);
        vector<long long> num2s;
        num2s.reserve(n);
        for (auto&& num : nums) { num2s.emplace_back(static_cast<long long>(num) * num); }
        sort(begin(num2s), end(num2s));
        long long total = 0;
        for (int i = 0; i < n / 2; i++) {
            total -= num2s[i];
        }
        for (int i = n / 2; i < n; i++) {
            total += num2s[i];
        }
        return total;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maxAlternatingSum(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"));
    test(get_list_int("[1,-1,2,-2,3,-3]"));
}
}
namespace problem3 {
class Solution {
public:

    static long long tle(vector<int>& capacity) {
        const auto n = size(capacity);
        vector<long long> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + static_cast<long long>(capacity[i]); }
        long long ans = 0;

        unordered_map<int, vector<int>> candidates;
        candidates[capacity[0]].emplace_back(0);
        candidates[capacity[1]].emplace_back(1);

        for (int r = 2; r < n; r++) {
            auto it = candidates.find(capacity[r]);
            if (it != cend(candidates)) {
                for (auto&& l : it->second) {
                    if (l == r - 1) {
                        break;
                    }
                    if (prefix_sums[r] - prefix_sums[l + 1] == static_cast<long long>(capacity[r])) {
                        ans++;
                    }
                }
            }
            candidates[capacity[r]].emplace_back(r);
        }

        return ans;
    }

    long long countStableSubarrays(vector<int>& capacity) {
        const auto n = size(capacity);
        vector<long long> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + static_cast<long long>(capacity[i]); }
        long long ans = 0;

        unordered_map<int, unordered_map<long long, vector<int>>> candidates;
        candidates[capacity[0]][capacity[0]].emplace_back(0);
        candidates[capacity[1]][static_cast<long long>(capacity[0]) + capacity[1]].emplace_back(1);

        for (int r = 2; r < n; r++) {
            auto it = candidates.find(capacity[r]);
            if (it != cend(candidates)) {
                const auto prev_val = prefix_sums[r];
                const auto target_val = prev_val - capacity[r];
                auto it2 = it->second.find(target_val);
                if (it2 != cend(it->second)) {
                    ans += static_cast<long long>(size(it2->second));
                    if (it2->second.back() == r - 1) {
                        ans--;
                    }
                }
            }
            candidates[capacity[r]][prefix_sums[r + 1]].emplace_back(r);
        }

        return ans;
    }
};
static void test(vector<int>&& capacity) {
    cout << Solution().countStableSubarrays(capacity) << endl;
}
static void run() {
    test(get_list_int("[9,3,3,3,9]"));
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[-4,4,0,0,-8,-4]"));
    test(get_list_int("[3,-3,3,3,-3,3,3,3]"));
}
}
namespace problem4 {
class Solution {
public:

    template <typename T>
    static T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

    template <typename T>
    static T lcm(const T& a, const T& b) {
        return a / gcd(a, b) * b;
    }

    static long long counting(const vector<int>& nums, int k, int s, int e) {
        long long ans = 0;
        unordered_map<long long, long long> prefix_map{ {0,1} };
        long long prefix_sum = 0;
        for (int l = s; l < e; l++) {
            prefix_sum += static_cast<long long>(nums[l]);
            prefix_sum %= k;
            auto it = prefix_map.find(prefix_sum);
            if (it != cend(prefix_map)) {
                ans += it->second;
            }
            prefix_map[prefix_sum]++;
        }
        return ans;
    }

    long long numGoodSubarrays(vector<int>& nums, int k) {
        const auto n = size(nums);
        long long ans = counting(nums, k, 0, n);


        auto update = [&](int v, int st, int s, int e) {
            if (st > 1) {
                const auto lcmv = lcm(static_cast<long long>(v), static_cast<long long>(k));
                const auto len = lcmv / v;
                if (len <= st) {
                    const auto temp_count = counting(nums, k, s, e);
                    ans -= temp_count;
                    ans += st / len;
                }
            }
            };

        long long streak = 0;
        int cur_val = -1;
        for (int i = 0; i < n; i++) {
            if (cur_val != nums[i]) {
                update(cur_val, streak, i - streak, i);
                cur_val = nums[i];
                streak = 1;
            }
            else {
                streak++;
            }
        }
        update(cur_val, streak, n - streak, n);
        return ans;
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().numGoodSubarrays(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"), 3);
    test(get_list_int("[2,2,2,2,2,2]"), 6);
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