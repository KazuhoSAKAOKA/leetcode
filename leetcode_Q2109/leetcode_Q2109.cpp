// leetcode_Q2109.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        string ans;
        ans.reserve(size(s) + size(spaces));

        auto it = cbegin(spaces);

        for (int i = 0; i < size(s); i++) {
            if (it != cend(spaces) && *it == i) {
                ans += ' ';
                ++it;
            }
            ans += s[i];
        }
        return ans;
    }
};

void test(string&& s, vector<int>&& spaces) {
    cout << Solution().addSpaces(s, spaces) << endl;
}

int main()
{
    test("LeetcodeHelpsMeLearn", get_list_int("[8,13,15]"));
    test("icodeinpython", get_list_int("[1,5,7,9]"));
    test("spacing", get_list_int("[0,1,2,3,4,5,6]"));
    return 0;
}