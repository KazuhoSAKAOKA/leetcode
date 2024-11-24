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
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        vector<long long> prefix_sums(size(nums) + 1);
        for (auto i = 0; i < size(nums); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + static_cast<long long>(nums[i]);
        }
        long long min_sum = LLONG_MAX;

        for (size_t i = 0; i < size(nums); i++) {
            for (size_t j = i + l; j <= min(size(nums), i + static_cast<size_t>(r)); j++) {
                const long long cur_sum = prefix_sums[j] - prefix_sums[i];
                if (cur_sum > 0) {
                    min_sum = min(min_sum, cur_sum);
                }
            }
        }
        if (min_sum == LLONG_MAX) { return -1; }
        return min_sum;
    }
};
void test(vector<int>&& nums, int l, int r) {
    cout << Solution().minimumSumSubarray(nums, l, r) << endl;
}

static void run() {
    test(get_list_int("[25,-9]"), 1, 1);
    test(get_list_int("[7,3]"), 2, 2);
    test(get_list_int("[3,-2,1,4]"),2, 3);
    test(get_list_int("[-2,2,-3,1]"),2,3 );
    test(get_list_int("[1,2,3,4]"), 2, 4);
}
}
namespace problem2 {
struct trie_tree {
    struct node {
        size_t count_ = 0;
        std::map<char, node*> nodes_;
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
        current->count_++;
    }
    bool erase(const std::string& s) {
        node* current = &root_;
        for (int i = 0; i < s.size(); i++) {
            const auto it = current->nodes_.find(s[i]);
            if (it == cend(current->nodes_)) {
                return false;
            }
            current = (it->second);
        }
        if (current->count_ == 0) {
            return false;
        }
        current->count_--;
        return true;
    }

};

class Solution {
public:
    bool isPossibleToRearrange(string s, string t, int k) {
        trie_tree tr;
        const int sub_size = size(s) / k;
        for (int i = 0; i < k; i++) {
            tr.add(s.substr(i * sub_size, sub_size));
        }
        for (int i = 0; i < k; i++) {
            if (!tr.erase(t.substr(i * sub_size, sub_size))) {
                return false;
            }
        }
        return true;
    }
};
void test(string&& s, string&& t, int k) {
    cout << Solution().isPossibleToRearrange(s, t, k) << endl;
}
static void run() {
    test("abcd", "cdab", 2);
    test("aabbcc", "bbaacc", 3);
    test("abcd", "cdab", 2);
}
}
namespace problem3 {
class Solution {
public:
    //template <typename TKey, typename TValue>
//const TValue& transit_map(map<TKey, TValue>& dp_map, const TKey& key, const TValue& value, function<const TValue&(const TValue&, const TValue&)> pred) {
//    const auto it = dp_map.find(key);
//    if (it == end(dp_map)) {
//        dp_map.insert(make_pair(key, value));
//        return value;
//    }
//    it->second = pred(it->second, value);
//    return value;
//}
    static int rec(const vector<int>& nums, int index, int k, int op1, int op2, int current_sum) {
        if (index == size(nums)) {
            return current_sum;
        }
        if (op1 == 0 && op2 == 0) {
            return current_sum;
        }

        int min_sum = rec(nums, index + 1, k, op1, op2, current_sum);
        if (0 < op1 && 0 < op2 && nums[index] >= k) {
            int temp = current_sum - nums[index];
            int temp_min = temp + div2up(nums[index] - k);
            int dived = div2up(nums[index]);
            if (dived >= k) {
                temp_min = min(temp_min, temp + dived - k);
            }
            min_sum = min(min_sum, rec(nums, index + 1, k, op1 - 1, op2 - 1, temp_min));
        }

        if (0 < op1) {
            int temp = current_sum - nums[index] + div2up(nums[index]);
            min_sum = min(min_sum, rec(nums, index + 1, k, op1 - 1, op2, temp));
        }

        if (0 < op2 && nums[index] >= k) {
            int temp = current_sum - k;
            min_sum = min(min_sum, rec(nums, index + 1, k, op1, op2 - 1, temp));
        }
        return min_sum;
    }

    static int tle(vector<int>& nums, int k, int op1, int op2) {
        const int total = accumulate(cbegin(nums), cend(nums), 0);
        return rec(nums, 0, k, op1, op2, total);
    }
    inline static int div2up(int num) {
        return num % 2 == 0 ? (num / 2) : ((num / 2) + 1);
    }
    static int do_both_op(int num, int k) {
        const int op2_first = div2up(num - k);
        const int dived = div2up(num);
        if (dived < k) {
            return op2_first;
        }
        return min(op2_first, dived - k);
    }


    int transit_map(map<pair<int,int>, int>& dp_map, const pair<int,int>& key, int value) {
        const auto it = dp_map.find(key);
        if (it == end(dp_map)) {
            dp_map.insert(make_pair(key, value));
            return value;
        }
        it->second = min(it->second, value);
        return value;
    }
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        vector < map<pair<int, int>, int>> dp(size(nums));

        dp[0][{op1, op2}] = nums[0];
        if (op1 > 0) {
            dp[0][{op1 - 1, op2}] = div2up(nums[0]);
        }
        if (op2 > 0 && nums[0] >= k) {
            dp[0][{op1, op2 - 1}] = nums[0] - k;
        }
        if (op1 > 0 && op2 > 0 && nums[0] >= k) {
            dp[0][{op1 - 1, op2 - 1}] = do_both_op(nums[0], k);
        }

        for (int i = 1; i < size(nums); i++) {
            for (auto&& [p, cur_sum] : dp[i - 1]) {
                const auto [op1_c, op2_c] = p;
                transit_map(dp[i], make_pair(op1_c, op2_c), cur_sum + nums[i]);
                if (op1_c > 0) {
                    transit_map(dp[i], make_pair(op1_c - 1, op2_c), cur_sum + div2up(nums[i]));
                }
                if (op2_c > 0 && nums[i] >= k) {
                    transit_map(dp[i], make_pair(op1_c, op2_c - 1), cur_sum + nums[i] - k);
                }
                if (op1_c > 0 && op2_c > 0 && nums[i] >= k) {
                    transit_map(dp[i], make_pair(op1_c - 1, op2_c - 1), cur_sum + do_both_op(nums[i], k));
                }
            }
        }

        int min_sum = INT_MAX;
        for (auto&& [_, cur_sum] : dp.back()) {
            min_sum = min(min_sum, cur_sum);
        }
        return min_sum;
    }
};
void test(vector<int>&& nums, int k, int op1, int op2) {
    cout << Solution().minArraySum(nums, k, op1, op2) << endl;
}

static void run() {
    //test(get_list_int("[10]"), 3, 1, 1);
    test(get_list_int("[2,8,3,19,3]"), 3, 1, 1);
    test(get_list_int("[2,4,3]"), 3, 2, 1);
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