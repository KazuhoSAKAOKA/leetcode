#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <climits>
#include <cassert>
#include <tuple>
#include <chrono>
#include <optional>
#include <queue>
#include <memory>
#include <random>
#include <exception>
#include <functional>
#include <ranges>
#include <iomanip>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        const auto n = size(nums);
        map<pair<long long, long long>, bool> pair_index_map;
        map<int, long long> num_map;
        int reverse_count = 0;
        for (int i = 0; i < n - 1; i++) {
            auto sorted = nums[i] <= nums[i + 1];
            if (!sorted) {
                reverse_count++;
            }
            pair_index_map.insert({ make_pair(nums[i] + nums[i + 1], i), sorted });
            num_map.insert({ i,nums[i] });
        }
        num_map.insert({ static_cast<int>(n - 1),nums[n - 1] });

        int op_count = 0;

        while (reverse_count > 0) {
            auto it = begin(pair_index_map);
            const auto [cur_sum, index] = it->first;
            const auto sorted = it->second;
            if (!sorted) {
                reverse_count--;
            }
            pair_index_map.erase(it);
            
            const auto it1 = num_map.find(index);
            const auto it2 = next(it1);
            const auto num1 = it1->second;
            const auto num2 = cur_sum - num1;
            if (it1 != begin(num_map)) {
                auto it_prev = prev(it1);
                const auto prev_num = it_prev->second;
                const auto past_sum = prev_num + num1;
                const auto it_prev_sum = pair_index_map.find({ past_sum, it_prev->first });
                const auto prev_sorted = it_prev_sum->second;
                pair_index_map.erase(it_prev_sum);
                const auto prev_new_sum = prev_num + cur_sum;
                const auto prev_new_sorted = prev_num <= cur_sum;
                pair_index_map.insert({ {prev_new_sum, it_prev->first}, prev_new_sorted });
                if (prev_sorted != prev_new_sorted) {
                    if (prev_sorted) {
                        reverse_count++;
                    }
                    else {
                        reverse_count--;
                    }
                }
            }

            const auto it_next = next(it1, 2);
            if (it_next != end(num_map)) {
                const auto next_num = it_next->second;
                const auto past_sum = next_num + num2;
                const auto it_next_sum = pair_index_map.find({ past_sum, it2->first });
                const auto next_sorted = it_next_sum->second;
                pair_index_map.erase(it_next_sum);
                const auto next_new_sum = next_num + cur_sum;
                const auto next_new_sorted = cur_sum <= next_num;
                pair_index_map.insert({ {next_new_sum, it1->first}, next_new_sorted });
                if (next_sorted != next_new_sorted) {
                    if (next_sorted) {
                        reverse_count++;
                    }
                    else {
                        reverse_count--;
                    }
                }
            }
            it1->second = cur_sum;
            num_map.erase(it2);

            op_count++;
        }
        return op_count;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().minimumPairRemoval(nums) << endl;
}

int main()
{
    test(get_list_int("[2,2,-1,3,-2,2,1,1,1,0,-1]"));

    test(get_list_int("[5,2,3,1]"));
    test(get_list_int("[1,2,2]"));
    return 0;
}