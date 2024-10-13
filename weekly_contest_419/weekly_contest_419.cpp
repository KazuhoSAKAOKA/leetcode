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
#include <cassert>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"


using namespace std;

namespace problem1 {
class Solution {
public:

    static int get_x(const map<size_t, set<int>>& rev_map, int x) {
        auto outer_it = crbegin(rev_map);
        auto inner_it = crbegin(outer_it->second);

        int total = 0;
        for (int i = 0; i < x; i++) {
            const auto& current_set = outer_it->second;
            if (inner_it == crend(current_set)) {
                ++outer_it;
                if (outer_it == crend(rev_map)) {
                    break;
                }
                inner_it = crbegin(outer_it->second);
            }
            total += outer_it->first * (*inner_it);
            ++inner_it;
        }
        return total;
    }

    vector<int> findXSum(vector<int>& nums, int k, int x) {

        vector<int> ans;
        for (int i = 0; i <= size(nums) - k; i++) {
            unordered_map<int, size_t> freq_map;
            for (int j = 0; j < k; j++) {
                freq_map[nums[j + i]]++;
            }
            map<size_t, set<int>> rev_map;

            for (auto&& [num, freq] : freq_map) {
                rev_map[freq].insert(num);
            }

            const auto v = get_x(rev_map, x);
            ans.emplace_back(v);
        }

        return ans;
    }
};

void test(vector<int>&& nums, int k, int x) {
    output(Solution().findXSum(nums, k, x));
}
void run() {
    test(get_list_int("[9,2,2]"), 3, 3);
    test(get_list_int("[1,1,2,2,3,4,2,3]"), 6, 2);
    test(get_list_int("[3,8,7,8,7,5]"), 2, 2);
}
}
namespace problem2 {
class Solution {
public:

    static pair<int,int> rec(const TreeNode* node, map<int, int>& pbt_size_map) {
        if (node == nullptr) {
            return {0,0};
        }

        const auto [left_depth, nodes1] = rec(node->left, pbt_size_map);
        const auto [right_depth, nodes2] = rec(node->right, pbt_size_map);
        if (left_depth == right_depth && left_depth >= 0) {
            int pbt_size = 1 + nodes1 + nodes2;
            pbt_size_map[pbt_size]++;
            return { left_depth + 1, pbt_size };
        }
        else {
            return { -1,-1 };
        }
    }

    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        map<int, int> pbt_size_map;
        rec(root, pbt_size_map);
        vector<int> rev;
        for (auto&& [s, freq] : pbt_size_map) {
            for (int i = 0; i < freq; i++) {
                rev.emplace_back(s);
            }
        }
        if (size(rev) < k) {
            return -1;
        }
        sort(begin(rev), end(rev), std::greater<int>());
        auto it = cbegin(rev);
        for (int i = 0; i < k - 1; i++) {
            ++it;
        }
        return *it;
    }
};

void test(vector<optional<int>>&& values, int k) {
    TreeNode* root = create_treenode2(values);
    cout << Solution().kthLargestPerfectSubtree(root, k) << endl;
}

void run() {
    test(get_list_optional_int("[5,3,6,5,2,5,7,1,8,null,null,6,8]"), 2);
    test(get_list_optional_int("[1,2,3,4,5,6,7]"), 1);
    test(get_list_optional_int("[1,2,3,null,4]"), 3);
    test(get_list_optional_int("[1,2,3,null,4]"), 2);
}
}
namespace problem3 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    static size_t get_index(char c) {
        switch (c) {
        case 'F':
            return 0;
        case 'W':
            return 1;
        case 'E':
            return 2;
        }
        throw exception();
    }

    static void calc_pattern(map<int, long long>& inner_map, int transit_val, map<int, long long>& before_map) {
        for (auto&& [diff, counts] : before_map) {
            inner_map[diff + transit_val] += counts;
            inner_map[diff + transit_val] %= MODULO;
        }
    }

    static int get_transit_val(char me, char other) {
        if (me == other) { return 0; }
        switch (me) {
        case 'F':
            return other == 'W' ? -1 : 1;
        case 'W':
            return other == 'E' ? -1 : 1;
        case 'E':
            return other == 'F' ? -1 : 1;
        }
        throw exception();
    }

    int countWinningSequences(string s) {
        vector<vector<map<int, long long>>> dp(size(s), vector<map<int, long long>>(3));

        switch (s[0]) {
        case 'F':
            dp[0][get_index('F')] = map<int, long long>{ {0,1} };
            dp[0][get_index('W')] = map<int, long long>{ {1,1} };
            dp[0][get_index('E')] = map<int, long long>{ {-1,1} };
            break;
        case 'W':
            dp[0][get_index('F')] = map<int, long long>{ {-1,1} };
            dp[0][get_index('W')] = map<int, long long>{ {0,1} };
            dp[0][get_index('E')] = map<int, long long>{ {1,1} };
            break;
        case 'E':
            dp[0][get_index('F')] = map<int, long long>{ {1,1} };
            dp[0][get_index('W')] = map<int, long long>{ {-1,1} };
            dp[0][get_index('E')] = map<int, long long>{ {0,1} };
            break;
        }

        for (size_t i = 1; i < size(s); i++) {
            calc_pattern(dp[i][get_index('F')], get_transit_val('F', s[i]), dp[i - 1][get_index('W')]);
            calc_pattern(dp[i][get_index('F')], get_transit_val('F', s[i]), dp[i - 1][get_index('E')]);

            calc_pattern(dp[i][get_index('W')], get_transit_val('W', s[i]), dp[i - 1][get_index('F')]);
            calc_pattern(dp[i][get_index('W')], get_transit_val('W', s[i]), dp[i - 1][get_index('E')]);

            calc_pattern(dp[i][get_index('E')], get_transit_val('E', s[i]), dp[i - 1][get_index('F')]);
            calc_pattern(dp[i][get_index('E')], get_transit_val('E', s[i]), dp[i - 1][get_index('W')]);
        }

        long long total = 0;
        for (auto&& inner_map : dp[size(s) - 1]) {
            for (auto&& [score, count] : inner_map) {
                if (0 < score) {
                    total += count;
                    total %= MODULO;
                }
            }
        }

        return static_cast<int>(total % MODULO);
    }
};

void test(string&& s) {
    cout << Solution().countWinningSequences(s) << endl;
}
void run() {
    test("FFF");
    test("FWEFW");
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