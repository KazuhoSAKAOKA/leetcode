#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <optional>

using namespace std;
class Solution {
public:
    static void make_digit_arrs(vector<int>& digit_counts, int target_len, int index, int cur_count, vector<int>& cur_digits, vector<vector<int>>& digitss) {
        if (index == 9) {
            if (target_len == cur_count) {
                digitss.emplace_back(cur_digits);
            }
            return;
        }

        make_digit_arrs(digit_counts, target_len, index + 1, cur_count, cur_digits, digitss);
        if (index + 1 <= target_len - cur_count) {
            cur_digits[index] = index + 1;
            make_digit_arrs(digit_counts, target_len, index + 1, cur_count + (index + 1), cur_digits, digitss);
            cur_digits[index] = 0;
        }
    }

    static vector<int> get_digits(int n) {
        if (n == 0) {
            return { 0 };
        }
        vector<int> digits;
        int cur(n);
        while (cur > 0) {
            digits.emplace_back(cur % 10);
            cur /= 10;
        }
        return vector<int>(crbegin(digits), crend(digits));
    }

    static optional<int> get_min(int target_len, const vector<int>& digit_counts, int index, const vector<int>& base_digits, vector<int>& useds, vector<int>& cur_digits, bool equals) {
        if (target_len == index) {
            if (equals) {
                return nullopt;
            }
            int value = 0;
            int base = 1;
            for (auto it = crbegin(cur_digits); it != crend(cur_digits); ++it) {
                value += *it * base;
                base *= 10;
            }
            return value;
        }
        int start;
        if (equals) {
            start = max(0, base_digits[index] - 1);
        }
        else {
            start = 0;
        }
        for (int i = start; i < 9; i++) {
            if (digit_counts[i] - useds[i] > 0) {
                useds[i]++;
                cur_digits.emplace_back(i + 1);
                auto ans1 = get_min(target_len, digit_counts, index + 1, base_digits, useds, cur_digits, equals && (i + 1 == base_digits[index]));
                cur_digits.pop_back();
                useds[i]--;
                if (ans1.has_value()) {
                    return ans1;
                }
            }
        }
        return nullopt;
    }

    int nextBeautifulNumber(int n) {
        vector<int> digit_counts(9);
        for (int i = 1; i <= 9; i++) {
            digit_counts[i - 1]= i;
        }

        auto base_digits = get_digits(n);
        auto cur_len = size(base_digits);
        for (;;) {
            vector<vector<int>> digitss;
            vector<int> work(9);
            make_digit_arrs(digit_counts, cur_len, 0, 0, work, digitss);
            optional<int> min_ans(nullopt);
            for (auto&& digits : digitss) {
                vector<int> used(9);
                vector<int> cur_work;
                const auto ans_opt = get_min(cur_len, digits, 0, base_digits, used, cur_work, true);
                if (ans_opt.has_value()) {
                    if (min_ans.has_value()) {
                        if (min_ans.has_value()) {
                            min_ans = min(min_ans.value(), ans_opt.value());
                        }
                    }
                    else {
                        min_ans = ans_opt.value();
                    }
                }
            }
            if (min_ans.has_value()) {
                return min_ans.value();
            }
            cur_len++;
            base_digits = vector<int>(cur_len, 0);
        }

    }
};

static void test(int n) {
    cout << Solution().nextBeautifulNumber(n) << endl;
}
int main() {
    test(1000);
    test(1);
    test(3000);
	return 0;
}