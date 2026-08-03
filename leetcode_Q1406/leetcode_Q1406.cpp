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
#include "./../utility/TreeNodeUtil.h"
using namespace std;

class Solution {
public:

    static long long dfs(const vector<int>& stoneValue, int index, unordered_map<int, long long>& memo) {
        const auto n = size(stoneValue);
        if (index == n) {
            return 0;
        }
        auto it = memo.find(index);
        if (it != cend(memo)) {
            return it->second;
        }
        long long value = stoneValue[index] - dfs(stoneValue, index + 1, memo);
        if (index + 2 <= n) {
            value = max(value, stoneValue[index] + stoneValue[index + 1] - dfs(stoneValue, index + 2, memo));
            if (index + 3 <= n) {
                value = max(value, stoneValue[index] + stoneValue[index + 1] + stoneValue[index + 2] - dfs(stoneValue, index + 3, memo));
            }
        }
        memo.insert({ index,value });
        return value;

    }

    string stoneGameIII(vector<int>& stoneValue) {

        const string tie = "Tie";
        const string alice = "Alice";
        const string bob = "Bob";
        const int n = size(stoneValue);
        unordered_map<int, long long> memo;
        const auto r = dfs(stoneValue, 0, memo);
        if (r == 0) {
            return tie;
        }
        if (r > 0) {
            return alice;
        }
        return bob;
    }
};

static void test(vector<int>&& stoneValue) {
    cout << Solution().stoneGameIII(stoneValue) << endl;
}

int main() {
    test(get_list_int("[1,2,3,7]"));
    test(get_list_int("[1,2,3,-9]"));
    test(get_list_int("[1,2,3,6]"));
    return 0;
}
