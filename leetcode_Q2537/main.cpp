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
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long count = 0LL;

        unordered_map<int, int> freqs;

        auto check_left = [&](int left, int cur_count)->bool {
            const auto it = freqs.find(nums[left]);
            const auto remain = cur_count - (it->second - 1);
            return remain >= k;
            };

        long long l = 0;
        int cur_pair_count = 0;
        for (int r = 0; r < size(nums); r++) {
            auto it = freqs.find(nums[r]);
            if (it == cend(freqs)) {
                freqs.insert({ nums[r],1 });
            }
            else {
                cur_pair_count += it->second;
                it->second++;
            }

            while (check_left(l, cur_pair_count)) {
                const auto remove_pairs = --freqs[nums[l]];
                cur_pair_count -= remove_pairs;
                l++;
            }

            if (k <= cur_pair_count) {
                count += l + 1;
            }
        }

        return count;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().countGood(nums, k) << endl;
}
int main() {
    test(get_list_int("[1,1,1,1,1]"), 10);
    test(get_list_int("[3,1,4,3,2,2,4]"), 2);
	return 0;
}