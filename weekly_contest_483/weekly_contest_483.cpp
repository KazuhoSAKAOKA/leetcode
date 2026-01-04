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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    string largestEven(string s) {
        while (!s.empty() && s.back() != '2') {
            s.pop_back();
        }
        return s;
    }
};
static void test(string&& s) {
    cout << Solution().largestEven(s) << endl;
}

static void run() {
    test("1112");
    test("221");
    test("1");
}
}

namespace problem2 {
class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        const auto n = size(words);
        map<char, vector<string>> first_char_map;
        map<pair<char,char>, vector<string>> both_char_map;
        for (auto&& word : words) {
            first_char_map[word[0]].emplace_back(word);
            both_char_map[{word[0], word[3]}].emplace_back(word);
        }
        auto get_candidate_from_first = [&](char c)->vector<string> {
            return first_char_map[c];
            };

        vector<vector<string>> ans;
        for (auto&& top: words) {
            const vector<string>& left_candidates = first_char_map[top[0]];
            const vector<string>& right_candidates = first_char_map[top[3]];

            for (auto&& left : left_candidates) {
                if (left == top) { continue; }
                for (auto&& right : right_candidates) {
                    if (right == top) { continue; }
                    if (right == left) { continue; }
                    const vector<string>& bottom_candidates = both_char_map[{left[3], right[3]}];
                    for (auto&& bottom : bottom_candidates) {
                        if (bottom == top) { continue; }
                        if (bottom == left) { continue; }
                        if (bottom == right) { continue; }
                        ans.emplace_back(vector<string>{top, left, right, bottom});
                    }
                }
            }
        }
        sort(begin(ans), end(ans));
        return ans;
    }
};
static void test(vector<string>&& words) {
    output_matrix(Solution().wordSquares(words));
}
static void run() {
    test(get_list_str(R"(["able","area","echo","also"])"));
    test(get_list_str(R"(["code","cafe","eden","edge"])"));
}
}

namespace problem3 {
class Solution {
public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
        const auto n = size(s);
        long long s_ones = 0;
        long long t_ones = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                if (s[i] == '1') {
                    s_ones++;
                }
                else {
                    t_ones++;
                }
            }
        }

        long long min_cost = (s_ones + t_ones) * flipCost;

        const auto min_ones = min(s_ones, t_ones);
        const auto max_ones = max(s_ones, t_ones);
        const auto diff = max_ones - min_ones;
        for (long long i = 0; ; i++) {
            const auto cur_min = min_ones + i;
            const auto cur_max = max_ones - i;
            if (cur_max < cur_min) { break; }
            const long long cost1 = i * crossCost + cur_min * swapCost + (cur_max - cur_min) * flipCost;
            min_cost = min(min_cost, cost1);
        }
        return min_cost;
    }
};

static void test(string&& s, string&& t, int flipCost, int swapCost, int crossCost) {
    cout << Solution().minimumCost(s, t, flipCost, swapCost, crossCost) << endl;
}
static void run() {
    test("01000", "10111", 10, 2, 2);
    test("001", "110", 2, 100, 100);
    test("1010", "1010", 5, 5, 5);
}
}

namespace problem4 {
class Solution {
public:
    //static long long get_median(const vector<int>& list);

    //static long long greedy_naive(vector<vector<int>>& lists) {
    //    const auto n = size(lists);
    //    if (n == 1) {
    //        return 0LL;
    //    }

    //    long long min_diff = LLONG_MAX;
    //    int selectedi = -1;
    //    int selectedj = -1;
    //    for (int i = 0; i < n; i++) {
    //        const auto meda = get_median(lists[i]);
    //        for (int j = i + 1; j < n; j++) {
    //            const auto medb = get_median(lists[j]);
    //            const auto cur_diff = abs(meda - medb);
    //            if (cur_diff < min_diff) {
    //                min_diff = cur_diff;
    //                selectedi = i;
    //                selectedj = j;
    //            }
    //        }
    //    }
    //    vector<vector<int>> new_lists;
    //    new_lists.reserve(n - 1);
    //    for (int i = 0; i < n; i++) {
    //        if (i == selectedi || i == selectedj) { continue; }
    //        new_lists.emplace_back(lists[i]);
    //    }

    //    vector<int> combine_list;
    //    int index1 = 0;
    //    int index2 = 0;
    //    while (index1 < size(lists[selectedi]) || index2 < size(lists[selectedj])) {
    //        if (index1 < size(lists[selectedi]) && index2 < size(lists[selectedj])) {
    //            if (lists[selectedi][index1] < lists[selectedj][index2]) {
    //                combine_list.emplace_back(lists[selectedi][index1++]);
    //            }
    //            else {
    //                combine_list.emplace_back(lists[selectedj][index2++]);
    //            }
    //        }
    //        else {
    //            if (index1 < size(lists[selectedi])) {
    //                combine_list.emplace_back(lists[selectedi][index1++]);
    //            }
    //            else {
    //                combine_list.emplace_back(lists[selectedj][index2++]);
    //            }
    //        }
    //    }
    //    new_lists.emplace_back(combine_list);
    //    return greedy_naive(new_lists) + static_cast<long long>(size(combine_list)) + min_diff;



    //}

    //static long long naive(vector<vector<int>>& lists) {
    //    const auto n = size(lists);
    //    if (n == 1) {
    //        return 0LL;
    //    }

    //    long long min_cost = LLONG_MAX;

    //    for (int i = 0; i < n; i++) {
    //        const auto meda = get_median(lists[i]);
    //        for (int j = i + 1; j < n; j++) {
    //            const auto medb = get_median(lists[j]);

    //            vector<vector<int>> new_lists;
    //            new_lists.reserve(n - 1);
    //            for (int k = 0; k < n; k++) {
    //                if (k == i || k == j) { continue; }
    //                new_lists.emplace_back(lists[k]);
    //            }

    //            vector<int> combine_list;
    //            combine_list.reserve(size(lists[i]) + size(lists[j]));
    //            int index1 = 0;
    //            int index2 = 0;
    //            while (index1 < size(lists[i]) || index2 < size(lists[j])) {
    //                if (index1 < size(lists[i]) && index2 < size(lists[j])) {
    //                    if (lists[i][index1] < lists[j][index2]) {
    //                        combine_list.emplace_back(lists[i][index1++]);
    //                    }
    //                    else {
    //                        combine_list.emplace_back(lists[j][index2++]);
    //                    }
    //                }
    //                else {
    //                    if (index1 < size(lists[i])) {
    //                        combine_list.emplace_back(lists[i][index1++]);
    //                    }
    //                    else {
    //                        combine_list.emplace_back(lists[j][index2++]);
    //                    }
    //                }
    //            }
    //            new_lists.emplace_back(combine_list);
    //            const long long cur_cost = size(lists[i]) + size(lists[j]) + abs(meda - medb);
    //            const auto temp = naive(new_lists) + cur_cost;
    //            min_cost = min(min_cost, temp);
    //        }
    //    }

    //    return min_cost;
    //}
    static long long get_median(const vector<int>& list) {
        if (size(list) % 2 == 0) {
            return list[(size(list) / 2) - 1];
        }
        else {
            return list[size(list) / 2];
        }
    }
    long long minMergeCost(vector<vector<int>>& lists) {
        const auto n = size(lists);
        if (n == 1) {
            return 0LL;
        }
        const unsigned int bitmasks = 1 << n;
        vector<vector<int>> combined_list(bitmasks);
        vector<long long> medians(bitmasks, -1);
        vector<long long> lens(bitmasks, 0);
        constexpr long long INF = LLONG_MAX / 3;
        vector<long long> dp(bitmasks, INF);
        for (int i = 0; i < n; i++) {
            const auto bit = 1 << i;
            combined_list[bit] = lists[i];
            medians[bit] = get_median(lists[i]);
            lens[bit] = size(lists[i]);
            dp[bit] = 0LL;
        }

        for (unsigned int bit = 1; bit < bitmasks; bit++) {
            if (has_single_bit(bit)) {
                continue;
            }

            if (medians[bit] < 0) {
                unsigned int lsb = bit & (~bit + 1);
                unsigned int prev = bit ^ lsb;
                auto& cur_list = combined_list[bit];
                merge(cbegin(combined_list[lsb]), cend(combined_list[lsb]), cbegin(combined_list[prev]), cend(combined_list[prev]), back_inserter(cur_list));
                medians[bit] = get_median(cur_list);
                lens[bit] = size(cur_list);
            }
            for (unsigned int s = (bit - 1) & bit; s > 0; s = (s - 1) & bit) {
                unsigned int t = bit ^ s;  // 残りの部分集合
                if (t == 0) { continue; }
                dp[bit] = min(dp[bit], dp[s] + dp[t] + lens[s] + lens[t] + abs(medians[s] - medians[t]));
            }
        }
        return dp[bitmasks - 1];
    }
};
static void test(vector<vector<int>>&& lists) {
    cout << Solution().minMergeCost(lists) << endl;
}

static void run() {
    test(get_matrix_int("[[1,3,5],[2,4],[6,7,8]]"));
    test(get_matrix_int("[[1,1,5],[1,4,7,8]]"));
    test(get_matrix_int("[[1],[3]]"));
    test(get_matrix_int("[[1],[1]]"));
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