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
    vector<string> divideString(string s, int k, char fill) {
        vector<string> ans;
        ans.reserve((size(s) + k - 1) / k);
        int i = 0;
        const auto count = size(s) / k;
        while (i < count) {
            ans.emplace_back(s.substr(i * k, k));
            i++;
        }
        if (size(s) % k != 0) {
            string temp = s.substr(k * count);
            const auto remain = k - size(temp);
            temp.append(remain, fill);
            ans.emplace_back(temp);
        }
        return ans;
    }
};

void test(string&& s, int k, char fill) {
    output(Solution().divideString(s, k, fill));
}
int main() {
    test("ctoyjrwtngqwt", 8, 'x');
    test("abcdefghij", 3, 'x');
    test("abcdefghi", 3, 'x');
    return 0;
}