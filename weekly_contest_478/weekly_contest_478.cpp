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

namespace problem1 {
class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        map<int, int> freq_map;
        for (auto&& num : nums) {
            freq_map[num]++;
        }
        const auto n = size(freq_map);
        vector<int> prefix_sums(n + 1);
        int index = 0;
        for (auto&& [_, freq] : freq_map) {
            prefix_sums[index + 1] = prefix_sums[index] + freq;
            index++;
        }
        const auto target = prefix_sums.back() - k;
        auto it = lower_bound(cbegin(prefix_sums), cend(prefix_sums), target);
        if (it == cbegin(prefix_sums)) {
            return 0;
        }
        if (*it == target) {
            return target;
        }
        return *prev(it);
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().countElements(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,2,2,3]"), 2);
    test(get_list_int("[3,1,2]"), 1);
    test(get_list_int("[5,5,5]"), 2);
}
}
namespace problem2 {
class Solution {
public:
    int maxDistinct(string s) {
        vector<bool> exists(26);
        for (auto&& c : s) {
            const auto index = c - 'a';
            exists[index] = true;
        }
        return static_cast<int>(count_if(cbegin(exists), cend(exists), [](bool b) { return b; }));
    }
};
static void test(string&& s) {
    cout << Solution().maxDistinct(s) << endl;
}
static void run() {
    test("abab");
    test("abcd");
    test("aaaa");
}
}
namespace problem3 {
class Solution {
public:
    long long reverse(long long num) {
        if (num == 0) { return 0; }
        int current(num);
        vector<long long> digits;
        while (current > 0) {
            digits.push_back(current % 10);
            current /= 10;
        }
        long long value = 0;
        long long base = 1;
        for (auto it = crbegin(digits); it != crend(digits); ++it) {
            value += (*it) * base;
            base *= 10;
        }
        return value;
    }

    int minMirrorPairDistance(vector<int>& nums) {
        int min_distance = INT_MAX;
        const auto n = size(nums);
        map<long long, int> rev_num_index_map;
        for (int i = 0; i < n; i++) {
            auto it = rev_num_index_map.find(nums[i]);
            if (it != cend(rev_num_index_map)) {
                min_distance = min(min_distance, i - it->second);
            }
            auto rev_val = reverse(nums[i]);
            rev_num_index_map[rev_val] = i;
        }
        if (min_distance == INT_MAX) {
            return -1;
        }
        return min_distance;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().minMirrorPairDistance(nums) << endl;
}
static void run() {
    test(get_list_int("[12,21,45,33,54]"));
    test(get_list_int("[120,21]"));
    test(get_list_int("[21,120]"));
}
}
namespace problem4 {
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

    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        const auto n = size(nums);
        const auto m = size(queries);
        vector<long long> prefix_sums_diff_modulo(n);
        for (int i = 0; i < n - 1; i++) {
            const auto diff_mod = abs(nums[i + 1] - nums[i]) % k;
            prefix_sums_diff_modulo[i + 1] = prefix_sums_diff_modulo[i] + diff_mod;
        }

        vector<long long> ans;
        ans.reserve(m);

        for (auto&& query : queries) {
            const auto l = query[0];
            const auto r = query[1];
            if (l == r) {
                ans.emplace_back(0);
            }
            else {
                if (prefix_sums_diff_modulo[r] - prefix_sums_diff_modulo[l] != 0) {
                    ans.emplace_back(-1);
                }
                else {
                    map<int, int> freq_map;
                    for (int i = l; i <= r; i++) {
                        freq_map[nums[i]]++;
                    }
                    if (size(freq_map) == 1) {
                        ans.emplace_back(0);
                    }
                    else {
                        const auto N = size(freq_map);
                        auto find_med = [&]() {
                            const auto target = (r - l + 1) / 2;
                            long long total = 0;
                            for (auto&& [num, c] : freq_map) {
                                total += c;
                                if (target < total) {
                                    return num;
                                }
                            }
                            throw runtime_error("");
                            };
                        const auto med = find_med();
                        long long cost = 0;
                        for (auto&& [num, c] : freq_map) {
                            cost += (abs(num - med) / k) * c;
                        }
                        ans.emplace_back(cost);
                    }
                }
            }
        }
        return ans;
    }
};
static void test(vector<int>&& nums, int k, vector<vector<int>>&& queries) {
    output(Solution().minOperations(nums, k, queries));
}
static void run() {
    test(get_list_int("[1,4,7]"), 3, get_matrix_int("[[0,1],[0,2]]"));
    test(get_list_int("[74422,29770,23740,84308,57718]"), 2, get_matrix_int("[[0,4],[2,3]]"));
    test(get_list_int("[1,2,4]"), 2, get_matrix_int("[[0,2],[0,0],[1,2]]"));
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