#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:
    static bool is_palindrome_base(long long v, int base) {
        if (v == 0) { return true; }
        vector<int> digits;
        while (v > 0) {
            digits.emplace_back(v % base);
            v /= base;
        }
        for (int i = 0; i < size(digits); i++) {
            if (digits[i] != digits[size(digits) - i - 1]) {
                return false;
            }
        }
        return true;
    }

    static long long tle(int k, int n) {
        long long cur_no = 1;
        int cur_count = 0;
        long long total = 0;
        while (cur_count < n) {
            if (is_palindrome_base(cur_no, 10) && is_palindrome_base(cur_no, k)) {
                total += cur_no;
                cur_count++;
            }
            cur_no++;
        }
        return total;
    }

    static long long digit10stovalue(const vector<int>& digits) {
        long long value = 0;
        long long base = 1;
        for (int i = 0; i < size(digits); i++) {
            value += static_cast<long long>(digits[i]) * base;
            base *= 10;
        }
        return value;
    }

    struct digit10s_t {
        vector<int> digits;

        long long next() {
            const int n = static_cast<int>(size(digits));
            const int center = n / 2;
            if (n % 2 == 0) {
                int offset = 1;
                while (center - offset >= 0) {
                    if (digits[center - offset] < 9) {
                        digits[center - offset]++;
                        digits[center + offset - 1]++;
                        return digit10stovalue(digits);
                    }
                    digits[center - offset] = 0;
                    digits[center + offset - 1] = 0;
                    offset++;
                }
            }
            else {
                if (digits[center] < 9) {
                    digits[center]++;
                    return digit10stovalue(digits);
                }
                digits[center] = 0;
                int offset = 1;
                while (center - offset >= 0) {
                    if (digits[center - offset] < 9) {
                        digits[center - offset]++;
                        digits[center + offset]++;
                        return digit10stovalue(digits);
                    }
                    digits[center - offset] = 0;
                    digits[center + offset] = 0;
                    offset++;
                }
            }
            digits.emplace_back(0);
            digits[0] = 1;
            digits[n] = 1;
            for (int i = 1; i < n; i++) {
                digits[i] = 0;
            }
            return digit10stovalue(digits);
        }
    };

    long long kMirror(int k, int n) {
        long long total = 0;
        digit10s_t digit10s{ {1} };
        total = 1;
        int cur_count = 1;
        while (cur_count < n) {
            const auto value = digit10s.next();
            if (is_palindrome_base(value, k)) {
                cur_count++;
                total += value;
            }
        }
        return total;
    }
};

void test(int k, int n) {
    cout << Solution().kMirror(k, n) << endl;
}
int main() {
    test(2, 5);
    test(3, 7);
    test(7, 17);
	return 0;
}