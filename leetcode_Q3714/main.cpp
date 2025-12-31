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
    int longestBalanced(string s) {
        const auto n = size(s);
        int longest = 0;
        int streak = 0;
        char cur_c;
        for (auto&& c : s) {
            if (cur_c != c) {
                cur_c = c;
                streak = 1;
            }
            else {
                streak++;
            }
            longest = max(longest, streak);
        }

        vector<map<int, int>> prefixess(3);
        for (int i = 0; i < n; i++) {
            const auto index = s[i] - 'a';
            auto& prefix_map = prefixess[index];
            auto it = 
        }





        return 0;
    }
};

static void test(string&& s) {
    cout << Solution().longestBalanced(s) << endl;
}
int main() {
	return 0;
}