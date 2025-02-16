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
    bool hasSpecialSubstring(string s, int k) {
        int streak = 0;
        char cur = 0;

        for (auto&& c : s) {
            if (cur != c) {
                if (streak == k) {
                    return true;
                }
                streak = 1;
                cur = c;
            }
            else {
                streak++;
            }
        }
        return false;
    }
};

static void test(string&& s, int k) {
    cout << Solution().hasSpecialSubstring(s, k) << endl;
}
static void run() {
    test("aaabaaa", 3);
    test("abc", 2);
}
}
namespace problem2 {
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        sort(begin(pizzas), end(pizzas), [](auto a, auto b) {return a > b; });
        const int days = size(pizzas) / 4;
        const int odd_days = days / 2 + days % 2;
        const int even_days = days - odd_days;
        long long weights = 0LL;
        for (int i = 0; i < odd_days; i++) {
            weights += static_cast<long long>(pizzas[i]);
        }
        int index = odd_days;
        for (int i = 0; i < even_days; i++) {
            weights += static_cast<long long>(pizzas[index + 1]);
            index += 2;
        }
        return weights;
    }
};
void test(vector<int>&& pizzas) {
    cout << Solution().maxWeight(pizzas) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4,5,6,7,8]"));
    test(get_list_int("[2,1,1,1,1,1,1,1]"));
}
}
namespace problem3 {
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        if (k == 0) { return true; }
        const auto N = size(s);
        vector<vector<int>> prefix_sumss(26, vector<int>(N + 1));

        vector<int> first_appears(26, INT_MAX);
        vector<int> last_appears(26, -1);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 26; j++) {
                prefix_sumss[j][i + 1] = prefix_sumss[j][i];
            }
            const auto index = s[i] - 'a';
            prefix_sumss[index][i + 1]++;
            first_appears[index] = min(first_appears[index], i);
            last_appears[index] = i;
        }

        map<int, vector<int>> range_map;
        for (int i = 0; i < 26; i++) {
            if (first_appears[i] < N) {
                range_map[last_appears[i] - first_appears[i] + 1].emplace_back(i);
            }
        }

        vector<bool> used(26);

        auto get_range_freqs = [&](int range_begin, int range_end)->pair<bool, vector<int>> {
            int range_begin1 = range_begin;
            int range_end1 = range_end;
            for (;;) {
                int range_begin_w = range_begin1;
                int range_end_w = range_end1;
                for (int i = 0; i < 26; i++) {
                    if (prefix_sumss[i][range_end1 + 1] - prefix_sumss[i][range_begin1] > 0) {
                        range_begin_w = min(range_begin_w, first_appears[i]);
                        range_end_w = max(range_end_w, last_appears[i]);
                        if (used[i]) {
                            return { false,{} };
                        }
                    }
                }
                if (range_begin_w == range_begin1 && range_end_w == range_end1) {
                    break;
                }
                range_begin1 = range_begin_w;
                range_end1 = range_end_w;
            }
            if (range_begin1 == 0 && range_end1 == N - 1) {
                return { false,{} };
            }
            vector<int> freqs(26);
            for (int i = 0; i < 26; i++) {
                freqs[i] = prefix_sumss[i][range_end1 + 1] - prefix_sumss[i][range_begin1];
            }
            return { true, freqs };
            };

        int current_count = 0;
        auto check_allow = [&](const vector<int> freqs) {
            for (int i = 0; i < 26; i++) {
                if (freqs[i] > 0) {
                    if (used[i]) { return false; }
                    if (freqs[i] != prefix_sumss[i].back()) { return false; }
                }
            }
            return true;
            };

        for (auto&& [count, list] : range_map) {
            if (count == 0) {
                for (auto&& target : list) {
                    current_count++;
                    used[target] = true;
                }
            }
            else {
                for (auto&& target : list) {
                    if (used[target]) { continue; }
                    const auto [ret, range_freq] = get_range_freqs(first_appears[target], last_appears[target]);
                    if (ret && check_allow(range_freq)) {
                        current_count++;
                        for (int i = 0; i < 26; i++) {
                            if (range_freq[i] > 0) {
                                used[target] = true;
                            }
                        }
                    }
                }
            }
            if (k <= current_count) {
                return true;
            }
        }
        return false;
    }
};
void test(string&& s, int k) {
    cout << Solution().maxSubstringLength(s, k) << endl;
}

static void run() {
    test("nbuirvanjiccnsyyyoirleqsrwrvxepaglcidqplyryujytzqoncxjgwdmatytgwhzyhlsodrbzrpbbitovtdasazjtoyyfhowqqrzuvjveydceouscrfazzoblqhalhfybwheybkpcroijxvarrtqrqnmwslkpdducfeblvfecyjyulxgahxlzlyztssfzwvfujrriryslkvdwhmkcyebfhkadrahunvxivkwitilyzknwyujtylahgmlddymlbrbrniomepbmdieasuvdcqnzfwspxewbbpruxrznjxwnjjxvblxyrgv", 1);

    test("abcdbaefab", 2);
    test("cdefdc", 3);
    test("abeabe", 0);
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