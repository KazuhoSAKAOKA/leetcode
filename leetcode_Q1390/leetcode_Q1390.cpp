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

    static int get_sum_of_4divisors(int n, unordered_map<int,int>& memo) {
        auto it = memo.find(n);
        if (it != cend(memo)) {
            return it->second;
        }
        std::vector<int> divisors;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) {
                    divisors.push_back(n / i);
                    if (size(divisors) > 4) { return 0; }
                }
            }
        }
        if (size(divisors) == 4) {
            return memo[n] = accumulate(cbegin(divisors), cend(divisors), 0);
        }
        else {
            return memo[n] = 0;
        }
    }

    int sumFourDivisors(vector<int>& nums) {
        unordered_map<int, int> memo;
        int total = 0;
        for (auto&& num : nums) {
            total += get_sum_of_4divisors(num, memo);
        }
        return total;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().sumFourDivisors(nums) << endl;
}

int main()
{
    test(get_list_int("[21,4,7]"));
    test(get_list_int("[21,21]"));
    test(get_list_int("[1,2,3,4,5]"));
    return 0;
}