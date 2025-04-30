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

    static bool is_digit_even(int num) {
        if (num == 0) { return false; }
        int len = 0;
        int cur(num);
        while (cur > 0) {
            cur /= 10;
            len++;
        }
        return len % 2 == 0;
    }

    int findNumbers(vector<int>& nums) {
        const int total_count = count_if(cbegin(nums), cend(nums), is_digit_even);
        return total_count;
    }
};

int main() {
	return 0;
}