// leetcode_Q0678.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;


class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left_parent_indexes;
        stack<int> astarisk_indexes;

        for (int i = 0; i < s.size(); i++) {
            const auto c = s[i];
            if (c == '(') {
                left_parent_indexes.push(i);
            }
            else if (c == '*') {
                astarisk_indexes.push(i);
            }
            else if (c == ')') {
                if (left_parent_indexes.empty() && astarisk_indexes.empty()) {
                    return false;
                }
                if (!left_parent_indexes.empty()) {
                    left_parent_indexes.pop();
                }
                else {
                    astarisk_indexes.pop();
                }
            }
            else {
                return false;
            }
        }
        while (!left_parent_indexes.empty()) {
            if (astarisk_indexes.empty()) { return false; }
            if (left_parent_indexes.top() > astarisk_indexes.top()) { return false; }
            astarisk_indexes.pop();
            left_parent_indexes.pop();
        }
        return true;
    }
};

void test(string&& s) {
    cout << Solution().checkValidString(s) << endl;
}

int main()
{
    test("()");
    test("(*)");
    test("(*))");
}