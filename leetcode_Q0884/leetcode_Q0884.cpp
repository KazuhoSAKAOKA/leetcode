// leetcode_Q0884.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:


    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, size_t> freq_map;
        for (auto&& s : { s1,s2, }) {
            size_t index = 0;
            while (index < size(s)) {
                const auto pos = s.find(' ', index);
                if (pos == string::npos) {
                    freq_map[s.substr(index)]++;
                    break;
                }
                freq_map[s.substr(index, pos - index)]++;
                index = pos + 1;
            }
        }
        vector<string> ans;
        for (auto&& [k, v] : freq_map) {
            if (v == 1) {
                ans.emplace_back(k);
            }
        }

        return ans;
    }
};

void test(string&& s1, string&& s2) {
    output(Solution().uncommonFromSentences(s1, s2));
}

int main()
{
    test("this apple is sweet", "this apple is sour");
    test("apple apple", "banana");
    return 0;
}