// leetcode_Q2904.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        const auto n = size(s);
        vector<int> prefix_sums(n + 1);
        for (size_t i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + (s[i] == '1' ? 1 : 0);
        }
        if (prefix_sums.back() < k) { return ""; }

        map<size_t, vector<size_t>> subarrs;

        for (size_t i = 0; i < n; i++) {
            if (prefix_sums.back() < prefix_sums[i] + k) {
                break;
            }
            auto begin_it = next(cbegin(prefix_sums), i);
            auto it = lower_bound(begin_it, cend(prefix_sums), prefix_sums[i] + k);
            auto dist = distance(begin_it, it);
            subarrs[dist].push_back(i);
        }

        set<string> substrs;
        auto& [len, indexes] = *cbegin(subarrs);
        for (auto&& index : indexes) {
            substrs.insert(s.substr(index, len));
        }

        return *cbegin(substrs);
    }
};

static void test(string&& s, int k) {
    cout << Solution().shortestBeautifulSubstring(s, k) << endl;
}

int main() {
    test("100011001", 3);
    test("1011", 2);
    test("000", 1);
    return 0;
}
