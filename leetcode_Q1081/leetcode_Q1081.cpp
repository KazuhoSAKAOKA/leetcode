#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        const auto n = size(s);
        map<char, vector<int>> pos_map;
        for (int i = 0; i < n; i++) {
            pos_map[s[i]].push_back(i);
        }
        set<char> candidates;
        for (auto&& [c, _] : pos_map) {
            candidates.insert(c);
        }

        auto check = [](char c, const set<char>& candidates, const map<char, vector<int>>& pmap, int& base_pos)->bool {
            const auto& poss1 = pmap.at(c);
            auto most_left_it = lower_bound(cbegin(poss1), cend(poss1), base_pos);
            if (most_left_it == cend(poss1)) {
                return false;
            }
            const auto most_left = *most_left_it;
            for (auto&& c1 : candidates) {
                if (c1 == c) { continue; }
                const auto& poss2 = pmap.at(c1);
                if (upper_bound(cbegin(poss2), cend(poss2), most_left) == cend(poss2)) {
                    return false;
                }
            }
            base_pos = most_left;
            return true;
            };

        string ans;

        int base_pos = 0;
        while (size(candidates) > 1) {
            for (auto&& c : candidates) {
                if (check(c, candidates, pos_map, base_pos)) {
                    ans += c;
                    candidates.erase(c);
                    break;
                }
            }
        }
        ans.push_back(*cbegin(candidates));

        return ans;
    }
};

static void test(string s) {
    cout << Solution().smallestSubsequence(s) << endl;
}

int main() {
    test("abcd");
    test("bcabc");
    test("cbacdcbc");
    return 0;
}
