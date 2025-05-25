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
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        vector<int> freqs(26);
        unordered_map<char, unordered_map<char, size_t>> diff_map;
        int diffs = 0;
        for (auto&& word : words) {
            if (word[0] == word[1]) {
                freqs[word[0] - 'a']++;
            }
            else {
                auto it = diff_map.find(word[1]);
                if (it != end(diff_map)) {
                    auto it2 = it->second.find(word[0]);
                    if (it2 != end(it->second) && it2->second > 0) {
                        it2->second--;
                        diffs += 2;
                        continue;
                    }
                }
                diff_map[word[0]][word[1]]++;
            }
        }
        bool exist_odd = false;
        int even_count = 0;
        for (auto&& freq : freqs) {
            if (freq % 2 == 1) {
                exist_odd = true;
            }
            even_count += freq / 2;
        }

        return 4 * even_count + 2 * diffs + (exist_odd ? 2 : 0);
    }
};
void test(vector<string>&& words) {
    cout << Solution().longestPalindrome(words) << endl;
}
int main() {
    test(get_list_str(R"(["nn","nn","hg","gn","nn","hh","gh","nn","nh","nh"])"));
    test(get_list_str(R"(["lc","cl","gg"])"));
    test(get_list_str(R"(["ab","ty","yt","lc","cl","ab"])"));
    test(get_list_str(R"(["cc","ll","xx"])"));
    return 0;
}