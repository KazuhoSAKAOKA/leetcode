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
    static string get_first_phrases(const string& str) {
        const auto e = str.find_first_of(' ');
        if (e == string::npos) {
            return str;
        }
        return str.substr(0, e);
    }
    static string get_last_phrases(const string& str) {
        const auto s = str.find_last_of(' ');
        if (s == string::npos) {
            return str;
        }
        return str.substr(s + 1);
    }

    static string combine(const string& prestr, const string& combstring, const string poststr) {
        return size(combstring) == size(poststr) ?
            prestr
            : prestr + poststr.substr(size(combstring));
    }

    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
        const auto n = size(phrases);
        set<string> ans;
        unordered_map<string, vector<int>> first_phrases_map;
        unordered_map<string, vector<int>> last_phrases_map;
        for (int i = 0; i < n; i++) {
            first_phrases_map[get_first_phrases(phrases[i])].emplace_back(i);
            last_phrases_map[get_last_phrases(phrases[i])].emplace_back(i);
        }
        for (auto&& [last_phrase, pre_indexes] : last_phrases_map) {
            const auto it = first_phrases_map.find(last_phrase);
            if (it != cend(first_phrases_map)) {
                const auto& post_indexes = it->second;
                for (auto&& preindex : pre_indexes) {
                    for (auto&& postindex : post_indexes) {
                        if (preindex != postindex) {
                            ans.insert(combine(phrases[preindex], last_phrase, phrases[postindex]));
                        }
                    }
                }
            }
        }
        return vector<string>(cbegin(ans), cend(ans));
    }
};

static void test(vector<string>&& phrases) {
    output(Solution().beforeAndAfterPuzzles(phrases));
}

int main() {
    test(get_list_str(R"(["writing code","code rocks"])"));
    test(get_list_str(R"(["mission statement","a quick bite to eat","a chip off the old block","chocolate bar","mission impossible","a man on a mission","block party","eat my words","bar of soap"])"));
    test(get_list_str(R"(["a","b","a"])"));
    return 0;
}