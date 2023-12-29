// leetcode_Q0022.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:

    pair<string, int> openParen(int depth, const string& current) {
        return make_pair(current + '(', depth + 1);
    }
    pair<string, int> closeParen(int depth, const string& current) {
        return make_pair(current + ')', depth - 1);
    }

    void generate(vector<string>& list, int depth, const string& current, int count) {

        if (count == 0)        {
            if (depth == 0) {
                list.emplace_back(current);
            }
            else {
                auto [closeItem, newDepth] = closeParen(depth, current);
                generate(list, newDepth, closeItem, count);
            }
            return;
        }

        auto [addItem, openedDepth] = openParen(depth, current);
        generate(list, openedDepth, addItem, count - 1);
        if (depth > 0) {
            auto [closeItem, closedDepth] = closeParen(depth, current);
            generate(list, closedDepth, closeItem, count);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        string current;
        generate(ret, 0, current, n);
        return ret;
    }
};



void output(const vector<string>& ans)
{
    for (auto&& v : ans) {
        cout << v << ",";
    }
    cout << endl;
}

int main()
{
    output(Solution().generateParenthesis(8));
    output(Solution().generateParenthesis(3));
    output(Solution().generateParenthesis(1));
}

