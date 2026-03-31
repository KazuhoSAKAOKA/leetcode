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
#include <numbers>
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
    string generateString(string str1, string str2) {
        const auto n = size(str1);
        const auto m = size(str2);
        vector<bool> fixed(n + m - 1);
        string ans(n + m - 1, ' ');

        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] == ' ') {
                        ans[i + j] = str2[j];
                        fixed[i + j] = true;
                    }
                    else {
                        if (ans[i + j] != str2[j]) {
                            return "";
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {
                bool eq = true;
                int last_changable = -1;
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] == ' ') {
                        ans[i + j] = 'a';
                        if (eq && str2[j] != 'a') {
                            eq = false;
                        }
                    }
                    else {
                        if (eq) {
                            if (str2[j] != ans[i + j]) {
                                eq = false;
                            }
                        }
                    }
                    if (eq && !fixed[i + j]) {
                        last_changable = i + j;
                    }
                }
                if (eq) {
                    if (last_changable < 0) { return ""; }
                    ans[last_changable] = 'b';
                }
            }
        }
        return ans;
    }
};

static void test(string&& str1, string&& str2) {
    cout << Solution().generateString(str1, str2) << endl;
}

int main() {
    test("TFTF", "ab");
    test("TFTF", "abc");
    test("F", "d");
    return 0;
}
