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
    int countCompleteSubarrays(vector<int>& nums) {
        unordered_set<int> distincts(cbegin(nums), cend(nums));
        const auto n = size(nums);
        const auto size_of_distincts = size(distincts);
        int count = 0;
        vector<int> freqs(2000 + 1);
        int cur_distincts = 0;

        int l = 0;
        for (int r = 0; r < n; r++) {
            freqs[nums[r]]++;
            if (freqs[nums[r]] == 1) {
                cur_distincts++;
            }

            while (l < r && cur_distincts == size_of_distincts && freqs[nums[l]] > 1) {
                freqs[nums[l]]--;
                if (freqs[nums[l]] == 0) {
                    cur_distincts--;
                }
                l++;
            }

            if (cur_distincts == size_of_distincts) {
                count += l + 1;
            }
        }
        return count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().countCompleteSubarrays(nums) << endl;
}
int main() {
	return 0;
}