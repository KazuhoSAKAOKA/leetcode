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
    int missingMultiple(vector<int>& nums, int k) {
        set<int> exists(cbegin(nums), cend(nums));
        int index = 1;
        for (;;) {
            if (exists.count(k * index) == 0) {
                return k * index;
            }
            index++;
        }
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().missingMultiple(nums, k) << endl;
}

static void run() {
    test(get_list_int("[8,2,3,4,6]"), 2);
    test(get_list_int("[1,4,7,10,15]"), 5);
}
}
namespace problem2 {
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        const auto n = size(nums);

        int longest_len = 0;
        for (int l = 0; l < n; l++) {
            set<int> evens;
            set<int> odds;
            if (nums[l] % 2 == 0) {
                evens.insert(nums[l]);
            }
            else {
                odds.insert(nums[l]);
            }
            for (int r = l + 1; r < n; r++) {
                if (nums[r] % 2 == 0) {
                    evens.insert(nums[r]);
                }
                else {
                    odds.insert(nums[r]);
                }
                if (size(evens) == size(odds)) {
                    longest_len = max(longest_len, r - l + 1);
                }
            }
        }
        return longest_len;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().longestBalanced(nums) << endl;
}
static void run() {
    test(get_list_int("[2,5,4,3]"));


    test(get_list_int("[6,6]"));
    test(get_list_int("[1,2,3,2]"));
    test(get_list_int("[3,2,2,5,4]"));
}
}
namespace problem3 {
class Solution {
public:
    static string tle(string&& s, string&& target) {
        sort(begin(s), end(s));
        do {
            if (target < s) {
                return s;
            }
        } while (next_permutation(begin(s), end(s)));
        return "";
    }

    static optional<string> bt(const string& target, int index, const vector<int>& freqs, vector<int>& used, string& current, bool cur_equals) {
        if (size(target) == index) {
            if (cur_equals) { return nullopt; }
            return current;
        }
        if (cur_equals) {
            const auto start_index = target[index] - 'a';
            for (int i = start_index; i < 26; i++) {
                if (freqs[i] - used[i] > 0) {
                    used[i]++;
                    current.push_back(i + 'a');
                    auto opt_ret = bt(target, index + 1, freqs, used, current, i == start_index);
                    if (opt_ret.has_value()) {
                        return opt_ret.value();
                    }
                    current.pop_back();
                    used[i]--;
                }
            }
            return nullopt;
        }
        else {
            const auto start_index = 0;
            for (int i = start_index; i < 26; i++) {
                if (freqs[i] - used[i] > 0) {
                    used[i]++;
                    current.push_back(i + 'a');
                    auto opt_ret = bt(target, index + 1, freqs, used, current, false);
                    if (opt_ret.has_value()) {
                        return opt_ret.value();
                    }
                    current.pop_back();
                    used[i]--;
                }
            }
            return nullopt;
        }
    }

    string lexGreaterPermutation(string s, string target) {
        const auto n = size(s);
        vector<int> freqs(26);
        for (auto&& c : s) { freqs[c - 'a']++; }
        vector<int> used(26);
        string work;
        auto ans_opt = bt(target, 0, freqs, used, work, true);
        if (ans_opt.has_value()) { return ans_opt.value(); }
        return "";
    }
};
static void test(string&& s, string&& target) {
    cout << Solution().lexGreaterPermutation(s, target) << endl;
}
static void run() {
    test("abc", "bba");
    test("leet", "code");
    test("baba", "bbaa");
    test("ababababababababababababababababababababababababab", "bababababababababababababababababababababababababa");
}
}
namespace problem4 {
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        const auto n = size(nums);
        int longest_len = 0;

        int l_exp = 0;
        int l_she = 0;
        map<int, int> even_exp_nums;
        map<int, int> odd_exp_nums;
        map<int, int> even_shr_nums;
        map<int, int> odd_shr_nums;
        for (int r = 0; r < n; r++) {
            if (nums[r] % 2 == 0) {
                even_exp_nums[nums[r]]++;
                even_shr_nums[nums[r]]++;
            }
            else {
                odd_exp_nums[nums[r]]++;
                odd_shr_nums[nums[r]]++;
            }
            while (l_exp > 0 && size(even_exp_nums) != size(odd_exp_nums)) {

            }

            if (size(even_nums) == size(odd_nums)) {
                longest_len = max(longest_len, r + 1);
            }
            else {

            }

        }

        return longest_len;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().longestBalanced(nums) << endl;
}
static void run() {
    test(get_list_int("[2,5,4,3]"));
    test(get_list_int("[3,2,2,5,4]"));
    test(get_list_int("[1,2,3,2]"));
    test(get_list_int("[6,6]"));
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

/*
        int longest_len = 0;

        int l1 = 0;
        int l2 = 0;
        set<int> even_nums;
        set<int> odd_nums;
        for (int r = 0; r < size(nums); r++) {
            if (nums[r] % 2 == 0) {
                even_nums.insert(nums[r]);
            }
            else {
                odd_nums.insert(nums[r]);
            }






        }



        return longest_len;



                const auto n = size(nums);
        vector<int> even_sums(n + 1);
        vector<int> odd_sums(n + 1);
        set<int> evens;
        set<int> odds;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 0) {
                evens.insert(nums[i]);
            }
            else {
                odds.insert(nums[i]);
            }
            even_sums[i + 1] = static_cast<int>(size(evens));
            odd_sums[i + 1] = static_cast<int>(size(odds));
        }


        int longest_len = 0;
        for (int l = 0; l < size(nums); l++) {
            for (int r = l + 1; r <= size(nums); r++) {
                const auto even_count = even_sums[r] - even_sums[l];
                const auto odd_count = odd_sums[r] - odd_sums[l];
                if (even_count == odd_count) {
                    longest_len = max(longest_len, r - l);
                }
            }
        }
        return longest_len;

*/