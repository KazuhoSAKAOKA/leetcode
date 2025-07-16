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
	static inline bool is_even(int n) {
		return n % 2 == 0;
	}
	int maximumLength(vector<int>& nums) {
		if (size(nums) < 2) { return 0; }
		int even_count = 0;
		int odd_count = 0;
		int alternate_count = 1;
		bool cur_even = false;
		if (is_even(nums[0])) {
			even_count++;
			cur_even = true;
		}
		else {
			odd_count++;
		}

		for (int i = 1; i < size(nums); i++) {
			if (is_even(nums[i])) {
				even_count++;
				if (!cur_even) {
					alternate_count++;
				}
				cur_even = true;
			}
			else {
				odd_count++;
				if (cur_even) {
					alternate_count++;
				}
				cur_even = false;
			}
		}

		return max(max(even_count, odd_count), alternate_count);
	}
};

int main() {
	return 0;
}