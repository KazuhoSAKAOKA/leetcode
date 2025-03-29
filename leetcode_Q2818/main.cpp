#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    static vector<int> eratosthenes(int n) {
        std::vector<bool> candidates(n + 1, true);
        candidates[0] = false;
        candidates[1] = false;
        const auto limit = n;
        int current = 2;
        while (current <= limit) {
            if (candidates[current]) {
                for (int i = 2; i * current <= n; i++) {
                    candidates[i * current] = false;
                }
            }
            current++;
        }
        vector<int> primes;
        for (int i = 2; i <= limit; i++) {
            if (candidates[i]) {
                primes.emplace_back(i);
            }
        }
        return primes;
    }

    static int prime_score(int value, const vector<int>& primes) {
        int score = 0;
        int current = value;
        for (auto&& prime : primes) {
            if (current % prime == 0) {
                score++;
                do {
                    current /= prime;
                } while (current % prime == 0);
            }
            if (current == 0) { break; }
        }
        return score;
    }

    static long long pow2(long long value, long long exp) {
        if (exp == 0) {
            return 1;
        }
        if (exp % 2 == 1) {
            return (pow2((value * value) % MODULO, exp / 2) * value) % MODULO;
        }
        else {
            return pow2((value * value) % MODULO, exp / 2);
        }
    }


    int maximumScore(vector<int>& nums, int k) {
        const auto n = size(nums);
        const auto max_val = *max_element(cbegin(nums), cend(nums));
        const auto primes = eratosthenes(max_val);
        vector<int> prime_scores(n);
        for (int i = 0; i < n; i++) {
            prime_scores[i] = prime_score(nums[i], primes);
        }
        vector<int> left(n);
        {
            vector<int> mono_stack{ -1 };
            for (int i = 0; i < n; i++) {
                while (mono_stack.back() >= 0 && prime_scores[mono_stack.back()] < prime_scores[i]) {
                    mono_stack.pop_back();
                }
                left[i] = mono_stack.back();
                mono_stack.push_back(i);
            }
        }
        vector<int> right(n);
        {
            vector<int> mono_stack{ static_cast<int>(n) };
            for (int i = n - 1; i >= 0; i--) {
                while (mono_stack.back() < n && prime_scores[mono_stack.back()] <= prime_scores[i]) {
                    mono_stack.pop_back();
                }
                right[i] = mono_stack.back();
                mono_stack.push_back(i);
            }
        }
        vector<int> indexes(n);
        for (int i = 0; i < n; i++) {
            indexes[i] = i;
        }
        sort(begin(indexes), end(indexes), [&](const auto& a, const auto& b) { return nums[a] > nums[b]; });
        long long cur_value = 1;
        int remain = k;
        int index = 0;
        while (remain > 0) {
            const auto target_index = indexes[index];
            const auto cur_num_ops = (target_index - left[target_index]) * (right[target_index] - target_index);
            const auto op_count = min(remain, cur_num_ops);
            cur_value *= pow2(nums[target_index], op_count);
            cur_value %= MODULO;
            remain -= op_count;
            index++;
        }
        return static_cast<int>(cur_value);
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maximumScore(nums, k) << endl;
}
int main() {
    test(get_list_int("[3289,2832,14858,22011]"), 6);
    test(get_list_int("[8,3,9,3,8]"), 2);
    test(get_list_int("[19,12,14,6,10,18]"), 3);
    return 0;
}