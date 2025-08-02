#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    inline static size_t get_count(const unordered_map<int, size_t>& mp, int num) {
        auto it = mp.find(num);
        return it == cend(mp) ? 0 : it->second;
    }

    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, size_t> freq1;
        unordered_map<int, size_t> freq2;
        unordered_set<int> alls;
        int min_item = INT_MAX;
        for (auto&& num : basket1) {
            freq1[num]++;
            alls.insert(num);
            min_item = min(min_item, num);
        }
        for (auto&& num : basket2) {
            freq2[num]++;
            alls.insert(num);
            min_item = min(min_item, num);
        }
        map<int, size_t> req_swaps_1to2;
        map<int, size_t> req_swaps_2to1;
        size_t total_count = 0;
        for (auto&& num : alls) {
            const auto count1 = get_count(freq1, num);
            const auto count2 = get_count(freq2, num);
            if ((count1 + count2) % 2 != 0) {
                return -1;
            }
            if (count1 == count2) { continue; }
            const auto dif = max(count1, count2) - min(count1, count2);
            const auto swap_req = dif / 2;
            total_count += swap_req;
            if (count1 < count2) {
                req_swaps_2to1.insert({ num, swap_req });
            }
            else {
                req_swaps_1to2.insert({ num, swap_req });
            }
        }
        size_t remain_count = total_count / 2;
        long long min_cost = 0;
        auto it1to2 = cbegin(req_swaps_1to2);
        auto it2to2 = cbegin(req_swaps_2to1);
        size_t op_count = 0;
        while (remain_count > 0) {
            const auto& [num1, count1] = *it1to2;
            const auto& [num2, count2] = *it2to2;
            const auto cur_count = min(remain_count, num1 < num2 ? count1 : count2);
            const auto cur_num = min(num1, num2);
            const auto c = min(cur_num, min_item * 2);
            min_cost += cur_count * c;
            remain_count -= cur_count;
            if (num1 < num2) {
                ++it1to2;
            }
            else {
                ++it2to2;
            }
        }
        return min_cost;
    }
};

static void test(vector<int>&& basket1, vector<int>&& basket2) {
    cout << Solution().minCost(basket1, basket2) << endl;
}
int main() {
    test(get_list_int("[84,80,43,8,80,88,43,14,100,88]"), get_list_int("[32,32,42,68,68,100,42,84,14,8]"));
    test(get_list_int("[4,2,2,2]"), get_list_int("[1,4,1,2]"));
    test(get_list_int("[2,3,4,1]"), get_list_int("[3,2,5,1]"));
    return 0;
}