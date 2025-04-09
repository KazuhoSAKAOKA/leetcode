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
    int minOperations(vector<int>& nums, int k) {
        vector<bool> exists(100 + 1);
        for (auto&& num : nums) {
            if (num < k) {
                return -1;
            }
            exists[num] = true;
        }
        int count = 0;
        for (int i = k + 1; i < 101; i++) {
            if (exists[i]) {
                count++;
            }
        }
        return count;
    }
};
int main() {
	return 0;
}