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
    string fractionToDecimal(int numerator, int denominator) {
        const long long numeratorL = static_cast<long long>(numerator);
        const long long denominatorL = static_cast<long long>(denominator);

        if (numeratorL % denominatorL == 0) {
            return to_string(numeratorL / denominatorL);
        }

        string pre;
        long long cur_val = abs(numeratorL);
        if (numeratorL * denominatorL < 0) {
            pre += '-';
        }
        const long long deno = abs(denominatorL);

        if (cur_val > deno) {
            pre += to_string(cur_val / deno);
            cur_val %= deno;
        }
        else {
            pre += '0';
        }
        pre += ".";
        cur_val *= 10;
        string digits;
        map<long long, int> mp;
        int index = 0;
        while (cur_val > 0) {
            auto it = mp.find(cur_val);
            if (it != cend(mp)) {
                string ans = pre;
                if (it->second > 0) {
                    ans += digits.substr(0, it->second);
                }
                ans += '(';
                ans += digits.substr(it->second);
                ans += ')';
                return ans;
            }
            mp.insert({ cur_val, index });
            const auto v = cur_val / deno;
            digits += static_cast<char>(v + '0');
            cur_val %= deno;
            cur_val *= 10;
            index++;
        }

        string ans = pre + digits;
        return ans;
    }
};

static void test(int numerator, int denominator) {
    cout << Solution().fractionToDecimal(numerator, denominator) << endl;
}
int main() {
    test(-2147483648, -10);
    test(-1, -2147483648);
    test(7, -12);
    test(-50, 8);
    test(1, 2);
    test(2, 1);
    test(4, 333);
	return 0;
}