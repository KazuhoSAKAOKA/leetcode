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
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        sort(begin(nums), end(nums));
        int index = 0;
        for (int i = nums.front(); i <= nums.back(); i++) {
            if (nums[index] == i) {
                index++;
            }
            else {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};
static void test(vector<int>&& nums) {
    output(Solution().findMissingElements(nums));
}

static void run() {
    test(get_list_int("[1,4,2,5]"));
    test(get_list_int("[7,8,6,9]"));
    test(get_list_int("[5,1]"));
}
}
namespace problem2 {
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        constexpr long long REPLACE_VAL = 1e5;
        long long max_abs_val = 0LL;
        long long max2_abs_val = 0LL;
        for (auto&& num1 : nums) {
            const long long num = abs(num1);
            if (max_abs_val < num) {
                max2_abs_val = max_abs_val;
                max_abs_val = num;
            }
            else if (max2_abs_val < num) {
                max2_abs_val = num;
            }
        }
        return REPLACE_VAL * max_abs_val * max2_abs_val;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maxProduct(nums) << endl;
}
static void run() {
    test(get_list_int("[-5,7,0]"));
    test(get_list_int("[-4,-2,-1,-3]"));
    test(get_list_int("[0,10,0]"));
}
}
namespace problem3 {
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
    
    static tuple<long long, long long, long long> get_commond1d2s(long long m, long long span, long long r1, long long r2) {
        const auto open1 = m / r1 + m % r1;
        const auto open2 = m / r2 + m % r2;
        const auto total_open = open1 + open2;
        const auto oplen = m % span == 0 ? m - 1 : m;
        const long long commons = (open1 + open2) - oplen;
        const auto only1 = max(0LL, open1 - commons);
        const auto only2 = max(0LL, open1 - commons);
        return { commons, only1, only2 };
    }

    long long minimumTime(vector<int>& d, vector<int>& r) {
        const long long d1 = static_cast<long long>(d[0]);
        const long long d2 = static_cast<long long>(d[1]);
        const long long r1 = static_cast<long long>(r[0]);
        const long long r2 = static_cast<long long>(r[1]);
        if (r[0] == r[1]) {
            const long long span_time = static_cast<long long>(r[0]);
            const long long total = static_cast<long long>(d[0]) + static_cast<long long>(d[1]);
            const long long span_count = total / static_cast<long long>(span_time - 1);
            const long long base_time = span_count * span_time;
            if (total == span_count * (span_time - 1)) {
                return base_time - 1;
            }
            const auto amari = total % span_count;
            return base_time * amari;
        }
        
        const long long span = lcm<long long>(r[0], r[1]);
        const long long can_deliverys_d1 = span - (span / r[0]);
        const long long can_deliverys_d2 = span - (span / r[1]);
        const long long common_deliverys = (can_deliverys_d1 + can_deliverys_d2) - (span - 1);
        const long long only_can_deliverys_d1 = can_deliverys_d1 - common_deliverys;
        const long long only_can_deliverys_d2 = can_deliverys_d2 - common_deliverys;
        const long long d1_only_count = only_can_deliverys_d1 > 0 ? static_cast<long long>(r[0]) / only_can_deliverys_d1 : LLONG_MAX;
        const long long d2_only_count = only_can_deliverys_d2 > 0 ? static_cast<long long>(r[1]) / only_can_deliverys_d2 : LLONG_MAX;

        const long long ok = (d1 / (r1 - 1)) * r1 + (d2 / (r2 - 1)) * r2 + (d1 % (r1 - 1)) + (d2 % (r2 - 1));
        const auto ans = binary_search_meguru<long long>(ok, 0,
            [&](long long time)->bool {
                const long long span_count = time / span;
                const long long d1_comps = span_count * only_can_deliverys_d1;
                const long long d2_comps = span_count * only_can_deliverys_d2;
                long long remaind1 = d1 - d1_comps;
                long long remaind2 = d2 - d2_comps;
                long long commons = common_deliverys * span_count;
                if (time % span != 0) {
                    const long long m = time % span;
                    const auto [commons1, only1, only2] = get_commond1d2s(m, span, r1, r2);
                    commons += commons1;
                    remaind1 -= only1;
                    remaind2 -= only2;
                    remaind1 = max(0LL, remaind1);
                    remaind2 = max(0LL, remaind2);
                }
                return (remaind1 + remaind2) <= commons;
            });
        return ans;
    }
};
static void test(vector<int>&& d, vector<int>&& r) {
    cout << Solution().minimumTime(d, r) << endl;
}
static void run() {
    test(get_list_int("[2,1]"), get_list_int("[3,4]"));

    test(get_list_int("[1,1]"), get_list_int("[3,4]"));
    test(get_list_int("[3,1]"), get_list_int("[2,3]"));
    test(get_list_int("[1,3]"), get_list_int("[2,2]"));
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