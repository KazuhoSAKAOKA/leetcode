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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int minFlips(string s) {
        const int n = size(s);
        if (n < 2) { return 0; }
        int even_count = 0;
        int odd_count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                if (i % 2 == 0) {
                    even_count++;
                }
                else {
                    odd_count++;
                }
            }
        }
        int min_count = INT_MAX;
        if (n % 2 == 0) {
            const auto half = n / 2;
            min_count = min(min_count, even_count + (half - odd_count));
            min_count = min(min_count, odd_count + (half - even_count));
        }
        else {
            const int evens = n / 2 + 1;
            const int odds = n / 2;
            min_count = min(min_count, even_count + (odds - odd_count));
            min_count = min(min_count, odd_count + (evens - even_count));

            for (int i = 0; i < n; i++) {
                if (s[i] == '1') {
                    even_count--;
                    odd_count++;
                }
                swap(even_count, odd_count);
                min_count = min(min_count, even_count + (odds - odd_count));
                min_count = min(min_count, odd_count + (evens - even_count));
            }
        }
        return min_count;
    }
};

static void test(string&& s) {
    cout << Solution().minFlips(s) << endl;
}

int main()
{
    test("111000");
    test("010");
    test("1110");
    test("01001001101");
    return 0;
}