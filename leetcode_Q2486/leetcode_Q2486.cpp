// leetcode_Q2486.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int appendCharacters(string s, string t) {
        int t_index = 0;
        for (auto&& c : s) {
            if (t[t_index] == c) {
                t_index++;
                if (t_index == t.size()) {
                    break;
                }
            }
        }
        return t.size() - t_index;
    }
};

void test(string&& s, string&& t) {
    cout << Solution().appendCharacters(s, t) << endl;
}

int main()
{
    test("coaching", "coding");
    test("abcde", "a");
    test("z", "abcde");
}