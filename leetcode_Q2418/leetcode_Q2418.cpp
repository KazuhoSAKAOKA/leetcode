// leetcode_Q2418.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        map<int, string> height_key_map;
        for (size_t i = 0; i < names.size(); i++) {
            const auto [_, r] = height_key_map.insert({ heights[i], names[i] });
            if (!r) {
                cerr << "unexpected data" << endl;
                return vector<string>();
            }
        }
        vector<string> ans;
        ans.reserve(names.size());
        for (auto it = crbegin(height_key_map); it != crend(height_key_map); ++it) {
            ans.push_back(it->second);
        }
        return ans;
    }
};

void test(vector<string>&& names, vector<int>&& heights) {
    const auto ans = Solution().sortPeople(names, heights);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(get_list_str(R"(["Mary","John","Emma"])"), get_list_int("[180,165,170]"));
    test(get_list_str(R"(["Alice","Bob","Bob"])"), get_list_int("[155,185,150]"));
    return 0;
}