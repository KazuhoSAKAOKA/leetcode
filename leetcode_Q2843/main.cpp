#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
using namespace std;
class Solution {
public:
    static vector<int> get_digits(int v) {
        if (v == 0) { return { 0 }; }
        auto cur = v;
        vector<int> digits;
        while (cur > 0) {
            digits.emplace_back(cur % 10);
            cur /= 10;
        }
        return vector<int>(crbegin(digits), crend(digits));
    }

    static bool check(int value) {
        auto digits = get_digits(value);
        if (size(digits) % 2 != 0) { return false; }
        int v1 = 0;
        int v2 = 0;
        for (int i = 0; i < size(digits) / 2; i++) {
            v1 += digits[i];
            v2 += digits[size(digits) - 1 - i];
        }
        return v1 == v2;
    }
    static int naive(int low, int high) {
        int count = 0;
        for (int i = low; i <= high; i++) {
            if (check(i)) { count++; }
        }
        return count;
    }

    static long long digitdp(const vector<int>& digits, int len) {
        if (size(digits) < len) {
            return 0;
        }
        if (size(digits) == len) {
            vector <unordered_map<int, long long>> dpeq(len);
            const auto start_index = size(digits) - len;
            dpeq[0][digits[0]] = 1;
            for (int i = 1; i < len / 2; i++) {
                for (auto&& [v, cnt] : dpeq[i - 1]) {
                    dpeq[i][digits[i] + v] += cnt;
                }
            }
            for (int i = len / 2; i < len; i++) {
                for (auto&& [v, cnt] : dpeq[i - 1]) {
                    dpeq[i][digits[i] - v] += cnt;
                }
            }
            vector <unordered_map<int, long long>> dp(len);
            for (int i = 1; i <= 9; i++) {
                dp[0][i]++;
            }

            for (int i = 1; i < len / 2; i++) {
                for (int j = 0; j <= 9; j++) {
                    for (auto&& [v, cnt] : dp[i - 1]) {
                        dp[i][v + j] += cnt;
                    }

                }
                for (int j = 0; j < digits[i]; j++) {
                    for (auto&& [v, cnt] : dpeq[i - 1]) {
                        dp[i][v + j] += cnt;
                    }
                }
            }

            for (int i = len; i < len; i++) {
                for (int j = 0; j <= 9; j++) {
                    for (auto&& [v, cnt] : dp[i - 1]) {
                        dp[i][v - j] += cnt;
                    }
                }
                for (int j = 0; j < digits[i]; j++) {
                    for (auto&& [v, cnt] : dpeq[i - 1]) {
                        dp[i][v - j] += cnt;
                    }
                }
            }
            return dp[len - 1][0] + dpeq[len-1][0];
        }
        else {
            vector <unordered_map<int, long long>> dp(len);
            const auto start_index = size(digits) - len;
            for (int i = 1; i <= 9; i++) {
                dp[0][i]++;
            }

            for (int i = 1; i < len / 2; i++) {
                for (int j = 0; j <= 9; j++) {
                    for (auto&& [v, cnt] : dp[i - 1]) {
                        dp[i][v + j] += cnt;
                    }
                }
            }
            for (int i = len; i < len; i++) {
                for (int j = 0; j <= 9; j++) {
                    for (auto&& [v, cnt] : dp[i - 1]) {
                        dp[i][v - j] += cnt;
                    }
                }
            }
            return dp[len - 1][0];
        }
    }

    static long long use_digitdp(int low, int high) {
        const auto high_digits = get_digits(high);
        const auto low_digits = get_digits(low);
        long long total = 0;

        for (int i = 2; i <= size(high_digits); i += 2) {
            total += digitdp(high_digits, i) - digitdp(low_digits, i);
        }
        return total;
    }


    int countSymmetricIntegers(int low, int high) {
        return use_digitdp(low, high);
        //return naive(low, high);
    }
};

void test(int low, int high) {
    cout << Solution().countSymmetricIntegers(low, high) << endl;
}

int main() {
    test(1, 100);
    test(1200, 1230);
	return 0;
}