#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    static bool check_candidates(const vector<unordered_set<char>>& new_line_candidate, int index,string& current, function<bool(const string&)> check) {
        if (index == size(new_line_candidate)) {
            return check(current);
        }
        for (auto&& c : new_line_candidate[index]) {
            current += c;
            make_candidates(new_line_candidate, index + 1, current, candidates);
            current.pop_back();
        }
    }

    static bool dfs(const unordered_map<string, unordered_set<char>>& allowed_map, const string& line) {
        const auto len = size(line);
        if (len == 1) { return true; }


        vector<unordered_set<char>> new_line_candidate;
        for (int j = 0; j < len - 1; j++) {
            auto key = line.substr(j, 2);
            auto it = allowed_map.find(key);
            if (it == cend(allowed_map)) {
                return false;
            }
            new_line_candidate.emplace_back(it->second);
        }

        string work;
        return check_candidates(new_line_candidate, 0, work, candidates);
        for (auto&& candidate : candidates) {
            if (dfs(allowed_map, candidate)) {
                return true;
            }
        }
        return false;
    }

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        const auto n = size(bottom);
        unordered_map<string, unordered_set<char>> allowed_map;
        for (auto&& allow : allowed) {
            allowed_map[allow.substr(0, 2)].insert(allow[2]);
        }


        return dfs(allowed_map, bottom);
    }
};

static void test(string&& bottom, vector<string>&& allowed) {
    cout << Solution().pyramidTransition(bottom, allowed) << endl;
}

int main()
{
    test("ABBBBA", get_list_str(R"(["ACA","ACF","ACE","ACD","ABA","ABF","ABE","ABD","FCA","FCF","FCE","FCD","FBA","FBF","FBE","FBD","ECA","ECF","ECE","ECD","EBA","EBF","EBE","EBD","DCA","DCF","DCE","DCD","DBA","DBF","DBE","DBD","CAA","CAF","CAE","CAD","CFA","CFF","CFE","CFD","CEA","CEF","CEE","CED","CDA","CDF","CDE","CDD","BAA","BAF","BAE","BAD","BFA","BFF","BFE","BFD","BEA","BEF","BEE","BED","BDA","BDF","BDE","BDD","CCA","CCF","CCE","CCD","CBA","CBF","CBE","CBD","BCA","BCF","BCE","BCD","BBA","BBF","BBE","BBD","CCC","CCB","CBC","CBB","BCC","BCB","BBC","BBB"])"));
    test("BCD", get_list_str(R"(["BCC","CDE","CEA","FFF"])"));
    test("AABA", get_list_str(R"(["AAA","AAB","ABA","ABB","BAC"])"));
    test("AAAA", get_list_str(R"(["AAB","AAC","BCD","BBE","DEF"])"));
    return 0;
}