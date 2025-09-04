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
class Solution {
public:

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        const int n = size(s);
        if (n < size(a) || n < size(b)) {
            return{};
        }
        vector<int> prefix_sums(n + 1);
        for (int i = 0; i < size(s) - size(b) + 1; i++) {
            prefix_sums[i + 1] += prefix_sums[i];
            if (equal(cbegin(b), cend(b), next(cbegin(s), i))) {
                prefix_sums[i + 1]++;
            }
        }
        for (int i = size(s) - size(b) + 1; i < size(s); i++) {
            prefix_sums[i + 1] += prefix_sums[i];
        }
        vector<int> ans;
        for (int i = 0; i < size(s) - size(a) + 1; i++) {
            if (equal(cbegin(a), cend(a), next(cbegin(s), i))) {
                if (prefix_sums[min(n, i + k + 1)] - prefix_sums[max(0, i - k)] > 0) {
                    ans.emplace_back(i);
                }
            }
        }
        return ans;
    }
};
static void test(string&& s, string&& a, string&& b, int k) {
    output(Solution().beautifulIndices(s, a, b, k));
}
int main() {
    test("wl", "xjigt", "wl", 2);
    test("baccccab", "a", "b", 1);

    test("isawsquirrelnearmysquirrelhouseohmy", "my", "squirrel", 15);
    test("abcd", "a", "a", 4);
    return 0;
}