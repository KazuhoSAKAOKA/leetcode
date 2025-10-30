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
    int minNumberOperations(vector<int>& target) {
        const int n = size(target);
        int total = 0;
        vector<int> monost;

        auto get_cost = [&](int val)->int {
            int count = 0;
            int prev_val = val;
            while (!monost.empty() && target[monost.back()] > val) {
                const auto cur_height = target[monost.back()];
                monost.pop_back();
                const auto base_height = monost.empty() ? val : max(target[monost.back()], val);
                count += cur_height - base_height;
            }
            return count;
            };

        for (int i = 0; i < n; i++) {
            const auto val = target[i];
            total += get_cost(target[i]);
            if (monost.empty() || target[monost.back()] < val) {
                monost.push_back(i);
            }
        }
        total += get_cost(0);
        return total;
    }
};

static void test(vector<int>&& target) {
    cout << Solution().minNumberOperations(target) << endl;
}
int main() {
    test(get_list_int("[1,2,3,2,1]"));
    test(get_list_int("[3,1,1,2]"));
    test(get_list_int("[3,1,5,4,2]"));
    return 0;
}