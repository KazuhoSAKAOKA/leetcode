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
    string decodeCiphertext(string encodedText, int rows) {
        const int len = size(encodedText);
        const int cols = len / rows;
        string ans;
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < min(rows, cols - i); j++) {
                ans.push_back(encodedText[(j * cols) + i + j]);
            }
        }
        while (!ans.empty() && ans.back() == ' ') {
            ans.pop_back();
        }
        return ans;
    }
};

static void test(string&& encodedText, int rows) {
    cout << Solution().decodeCiphertext(encodedText, rows) << endl;
}

int main() {
    test("ch   ie   pr", 3);
    test("iveo    eed   l te   olc", 4);
    test("coding", 1);
    return 0;
}
