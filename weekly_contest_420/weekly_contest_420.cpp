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
    vector<string> stringSequence(string target) {
        vector<string> ans;
        string current = "";
        for (auto&& c : target) {
            current += 'a';
            ans.emplace_back(current);
            while (c != current.back()) {
                current.back() = current.back() + static_cast<char>(1);
                ans.emplace_back(current);
            }
        }
        return ans;
    }
};

void test(string&& target) {
    output(Solution().stringSequence(target));
}

void run() {
    test("abc");
    test("he");
}
}
namespace problem2 {
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        vector<int> freq_count(26, 0);

        int count = 0;
        int current_multiples = 0;
        int r = 0;
        int l = 0;
        for (; r < size(s); r++) {
            const size_t index = static_cast<size_t>(s[r] - 'a');
            freq_count[index]++;
            if (freq_count[index] == k) {
                current_multiples++;
            }

            if (current_multiples > 0) {
                while (l < r) {
                    const size_t index_l = static_cast<size_t>(s[l] - 'a');
                    if (freq_count[index_l] == k) {
                        if (current_multiples == 1) {
                            break;
                        }
                        current_multiples--;
                    }
                    freq_count[index_l]--;
                    l++;
                }
            }

            if (current_multiples > 0) {
                count += l + 1;
            }
        }
        return count;
    }
};
void test(string&& s, int k) {
    cout << Solution().numberOfSubstrings(s, k) << endl;
}
void run() {
    test("abacb", 2);
    test("abcde", 1);
}
}
namespace problem3 {
class Solution {
public:

    static optional<int> get_proper_divisor(int n, unordered_map<int, optional<int>>& memo) {
        auto it = memo.find(n);
        if (it != cend(memo)) {
            return it->second;
        }
        int limit = sqrt(n);
        for (int i = 2; i <= limit; i++) {
            if ((n % i) == 0) {
                memo.insert({ n, n / i });
                return n / i;
            }
        }
        memo.insert({ n, nullopt });
        return nullopt;
    }

    int minOperations(vector<int>& nums) {
        unordered_map<int, optional<int>> memo;
        int op_count = 0;

        for (int i = size(nums) - 2; i >= 0; i--) {
            while (nums[i] > nums[i + 1]) {
                auto proper_divisor = get_proper_divisor(nums[i], memo);
                if (!proper_divisor.has_value()) {
                    return -1;
                }
                nums[i] = nums[i] / proper_divisor.value();
                op_count++;
            }
        }

        return op_count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minOperations(nums) << endl;
}

void run() {
    test(get_list_int("[105,11]"));
    test(get_list_int("[25,7]"));
    test(get_list_int("[7,7,6]"));
    test(get_list_int("[1,1,1,1]"));
}
}
namespace problem4 {
class Solution {
public:


    static void dfs(const vector<vector<int>>& tree, const string& s, int index, string& def_str, vector<string>& memo) {
        if (!memo[index].empty()) {
            def_str += memo[index];
            return;
        }
        string work;
        for (auto&& child : tree[index]) {
            dfs(tree, s, child, work, memo);
        }
        work += s[index];
        memo[index] = work;
        def_str += work;
    }


    static vector<bool> mle(vector<int>& parent, string s) {
        vector<vector<int>> tree(size(parent));

        for (int i = 1; i < size(parent); i++) {
            tree[parent[i]].emplace_back(i);
        }

        vector<bool> ans;
        ans.reserve(size(s));
        vector<string> memo(size(parent));

        for (int i = 0; i < size(parent); i++) {
            if (tree[i].empty()) {
                ans.emplace_back(true);
            }
            else {
                string def_str;
                dfs(tree, s, i, def_str, memo);
                ans.emplace_back(is_palindrome(def_str));
            }
        }
        return ans;
    }

    static bool is_palindrome(const string& p) {
        for (int i = 0; i < size(p) / 2; i++) {
            if (p[i] != p[size(p) - i - 1]) {
                return false;
            }
        }
        return true;
    }

    static void dfs1(const vector<vector<int>>& tree, const string& s, int index, string& dfs_str, vector<pair<int, int>>& rev_indexes) {
        const int begin_ind = size(dfs_str);
        for (auto&& child : tree[index]) {
            dfs1(tree, s, child, dfs_str, rev_indexes);
        }
        dfs_str += s[index];
        const int end_ind = size(dfs_str);
        rev_indexes[index] = { begin_ind,end_ind };
    }

    static vector<int> manacher(const string& s) {
        vector< int > radius(s.size());
        int i = 0, j = 0;
        while (i < s.size()) {
            while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
                ++j;
            }
            radius[i] = j;
            int k = 1;
            while (i - k >= 0 && i + k < s.size() && k + radius[i - k] < j) {
                radius[i + k] = radius[i - k];
                ++k;
            }
            i += k;
            j -= k;
        }
        return radius;
    }

    static bool is_palindrome1(const vector<int>& manachers_radiuss, const vector<int>& manachers_radiuss_even, int begin_ind, int end_ind) {
        const auto width = end_ind - begin_ind;
        if (width % 2 == 0) {
            const auto index = begin_ind * 2 + width;
            return (width / 2) <= ((manachers_radiuss_even[index] - 1) / 2);
        }
        else {
            const auto center = (end_ind + begin_ind) / 2;
            return width <= (2 * (manachers_radiuss[center] - 1) + 1);
        }
    }

    vector<bool> findAnswer(vector<int>& parent, string s) {
        vector<vector<int>> tree(size(parent));

        for (int i = 1; i < size(parent); i++) {
            tree[parent[i]].emplace_back(i);
        }

        string dfs_str_root;
        dfs_str_root.reserve(size(parent));
        vector<pair<int, int>> rev_indexes(size(parent));
        dfs1(tree, s, 0, dfs_str_root, rev_indexes);
        vector<bool> ans;
        ans.reserve(size(s));
        vector<string> memo(size(parent));

        const auto manachers_radius = manacher(dfs_str_root);
        string dfs_str_root_even = "#";
        dfs_str_root_even.reserve((size(parent) + 1) * 2);
        for (auto&& c : dfs_str_root) {
            dfs_str_root_even += c;
            dfs_str_root_even += '#';
        }

        const auto manachers_radius_even = manacher(dfs_str_root_even);


        for (int i = 0; i < size(parent); i++) {
            if (tree[i].empty()) {
                ans.emplace_back(true);
            }
            else {
                const auto [begin_ind, end_ind] = rev_indexes[i];
                ans.emplace_back(is_palindrome1(manachers_radius, manachers_radius_even, begin_ind, end_ind));
            }
        }
        return ans;
    }
};
void test(vector<int>&& parent, string&& s) {
    output(Solution().findAnswer(parent, s));
}
void run() {
    test(get_list_int("[-1,9,7,13,14,12,3,13,11,12,12,15,16,10,0,14,15]"), "ifdhhfdhikfiedhdh");

    test(get_list_int("[-1,0,0,1,1,2]"), "aababa");
    test(get_list_int("[-1,0,0,0,0]"), "aabcb");
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