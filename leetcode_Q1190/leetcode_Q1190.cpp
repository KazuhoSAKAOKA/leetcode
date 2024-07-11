// leetcode_Q1190.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:

    static string rec(const string& s, int& index) {
        stack<char> st;
        while (index < s.size() && s[index] != ')') {
            if (s[index] == '(') {
                index++;
                const auto inner = rec(s, index);
                for (auto&& c : inner) {
                    st.push(c);
                }
            }
            else {
                st.push(s[index]);
                index++;
            }
        }
        string reverse_string;
        reverse_string.reserve(st.size());
        while (!st.empty()) {
            reverse_string += st.top();
            st.pop();
        }
        index++;
        return reverse_string;
    }

    string reverseParentheses(string s) {
        string ans;
        ans.reserve(s.size());
        int index = 0;
        while (index < s.size()) {
            //'('があるまで探す
            while (index < s.size() && s[index] != '(') {
                if (s[index] == ')') {
                    return "";
                }
                ans += s[index];
                index++;
            }
            index++;
            const auto part = rec(s, index);
            ans.append(part);
        }

        return ans;
    }
};

void test(string&& s) {
    cout << Solution().reverseParentheses(s) << endl;
}
int main()
{
    test("(abcd)");
    test("(u(love)i)");
    test("(ed(et(oc))el)");
    return 0;
}