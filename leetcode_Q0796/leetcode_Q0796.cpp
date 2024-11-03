// leetcode_Q0796.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        const auto l = size(s);
        for (int i = 0; i < l; i++) {
            string work = s.substr(i) + s.substr(0, i);
            if (work == goal) {
                return true;
            }
        }
        return false;
    }
};

void test(string&& s, string&& goal) {
    cout << Solution().rotateString(s, goal) << endl;
}

int main()
{
    test("abcde", "cdeab");
    test("abcde", "abced");
    return 0;
}