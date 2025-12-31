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
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        unordered_set<int> friend_set(cbegin(friends), cend(friends));
        vector<int> ans;
        ans.reserve(size(friends));
        for (auto&& o : order) {
            if (friend_set.find(o) != cend(friend_set)) {
                ans.emplace_back(o);
            }
        }
        return ans;
    }
};
static void test(vector<int>&& order, vector<int>&& friends) {
    output(Solution().recoverOrder(order, friends));
}
static void run() {
    test(get_list_int("[3,1,2,5,4]"), get_list_int("[1,3,4]"));
    test(get_list_int("[1,4,5,3,2]"), get_list_int("[2,5]"));
}
}
namespace problem2 {
class Solution {
public:

    static vector<int> enum_divisors(int N) {
        vector<int> res;
        for (int i = 1; i * i <= N; ++i) {
            if (N % i == 0) {
                res.push_back(i);
                if (N / i != i) { res.push_back(N / i); }
            }
        }
        sort(begin(res), end(res));
        return res;
    }


    static void rec(const vector<int>& divisors, int n, int k, int index, vector<int>& cur_arr, int cur_val, int& cur_min, vector<int>& min_arr) {
        if (size(cur_arr) == k) {
            if (cur_val != n) {
                return;
            }
            const auto diff = cur_arr.back() - cur_arr.front();
            if (diff < cur_min) {
                cur_min = diff;
                min_arr = cur_arr;
            }
        }
        if (size(divisors) == index) {
            return;
        }
        rec(divisors, n, k, index + 1, cur_arr, cur_val, cur_min, min_arr);
        int working = cur_val;
        int count = 0;
        while (working <= n && size(cur_arr) < k) {
            const auto temp = static_cast<long long>(working) * divisors[index];
            if (n < temp) { break; }
            working = static_cast<int>(temp);
            cur_arr.emplace_back(divisors[index]);
            count++;
            rec(divisors, n, k, index + 1, cur_arr, working, cur_min, min_arr);
        }
        for (auto i = 0; i < count; i++) {
            cur_arr.pop_back();
        }
    }

    vector<int> minDifference(int n, int k) {
        const auto divisors = enum_divisors(n);
        vector<int> working;
        vector<int> ans;
        int cur_min = INT_MAX;
        rec(divisors, n, k, 0, working, 1, cur_min, ans);
        return ans;
    }
};
static void test(int n, int k) {
    output(Solution().minDifference(n, k));
}
static void run() {
    test(100, 2);
    test(44, 3);
}
}
namespace problem3 {
constexpr size_t MAX_BITS = 18;
class Solution {
public:
    static long long naive(const vector<int>& nums) {
        const auto n = size(nums);
        long long max_products = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((nums[i] & nums[j]) == 0) {
                    max_products = max(max_products, static_cast<long long>(nums[i]) * nums[j]);
                }
            }
        }
        return max_products;
    }

    struct trie_tree {
        struct node {
            vector<node*> nodes_;
            int max_value_;
            node() :nodes_(2, nullptr ), max_value_(0){
            }
        };
        node root_;

        void add(int value) {
            node* current = &root_;
            const auto rev = ~value;
            for (int i = 0; i < MAX_BITS; i++) {
                const auto index = (rev & (1 << i)) == 0 ? 0 : 1;
                if (current->nodes_[index] == nullptr) {
                    current->nodes_[index] = new node();
                    current->nodes_[index]->max_value_ = value;
                }
                else {
                    current->nodes_[index]->max_value_ = max(current->nodes_[index]->max_value_, value);
                }
                current = current->nodes_[index];
            }
        }

        int get_mask_max(int value) const {
            const node* current = &root_;
            int max_value = 0;
            for (int i = 0; i < MAX_BITS; i++) {
                const auto index = (value & (1 << i)) == 0 ? 0 : 1;
                if (current->nodes_[index] == nullptr) {
                    break;
                }
                if ((value & current->nodes_[index]->max_value_) == 0) {
                    max_value = max(max_value, current->nodes_[index]->max_value_);
                }
                current = current->nodes_[index];
            }
            return max_value;
        }

    };

    static int get_msb(int num) {
        int position = -1;
        while (num > 0) {
            num >>= 1;
            position++;
        }
        return position;
    }
    long long maxProduct(vector<int>& nums) {
        const auto max_val = *max_element(cbegin(nums), cend(nums));
        const auto msb = get_msb(max_val);
        const auto MASK = (1 << (msb + 1)) - 1;
        vector<int> dp(MASK + 1, 0);
        for (auto&& num : nums) {
            dp[num] = num;
        }
        for (int mask = 0; mask <= MASK; mask++) {
            for (int bit = 0; bit <= msb; bit++) {
                const auto bm = 1 << bit;
                if ((mask & bm) != 0) {
                    const auto M = mask ^ bm;
                    dp[mask] = max(dp[mask], dp[M]);
                }
            }
        }

        long long max_products = 0;

        for (auto&& num : nums) {
            const auto  cm = ~num & MASK;
            const long long cur_products = static_cast<long long>(num) * dp[cm];
            max_products = max(max_products, cur_products);
        }
        return max_products;
//        return naive(nums);
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maxProduct(nums) << endl;
}
static void run() {
    test(get_list_int("[10,10,14,5,11,6,14,8]"));
    test(get_list_int("[64,8,32]"));
    test(get_list_int("[1,2,3,4,5,6,7]"));
    test(get_list_int("[5,6,4]"));
}
}
namespace problem4 {
class Solution {
public:
    template <typename T>
    static
    T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

    int totalBeauty(vector<int>& nums) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(nums);
        map<int, map<int, long long>> pre_map;
        long long total_sum = 0LL;
        for (int i = 0; i < n; i++) {
            map<int, map<int, long long>> next_map(pre_map);

            const auto& num = nums[i];
            total_sum += static_cast<long long>(num);
            total_sum %= MODULO;
            next_map[num][num]++;

            auto last_it = pre_map.lower_bound(num);
            for (auto it = begin(pre_map); it != last_it; ++it) {
                for (auto&& [past_gcd, count] : it->second) {
                    const auto cur_gcd = gcd(past_gcd, num);
                    total_sum += cur_gcd * count;
                    total_sum %= MODULO;
                    next_map[num][cur_gcd] += count;
                }
            }
            swap(next_map, pre_map);
        }
        return static_cast<int>(total_sum % MODULO);
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().totalBeauty(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"));
    test(get_list_int("[4,6]"));
}
}

int main(){
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}