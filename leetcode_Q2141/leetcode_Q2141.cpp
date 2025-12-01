#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

template <typename T = long long>
T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
    while (abs(ng - ok) > 1) {
        const auto mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        }
        else {
            ng = mid;
        }
    }
    return ok;
}
class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        const auto m = size(batteries);
        if (m < n) { return 0LL; }
        long long total = 0LL;
        long long min_val = LLONG_MAX;
        for (int i = 0; i < m; i++) {
            total += batteries[i];
            min_val = min(min_val, static_cast<long long>(batteries[i]));
        }
        const long long ok = min_val;
        const long long ng = (total / n) + 1;

        const auto ans = binary_search_meguru<long long>(ok, ng,
            [&](long long v)->bool {
                long long r = 0;
                for (auto b : batteries) {
                    r += min(v, static_cast<long long>(b));
                }
                return r >= n * v;
            });

        return ans;
    }
};

static void test(int n, vector<int>&& batteries) {
    cout << Solution().maxRunTime(n, batteries) << endl;
}

int main(){
    test(3, get_list_int("[10,10,6,9,3]"));
    test(9, get_list_int("[18,54,2,53,87,31,71,4,29,25]"));
    test(3, get_list_int("[10,10,3,5]"));
    test(2, get_list_int("[3,3,3]"));
    test(2, get_list_int("[1,1,1,1]"));

    return 0;
}