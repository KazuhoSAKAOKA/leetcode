// leetcode_Q1508.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    int rangeSum(vector<int>& nums, int n, int left, int right) {
        vector<long long> subarray_sums;
        subarray_sums.reserve(n * (n + 1) / 2);
        for (int i = 0; i < n; i++) {
            long long total = 0;
            for (int j = i; j < n; j++) {
                total += nums[j];
                subarray_sums.push_back(total);
            }
        }
        sort(begin(subarray_sums), end(subarray_sums));
        const long long ans = accumulate(next(cbegin(subarray_sums), left - 1), next(cbegin(subarray_sums), right), 0,
            [](const long long a, const long long b) { return (a + b) % MODULO; });

        return ans;
    }
};

void test(vector<int>&& nums, int n, int left, int right) {
    cout << Solution().rangeSum(nums, n, left, right) << endl;
}

int main()
{
    test(get_list_int("[1,2,3,4]"), 4, 1, 5);
    test(get_list_int("[1,2,3,4]"), 4, 3, 4);
    test(get_list_int("[1,2,3,4]"), 4, 1, 10);
    return 0;
}
