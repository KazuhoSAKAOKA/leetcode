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
using namespace std;
class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int max_freq = 0;
        for (auto&& num : nums) {
            freq[num]++;
            max_freq = max(max_freq, freq[num]);
        }
        return max_freq * k <= size(nums);
    }
};

static void test(vector<int>&& nums, int k) {

}

int main() {
	return 0;
}