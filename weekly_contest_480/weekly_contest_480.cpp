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
    int absDifference(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        const auto min_k = accumulate(cbegin(nums), next(cbegin(nums), k), 0);
        const auto max_k = accumulate(next(cbegin(nums), size(nums) - k), cend(nums), 0);
        return max_k - min_k;
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().absDifference(nums, k) << endl;
}
static void run() {
    test(get_list_int("[5,2,2,4]"), 2);
    test(get_list_int("[100]"), 1);
}
}

namespace problem2 {
class Solution {
public:
    static size_t next_word(const string& s, size_t index) {
        if (size(s) <= index) {
            return 0;
        }
        auto pos = s.find(' ', index);
        if (pos == string::npos) {
            return size(s) - index;
        }
        return pos - index;
    }

    static int counting_vowels(const string& s, size_t index, size_t len) {
        return count_if(next(cbegin(s), index), next(cbegin(s), index + len), [](char c) {
            return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o';
            });
    }

    static void reverse_ss(string& s, size_t index, size_t len) {
        for (int i = 0; i < len / 2; i++) {
            swap(s[index + i], s[index + len - i - 1]);
        }
    }

    string reverseWords(string s) {
        size_t index = 0;
        const auto first_len = next_word(s, index);
        const auto first_vowels = counting_vowels(s, 0, first_len);
        index = first_len + 1;

        for (;;) {
            const auto cur_len = next_word(s, index);
            if (cur_len == 0) {
                break;
            }
            const auto cur_vowels = counting_vowels(s, index, cur_len);
            if (cur_vowels == first_vowels) {
                reverse_ss(s, index, cur_len);
            }

            index += cur_len + 1;
        }

        return s;
    }
};
static void test(string&& s) {
    cout << Solution().reverseWords(s) << endl;
}
static void run() {
    test("cat and mice");
    test("book is nice");
    test("banana healthy");
}
}

namespace problem3 {
class Solution {
public:
    long long minMoves(vector<int>& balance) {
        const auto sum = accumulate(cbegin(balance), cend(balance), 0LL, [](long long t, int a) { return t + static_cast<long long>(a); });
        if (sum < 0) { return -1; }
        const int n = static_cast<int>(size(balance));
        vector<int> positive_indexes;
        positive_indexes.reserve(n);
        set<int> negatives;
        for (int i = 0; i < n; i++) {
            if (balance[i] < 0) {
                negatives.insert(i);
            }
            else {
                positive_indexes.emplace_back(i);
            }
        }
        const auto min_negative = *cbegin(negatives);
        const auto max_negative = *crbegin(negatives);
        auto get_distance = [&](int a)->int {
            int min_dist = INT_MAX;
            auto it = negatives.upper_bound(a);
            if (it != cend(negatives)) {
                min_dist = min(min_dist, *it - a);
            }
            else {
                min_dist = min(min_dist, n - a + min_negative);
            }
            if (it != cbegin(negatives)) {
                auto it1 = prev(it);
                min_dist = min(min_dist, a - *it1);
            }
            else {
                min_dist = min(min_dist, a + n - max_negative);
            }
            };
        vector<int> distances(n);
        for (auto&& index : positive_indexes) {
            distances[index] = get_distance(index);
        }

        sort(begin(positive_indexes), end(positive_indexes), [&](int a, int b) { return distances[a] < distances[b]; });
    }
};
static void test(vector<int>&& balance) {
    cout << Solution().minMoves(balance) << endl;
}
static void run() {
    test(get_list_int("[5,1,-4]"));
    test(get_list_int("[1,2,-5,2]"));
    test(get_list_int("[-3,2]"));
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