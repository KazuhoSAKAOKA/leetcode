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


    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        constexpr long long MODULO = 1e9 + 7;
        long long cur_value = 1;
        while (cur_value * 2 <= n) {
            cur_value *= 2;
        }
        vector<long long> nums;
        long long remain = n;
        while (remain > 0) {
            const auto count = remain / cur_value;
            nums.insert(end(nums), count, cur_value);
            remain -= count * cur_value;
            cur_value /= 2;
        }
        reverse(begin(nums), end(nums));
        const auto m = size(nums);
        //vector<long long> prefix_products(m + 1);
        //prefix_products[0] = 1LL;
        //for (int i = 0; i < m; i++) {
        //    prefix_products[i + 1] = (prefix_products[i] * nums[i]) % MODULO;
        //}

        vector<int> ans;
        ans.reserve(size(queries));

        for (auto&& q : queries) {
            long long v = 1;
            for (int i = q.front(); i <= q.back(); i++) {
                v *= nums[i];
                v %= MODULO;
            }
            //auto v = prefix_products[q.back() + 1] / prefix_products[q.front()];
            //v %= MODULO;
            ans.emplace_back(v);
        }

        return ans;
    }
};

static void test(int n, vector<vector<int>>&& queries) {
    output(Solution().productQueries(n, queries));
}
int main() {
    test(2, get_matrix_int("[[0,0]]"));
    test(15, get_matrix_int("[[0,1],[2,2],[0,3]]"));
    return 0;
}