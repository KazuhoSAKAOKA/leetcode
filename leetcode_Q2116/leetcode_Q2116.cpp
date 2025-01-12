// leetcode_Q2116.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    bool canBeValid(string s, string locked) {
        if (size(s) % 2 == 1) { return false; }
        stack<int> locked_lefts;
        stack<int> frees;
        for (int i = 0; i < size(s); i++) {
            if (locked[i] == '1') {
                if (s[i] == '(') {
                    locked_lefts.push(i);
                }
                else {
                    //s[i] == ')'
                    if (locked_lefts.empty() && frees.empty()) {
                        return 0;
                    }
                    if (!locked_lefts.empty()) {
                        locked_lefts.pop();
                    }
                    else {
                        frees.pop();
                    }
                }
            }
            else {
                frees.push(i);
            }
        }
        while (!locked_lefts.empty()) {
            if (frees.empty() || frees.top() < locked_lefts.top()) {
                return false;
            }
            locked_lefts.pop();
            frees.pop();
        }
        return true;
    }
};

void test(string&& s, string&& locked) {
    cout << Solution().canBeValid(s, locked) << endl;
}

int main()
{
    test("))()))", "010100");
    test("()()", "0000");
    test(")", "0");
    return 0;
}