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
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
        vector<string> ans1;
        vector<string> ans2;
        int ans1_cur = 0;
        int ans2_cur = 1;
        for (int i = 0; i < size(words); i++) {
            if (ans1_cur != groups[i]) {
                ans1.emplace_back(words[i]);
                ans1_cur = groups[i];
            }

            if (ans2_cur != groups[i]) {
                ans2.emplace_back(words[i]);
                ans2_cur = groups[i];
            }
        }


        return size(ans1) < size(ans2) ? ans2 : ans1;
    }
};

int main() {
	return 0;
}