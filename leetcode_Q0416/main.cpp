#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

class Solution {
public:

    static bool rec(const vector<int>& nums, int index, int sums1, int sums2) {
        if (size(nums) == index) {
            return sums1 == sums2;
        }

        if (rec(nums, index + 1, sums1 + nums[index], sums2)) {
            return true;
        }
        return rec(nums, index + 1, sums1, sums2 + nums[index]);
    }


    static bool tle(const vector<int>& nums) {
        return rec(nums, 0, 0, 0);
    }

    bool canPartition(vector<int>& nums) {
        const auto total = accumulate(cbegin(nums), cend(nums), 0LL, [](long long a, long long b) { return a + b; });
        if (total % 2 != 0) {
            return false;
        }
        const auto half = total / 2;
        set<long long> before;
        if (nums[0] == half) { return true; }
        before.insert(nums[0]);
        for (int i = 1; i < size(nums); i++) {
            set<long long> current(before);
            for (auto&& bef_val : before) {
                const auto cur_val = bef_val + static_cast<long long>(nums[i]);
                if (cur_val == half) {
                    return true;
                }
                current.insert(cur_val);
            }
            before = current;
        }
        return false;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().canPartition(nums) << endl;
}

int main() {
	return 0;
}