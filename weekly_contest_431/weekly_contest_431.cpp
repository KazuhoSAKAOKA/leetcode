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

    template <typename T>
    static T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

    template <typename T>
    static T lcm(const T& a, const T& b) {
        return a / gcd(a, b) * b;
    }
    static long long gcd(const vector<int>& nums, int start, int end_include) {
        long long v = static_cast<long long>(nums[start]);
        for (int i = start + 1; i <= end_include; i++) {
            v = gcd(v, static_cast<long long>(nums[i]));
        }
        return v;
    }

    static long long lcm(const vector<int>& nums, int start, int end_include) {
        long long v = static_cast<long long>(nums[start]);
        for (int i = start + 1; i <= end_include; i++) {
            v = lcm(v, static_cast<long long>(nums[i]));
        }
        return v;
    }

    static long long check_product(const vector<int>& nums, int start, int end_include, long long gcd_val, long long lcm_val) {
        long long v = 1;
        long long upper = gcd_val * lcm_val;
        for (int i = start; i <= end_include; i++) {
            v *= static_cast<long long>(nums[i]);
            if (v > upper) { return false; }
        }
        return v == upper;
    }

    int maxLength(vector<int>& nums) {
        int max_length = 0;
        for (int l = 0; l < size(nums); l++) {
            for (int r = l + 1; r < size(nums); r++) {
                const auto gcd_val = gcd(nums, l, r);
                const auto lcm_val = lcm(nums, l, r);
                if (check_product(nums, l, r, gcd_val, lcm_val)) {
                    max_length = max(max_length, r - l + 1);
                }
            }
        }
        return max_length;
    }
}; 

static void test(vector<int>&& nums) {
    cout << Solution().maxLength(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,1,2,1,1,1]"));
    test(get_list_int("[2,3,4,5,6]"));
    test(get_list_int("[1,2,3,1,4,5,1]"));
}
}
namespace problem2 {
class Solution {
public:
    long long calculateScore(string s) {
        vector<vector<int>> freqs(26);
        long long score = 0LL;

        for (int i = 0; i < size(s); i++) {
            const int index = s[i] - 'a';
            const char mirror = 'z' - (index) - 'a';
            auto& list = freqs[mirror];
            if (list.empty()) {
                freqs[index].emplace_back(i);
            }
            else {
                const auto j = list.back();
                list.pop_back();
                score += static_cast<long long>(i - j);
            }
        }
        return score;
    }
}; 
void test(string&& s) {
    cout << Solution().calculateScore(s) << endl;
}
static void run() {
    test("aczzx");
    test("abcdef");
}
}
namespace problem3 {
class Solution {
public:
    /*
            ;*/

    static long long mle(vector<vector<int>>& coins, int k) {
        int max_right = 0;
        for (auto&& coin : coins) {
            max_right = max(max_right, coin[1]);
        }
        vector<long long> coins_pred(max_right + 2);
        for (auto&& coin : coins) {
            coins_pred[coin[0]] += coin[2];
            coins_pred[coin[1] + 1] += -coin[2];
        }

        long long max_coin = 0;
        long long current_coin = 0;
        long long current_pred = 0;
        for (int i = 0; i < k; i++) {
            current_pred += coins_pred[i];
            current_coin += current_pred;
        }
        max_coin = max(max_coin, current_coin);
        long long current_front_pred = 0;

        for (int i = k; i < size(coins_pred) - 1; i++) {
            current_front_pred -= coins_pred[i - k];
            current_pred += coins_pred[i];
            current_coin += current_front_pred;
            current_coin += current_pred;
            max_coin = max(max_coin, current_coin);
        }

        return max_coin;
    }

    class range_coins {
        int k;
        int current_start;

    };


    long long maximumCoins(vector<vector<int>>& coins, int k) {
        map<int, pair<int, long long>> value_map;
        for (auto&& coin : coins) {
            value_map[coin[0]] = { coin[1], coin[2] };
        }

        long long max_value = 0;
        auto it = cbegin(value_map);
        int current_start = it->first;
        int current_end = current_start + k;
        long long current_coins = 0;

        struct info {
            int start_index;
            int end_index;
            long long coin;
        };
        queue<info> coins_que;
        while (it != cend(value_map)) {
            const auto begin_point = it->first;
            const auto [end_point, coin] = it->second;
            if (end_point <= current_end) {
                current_coins += coin * (end_point - it->first + 1);
                coins_que.push(info{begin_point, end_point, coin});
            }
            else {
                if (current_end < begin_point) {
                    current_start = begin_point;
                    current_end = current_start + k;
                    current_coins = coin * min(current_end, end_point);
                    while (!coins_que.empty()) { coins_que.pop(); }
                    coins_que.push(info{ begin_point, end_point, coin });
                }
                else {
                    while (!coins_que.empty() && coins_que.front().end_index + k < end_point) {

                        current_coins += coin * (end_point - it->first + 1);


                    }
                }
            }

            max_value = max(max_value, current_coins);
            ++it;
        }

        return max_value
        return max_coin;
    }
}; 
static void test(vector<vector<int>>&& coins, int k) {
    cout << Solution().maximumCoins(coins, k) << endl;
}

static void run() {
    test(get_matrix_int("[[8,12,13],[29,32,2],[13,15,2],[40,41,18],[42,48,18],[33,36,11],[37,38,6]]"), 28);
    test(get_matrix_int("[[8,10,1],[1,3,2],[5,6,4]]"), 4);
    test(get_matrix_int("[[1,10,3]]"), 2);
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