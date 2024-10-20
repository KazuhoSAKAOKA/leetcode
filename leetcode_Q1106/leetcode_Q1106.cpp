// leetcode_Q1106.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;


class Solution {
public:

    static pair<bool, int> parse_and_eval(const string& expression, size_t index) {
        if (size(expression) == index) {
            throw exception();
        }
        switch (expression[index]) {
        case 't':
            return { true,1 };
        case 'f':
            return { false, 1 };
        case '!':
        {
            if (expression[index + 1] != '(') {
                throw exception();
            }
            const auto [r, len] = parse_and_eval(expression, index + 2);
            if (expression[index + 1 + len + 1] != ')') {
                throw exception();
            }
            return { !r, len + 3 };
        }
        case '&':
        case '|':
        {
            if (expression[index + 1] != '(') {
                throw exception();
            }
            bool cur_val = expression[index] == '&';
            int offset = 2;
            for (;;) {
                const auto [r, len] = parse_and_eval(expression, index + offset);
                if (expression[index] == '&') {
                    cur_val &= r;
                }
                else {
                    cur_val |= r;
                }
                offset += len;
                if (expression[index + offset] == ')') {
                    break;
                }
                if (expression[index + offset] != ',') {
                    throw exception();
                }
                offset++;
            }
            return { cur_val, offset + 1 };
        }
        }
        throw exception();
    }


    bool parseBoolExpr(string expression) {
        const auto [r, len] = parse_and_eval(expression, 0);
        if (len != size(expression)) {
            throw exception();
        }
        return r;
    }
};

void test(string&& expression) {
    cout << Solution().parseBoolExpr(expression) << endl;
}
int main()
{
    test("&(|(f))");
    test("|(f,f,f,t)");
    test("!(&(f,t))");
    return 0;
}