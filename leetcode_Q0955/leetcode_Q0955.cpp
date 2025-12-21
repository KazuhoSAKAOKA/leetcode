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
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        const auto n = size(strs);
        const auto len = size(strs[0]);
        vector<bool> order_defined(n);
        auto check = [&](int index)->bool {
            for (int i = 1; i < n; i++) {
                if (!order_defined[i]){
                    if (strs[i - 1][index] > strs[i][index]) {
                        return true;
                    }
                }
            }
            return false;
            };
        int count = 0;
        for (int i = 0; i < len; i++) {
            if (check(i)) {
                count++;
            }
            else {
                for (int j = 1; j < n; j++) {
                    if (strs[j - 1][i] < strs[j][i]) {
                        order_defined[j] = true;
                    }
                }
            }
        }
        return count;
    }
};
static void test(vector<string>&& strs) {
    cout << Solution().minDeletionSize(strs) << endl;
}
int main()
{
    test(get_list_str(R"(["ca","bb","ac"])"));
    test(get_list_str(R"(["xc","yb","za"])"));
    test(get_list_str(R"(["zyx","wvu","tsr"])"));
    return 0;
}