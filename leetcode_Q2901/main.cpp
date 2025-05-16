#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    static bool is_hamming_distance_1(const string& a, const string& b) {
        if (size(a) != size(b)) { return false; }
        bool exist = false;
        for (int i = 0; i < size(a); i++) {
            if (a[i] != b[i]) {
                if (exist) { return false; }
                exist = true;
            }
        }
        return exist;
    }
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
        const auto n = size(words);
        vector<int> dp(n, 1);
        vector<int> froms(n, -1);
        dp[0] = 1;
        int max_len = 1;
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (groups[j] != groups[i] && is_hamming_distance_1(words[i], words[j])) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        froms[i] = j;
                    }
                }
            }
            max_len = max(max_len, dp[i]);
        }

        vector<string> ans;
        ans.reserve(max_len);
        for (int i = n - 1; i >= 0; i--) {
            if (max_len == dp[i]) {
                ans.emplace_back(words[i]);
                int index = froms[i];
                while (index>=0) {
                    ans.emplace_back(words[index]);
                    index = froms[index];
                }
                break;
            }
        }
        return vector<string>(crbegin(ans), crend(ans));
    }
};

void test(vector<string>&& words, vector<int>&& groups) {
    output(Solution().getWordsInLongestSubsequence(words, groups));
}
int main() {
    test(get_list_str(R"(["bab","dab","cab"])"), get_list_int("[1,2,2]"));
    test(get_list_str(R"(["a","b","c","d"])"), get_list_int("[1,2,3,4]"));
    return 0;
}