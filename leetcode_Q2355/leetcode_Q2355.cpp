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
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    long long maximumBooks(vector<int>& books) {
        const int n = size(books);
        vector<long long> dp(n);
        long long max_value = 0LL;
        vector<int> slopes;

        auto cal_sum = [&](int l, int r) {
            long long cnt = min(books[r], r - l + 1);
            return (2LL * books[r] - (cnt - 1)) * cnt / 2;
            };

        dp[0] = books[0];
        max_value = dp[0];

        slopes.push_back(0);
        for (int i = 1; i < n; i++) {
            if (books[i - 1] < books[i]) {
                dp[i] = dp[i - 1] + books[i];
            }
            else {
                while (!slopes.empty() && books[slopes.back()] - slopes.back() >= books[i] - i) {
                    slopes.pop_back();
                }
                if (slopes.empty()) {
                    dp[i] = cal_sum(0, i);
                }
                else {
                    dp[i] = dp[slopes.back()] +  cal_sum(slopes.back() + 1, i);
                }
            }

            max_value = max(max_value, dp[i]);
            slopes.push_back(i);
        }


        return max_value;
    }
};

static void test(vector<int>&& books) {
    cout << Solution().maximumBooks(books) << endl;
}

int main() {
    //test(get_list_int("[8,5,2,7,9]"));
    //test(get_list_int("[7,0,3,4,5]"));
    test(get_list_int("[8,2,3,7,3,4,0,1,4,3]"));
    return 0;
}
