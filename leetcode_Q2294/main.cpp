#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        int count = 0;
        auto cur_it = cbegin(nums);
        while (cur_it != cend(nums)) {
            count++;
            const auto limit = *cur_it + k;
            cur_it = upper_bound(cur_it, cend(nums), limit);
        }
        return count;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().partitionArray(nums, k) << endl;
}
int main() {

	return 0;
}