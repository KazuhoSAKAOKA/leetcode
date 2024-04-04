// leetcode_Q1614.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDepth(string s) {
        stack<char> parents;
        int max_depth = 0;
        for (auto&& c : s) {
            if (c == '(') {
                parents.push(c);
                max_depth = max(max_depth, static_cast<int>(parents.size()));
            }
            else if (c == ')') {
                parents.pop();
            }

        }
        return max_depth;
    }
};

void test(string&& s) {
    cout << Solution().maxDepth(s) << endl;
}

int main()
{
    test("(1+(2*3)+((8)/4))+1");
    test("(1)+((2))+(((3)))");
}