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
    vector<int> getSneakyNumbers(vector<int>& nums) {
        unordered_set<int> exists;
        vector<int> ans;
        for (auto&& num : nums) {
            if (exists.count(num) > 0) {
                ans.emplace_back(num);
            }
            else {
                exists.insert(num);
            }
        }
        return ans;
    }
};
void test(vector<int>&& nums) {
    output(Solution().getSneakyNumbers(nums));
}
void run() {
    test(get_list_int("[0,1,1,0]"));
    test(get_list_int("[0,3,2,1,3,2]"));
    test(get_list_int("[7,1,5,4,3,4,6,0,9,5,8,2]"));
}

}
namespace problem2 {
class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        vector<vector<long long>> dp(size(b), vector<long long>(4, LLONG_MIN));
        dp[0][0] = static_cast<long long>(a[0]) * static_cast<long long>(b[0]);

        for (int i = 1; i < size(b); i++) {
            dp[i][0] = max(dp[i - 1][0], static_cast<long long>(a[0]) * static_cast<long long>(b[i]));
            for (int j = 1; j < min(i + 1, 4); j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + static_cast<long long>(a[j]) * static_cast<long long>(b[i]));
            }
        }
        return dp[size(b) - 1][3];
    }
};
void test(vector<int>&& a, vector<int>&& b) {
    cout << Solution().maxScore(a, b) << endl;
}
void run() {
    test(get_list_int("[-7,5,-10,-10]"), get_list_int("[7,-8,-1,2,4,8,-5,-5,5,-2,4]"));
    test(get_list_int("[3,2,5,6]"), get_list_int("[2,-6,4,-5,-3,2,-7]"));
    test(get_list_int("[-1,4,5,-2]"), get_list_int("[-5,-1,-3,-2,-4]"));
}

}
namespace problem3 {
class Solution {
public:

    struct trie_tree {
        struct node {
            bool end_;
            std::unordered_map<char, node*> nodes_;
        };
        node root_;

        void add(const std::string& s) {
            node* current = &root_;
            for (int i = 0; i < s.size(); i++) {
                const auto it = current->nodes_.find(s[i]);
                if (it != cend(current->nodes_)) {
                    current = (it->second);
                }
                else {
                    auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
                    current = (itnew->second);
                }
            }
            current->end_ = true;
        }

        size_t get_common_prefix_list(const std::string& s, size_t offset) const {
            const node* current = &root_;
            for (size_t i = 0; i < s.size() - offset; i++) {
                const auto it = current->nodes_.find(s[i + offset]);
                if (it == cend(current->nodes_)) {
                    return i;
                }
                current = (it->second);
            }
            return s.size() - offset;
        }

    };
    using memo_key_t = size_t;
    using memo_t = map<memo_key_t, int>;
    static int rec(const string& target, size_t index, const trie_tree& trie, memo_t& memo) {
        if (size(target) == index) {
            return 0;
        }
        const auto key = memo_key_t(index);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        const auto common_len = trie.get_common_prefix_list(target, index);
        if (common_len == 0) {
            return INT_MAX;
        }
        int min_count = INT_MAX;
        for (size_t i = 1; i <= common_len; i++) {
            const int current = rec(target, index + i, trie, memo);
            if (current != INT_MAX) {
                min_count = min(min_count, current + 1);
            }
        }
        memo[key] = min_count;
        return min_count;
    }

    static int tle(vector<string>& words, string target) {
        trie_tree trie;
        for (auto&& word : words) {
            trie.add(word);
        }
        memo_t memo;
        const int count = rec(target, 0, trie, memo);
        if (count == INT_MAX) { return -1; }
        return count;
    }

    int minValidStrings(vector<string>& words, string target) {
        trie_tree trie;
        for (auto&& word : words) {
            trie.add(word);
        }

        vector<int> dp(size(target) + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < size(target); i++) {
            const auto common_len = trie.get_common_prefix_list(target, i);
            if (common_len > 0) {
                for (int j = 1; j <= common_len; j++) {
                    if (dp[i] != INT_MAX) {
                        dp[i + j] = min(dp[i + j], dp[i] + 1);
                    }
                }
            }
        }
        if (dp[size(target)] == INT_MAX) { return -1; }
        return dp[size(target)];
    }
};

void test(vector<string>&& words, string&& target) {
    cout << Solution().minValidStrings(words, target) << endl;
}
    
void run() {
    test(get_list_str(R"(["abc","aaaaa","bcdef"])"), "aabcdabc");
    test(get_list_str(R"(["abababab","ab"])"), "ababaababa");
    test(get_list_str(R"(["abcdef"])"), "xyz");
}
}
namespace problem4 {
void run() {
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