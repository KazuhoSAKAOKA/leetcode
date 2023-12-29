// leetcode_20.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;


class Solution {
public:
    bool isValid(string s) {
        stack<char> stack;
        const map<char, char> brackets
        {
            {')','('},
            {']','['},
            {'}','{'},
        };

        for (const auto& c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                stack.push(c);
            }
            else
            {
                const auto it = brackets.find(c);
                if (it != cend(brackets))
                {
                    if (stack.empty()) { return false; }
                    const auto begin_of_brackets = stack.top();
                    stack.pop();
                    if (it->second != begin_of_brackets)
                    {
                        return false;
                    }
                }
            }
        }
        return stack.empty();
    }
};

int main()
{
    std::cout << Solution().isValid("()") << std::endl;
    std::cout << Solution().isValid("[()]") << std::endl;
    std::cout << Solution().isValid("{()}") << std::endl;
}

