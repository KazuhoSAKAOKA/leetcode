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
    int numberOfBeams(vector<string>& bank) {
        int ans = 0;
        int prev = 0;
        for (auto&& line : bank) {
            const auto cur_count = static_cast<int>(count_if(cbegin(line), cend(line), [](char c) { return c == '1'; }));
            if (cur_count > 0) {
                ans += prev * cur_count;
                prev = cur_count;
            }
        }
        return ans;
    }
};

int main() {
	return 0;
}