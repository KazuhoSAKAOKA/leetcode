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

    template <typename T> 
    static pair<T, size_t> boyer_moore_majority_voting(const vector<T>& arr) {
        T candidate = arr[0];
        size_t votes = 1;
        for (int i = 1; i < size(arr); i++) {
            const auto& v = arr[i];
            if (votes == 0) {
                candidate = v;
                votes = 1;
            }
            else {
                if (v == candidate) {
                    votes++;
                }
                else {
                    votes--;
                }
            }
        }
        size_t count = count_if(cbegin(arr), cend(arr), [&](const T& v) { return v == candidate; });
        return { candidate, count };
    }


    int minimumIndex(vector<int>& nums) {
        //map<int, int> freq_map;
        //for (auto&& num : nums) {
        //    freq_map[num]++;
        //}
        //int max_freq = 0;
        //int max_num = 0;
        //for (auto&& [k, c] : freq_map) {
        //    if (max_freq < c) {
        //        max_num = k;
        //        max_freq = c;
        //    }
        //}
        const auto [max_num, total_count] = boyer_moore_majority_voting<int>(nums);

        int cur_left = 0;

        for (int i = 0; i < size(nums); i++) {
            if (nums[i] == max_num) {
                cur_left++;
                const auto cur_right = total_count - cur_left;
                if ((i + 1) / 2 < cur_left && (size(nums) - i - 1) / 2 < cur_right) {
                    return i;
                }
            }
        }
        return -1;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().minimumIndex(nums) << endl;
}
int main() {
    test(get_list_int("[1,2,2,2]"));
    test(get_list_int("[2,1,3,1,1,1,7,1,2,1]"));
    test(get_list_int("[3,3,3,3,7,2,2]"));
    return 0;
}