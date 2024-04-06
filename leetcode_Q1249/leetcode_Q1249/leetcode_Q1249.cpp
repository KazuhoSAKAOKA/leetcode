// leetcode_Q1249.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <stack>
#include <deque>

using namespace std;

class Solution {
public:
    /*
    static string convert_str(stack<char>& c_stack) {
        if (c_stack.empty()) { return string(); }
        string temp;
        temp += ')';
        while (!c_stack.empty()) {
            temp += c_stack.top();
            c_stack.pop();
            if (temp[temp.size() - 1] == '(') {
                break;
            }
        }
        if (temp[temp.size() - 1] == '(') {
            return string(crbegin(temp), crend(temp));
        }
        else {
            // カッコ無視
            return string(crbegin(temp), prev(crend(temp)));
        }
    }
    void gomi(){
            int left = 0;
        int right = s.size() - 1;
        string forward;
        string backward;
        int balance = 0;
        while (left <= right) {
            if (0 <= balance) {
                if (s[left] == '(') {
                    balance--;
                    forward += '(';
                }
                else if (s[left] == ')') {
                }
                else {
                    forward += s[left];
                }
                left++;
            }
            else {
                if (s[right] == '(') {
                }
                else if (s[right] == ')') {
                    backward += ')';
                    balance++;
                }
                else {
                    backward += s[right];
                }
                right--;
            }
        }
        if (balance < 0) {
            forward.pop_back();
        }
        else if (balance > 0) {
            backward.pop_back();
        }
        return forward + string(crbegin(backward), crend(backward));

    */

    tuple<string, bool, int> create(const string& s, int index) {
        if (s.size() == index) {
            return make_tuple("", false, index);
        }
        string buffer;
        while (index < s.size()) {
            const char c = s[index];
            if (c == '(') {
                const auto [v, closed, i] = create(s, index + 1);
                if (closed) {
                    buffer += '(';
                    buffer += v;
                    buffer += ')';
                }
                else {
                    buffer += v;
                }
                index = i;
            }
            else {
                if (c == ')') {
                    return make_tuple(buffer, true, index + 1);
                }
                buffer += c;
                index++;
            }
        }
        return make_tuple(buffer, false, index);
    }


    string minRemoveToMakeValid(string s) {
        string ans;
        int index = 0;

        while (index < s.size()) {
            const auto [v, _, i] = create(s, index);
            ans += v;
            index = i;
        }

        return ans;
    }
};

void test(string&& s) {
    cout << Solution().minRemoveToMakeValid(s) << endl;
}

int main()
{
    test("v((((((())");
    test("())()(((");
    test("lee(t(c)o)de)");
    test("a)b(c)d");
    test("((()))");
    test("))((");
}