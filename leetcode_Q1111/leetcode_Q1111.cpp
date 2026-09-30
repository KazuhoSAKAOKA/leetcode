
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
#include <bitset>
#include <sstream>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        const auto n = size(seq);
        vector<pair<size_t, int>> st;

        vector<int> ans(n);
        int cur_section = 0;
        for (size_t i = 0; i < n; i++) {
            if (seq[i] == '(') {
                st.push_back({ i, cur_section });
                cur_section = (cur_section + 1) % 2;
            }
            else {
                if (st.empty()) { throw runtime_error(""); }
                auto [index, color] = st.back();
                ans[index] = color;
                ans[i] = color;
                st.pop_back();
                if (!st.empty()) {
                    cur_section = (st.back().second + 1) % 2;
                }
            }
        }

        return ans;
    }
};

static void test(string&& seq) {
    output(Solution().maxDepthAfterSplit(seq));
}
int main() {
    test("(()())");
    test("()(())()");
    return 0;
}
