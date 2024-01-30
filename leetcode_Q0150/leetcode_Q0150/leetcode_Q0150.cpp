// leetcode_Q0150.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <numbers>
#include <numeric>
#include <algorithm>
using namespace std;


class Solution {
public:

    static bool is_numeric(const string& token) {
        if (token[0] == '-') {
            return token.size() > 1 && all_of(next(cbegin(token)), cend(token), [](const auto c) { return isdigit(c); });
        }
        else {
            return all_of(cbegin(token), cend(token), [](const auto c) { return isdigit(c); });
        }
    }

    int evalRPN(vector<string>& tokens) {

        stack<int> num_stack;


        for (auto&& token : tokens) {
            if (is_numeric(token)) {
                num_stack.push(stoi(token));
            }
            else {
                const auto value2 = num_stack.top();
                num_stack.pop();
                const auto value1 = num_stack.top();
                num_stack.pop();
                if (token == "*") {
                    num_stack.push(value1 * value2);
                }
                else if (token == "+") {
                    num_stack.push(value1 + value2);
                }
                else if (token == "-") {
                    num_stack.push(value1 - value2);
                }
                else if (token == "/") {
                    num_stack.push(value1 / value2);
                }
                else {
                    throw exception();
                }
            }
        }

        return num_stack.top();
    }
};

void test(vector<string>&& tokens) {
    cout << Solution().evalRPN(tokens) << endl;
}

int main()
{
    test({"2", "1", "+", "3", "*"});
    test({ "4","13","5","/","+" });
    test({ "10","6","9","3","+","-11","*","/","*","17","+","5","+" });

}