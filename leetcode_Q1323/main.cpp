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

    static vector<int> get_revdigits(int num) {
        if (num == 0) { return{ 0 }; }
        vector<int> digits;
        while (num > 0) {
            digits.emplace_back(num % 10);
            num /= 10;
        }
        return digits;
    }


    int maximum69Number(int num) {
        auto digits = get_revdigits(num);
        for (auto it = rbegin(digits); it != rend(digits); ++it) {
            if (*it == 6) {
                *it = 9;
                break;
            }
        } 
        int ans = 0;
        int base = 1;
        for (auto&& digit: digits) {
            ans += digit * base;
            base *= 10;
        }
        return ans;
    }
};

static void test(int num) {
    cout << Solution().maximum69Number(num) << endl;
}

int main() {
    test(9669);
    test(9996);
    test(9999);
	return 0;
}