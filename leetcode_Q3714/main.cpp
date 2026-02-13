#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>

using namespace std;
class Solution {
public:

    static int solve1(const string& s) {
		const auto n = size(s);
        int longest = 0;
		int streak = 0;
        char current = 0;
        for (auto&& c : s) {
            if (current == c) {
                streak++;
            }
            else {
                current = c;
                streak = 1;
            }
            longest = max(longest, streak);
        }
        return longest;
    }

    static int solve2(size_t n, const vector<vector<long long>>& prefix_sumss, int index1, int index2) {
        int longest = 0;
        const auto index_ignore = 3 - index1 - index2;
        const auto& ignores = prefix_sumss[index_ignore];
        const auto& p1 = prefix_sumss[index1];
        const auto& p2 = prefix_sumss[index2];
        map<int, int> mp{ {0,-1} };
        for (int i = 0; i < n; i++) {
            if (ignores[i] != ignores[i + 1]) {
                mp.clear();
                mp.insert({ p1[i] - p2[i], i });
            }
            else {
                const auto diff = p1[i + 1] - p2[i + 1];
                auto it = mp.find(diff);
                if (it == cend(mp)) {
                    mp.insert({ diff, i });
                }
                else {
                    const auto dist = i - it->second;
                    longest = max(longest, dist);
                }
            }
        }
        return longest;
    }

    static int solve3(size_t n, const vector<vector<long long>>& prefix_sumss) {
        int longest = 0;
        const auto& p1 = prefix_sumss[0];
        const auto& p2 = prefix_sumss[1];
        const auto& p3 = prefix_sumss[2];
        map<pair<int, int>, int> mp{ {{0,0},-1} };
        for (int i = 0; i < n; i++) {
            const auto diff1 = p1[i + 1] - p2[i + 1];
            const auto diff2 = p1[i + 1] - p3[i + 1];
            const auto key = make_pair(diff1, diff2);
            auto it = mp.find(key);
            if (it == cend(mp)) {
                mp.insert({ key, i });
            }
            else {
                const auto dist = i - it->second;
                longest = max(longest, dist);
            }
        }
        return longest;
    }


    int longestBalanced(string s) {
        const auto n = size(s);
        vector<vector<long long>> prefix_sumss(3, vector<long long>(n + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                prefix_sumss[j][i + 1] = prefix_sumss[j][i] + (s[i] == static_cast<char>(j + 'a') ? 1LL : 0LL);
            }
        }
        int longest = solve1(s);
        longest = max(longest, solve2(n, prefix_sumss, 0, 1));
        longest = max(longest, solve2(n, prefix_sumss, 0, 2));
        longest = max(longest, solve2(n, prefix_sumss, 1, 2));
        longest = max(longest, solve3(n, prefix_sumss));
        return longest;
    }
};

static void test(string&& s) {
    cout << Solution().longestBalanced(s) << endl;
}
int main() {
    test("abcbc");
    test("abbac");
    test("aabcc");
    test("aba");
    return 0;
}