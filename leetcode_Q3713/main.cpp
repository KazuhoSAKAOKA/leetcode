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
        vector<vector<int>> prefix_sumss(n + 1, vector<int>(26));
        for (int i = 0; i < n; i++) {
            prefix_sumss[i + 1][s[i] - 'a']++;
            for (int j = 0; j < 26; j++) {
                prefix_sumss[i + 1][j] += prefix_sumss[i][j];
            }
        }
        int longest = 1;
        for (int i = 0; i < n; i++) {
            for (int len = 2; i + len <= n; len++) {
                auto check = [&]()->bool {
                    int exist_count = -1;
                    for (int j = 0; j < 26; j++) {
                        const auto appears = prefix_sumss[i + len][j] - prefix_sumss[i][j];
                        if (appears != 0) {
                            if (exist_count < 0) {
                                exist_count = appears;
                            }
                            else {
                                if (exist_count != appears) {
                                    return false;
                                }
                            }
                        }
                    }
                    return true;
                    };

                if (check()) {
                    longest = max(longest, len);
                }
            }
        }

        return longest;
    }
};

static void test(string&& s) {
    cout << Solution().longestBalanced(s) << endl;
}
int main() {
    test("kl");
    test("abbac");
    test("zzabccy");
    test("aba");
    return 0;
}