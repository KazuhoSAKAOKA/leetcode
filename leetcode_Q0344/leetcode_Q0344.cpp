// leetcode_Q0344.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0;
        int r = s.size() - 1;
        while (l < r) {
            swap(s[l], s[r]);
            l++;
            r--;
        }
    }
};


void test(vector<char>&& s) {
    Solution().reverseString(s);
    string ans;
    for (auto&& c : s) {
        ans += c;
    }
    cout << ans << endl;
}


int main()
{
    test(get_list_char(R"(["h","e","l","l","o"])"));
    test(get_list_char(R"(["H","a","n","n","a","h"])"));
}