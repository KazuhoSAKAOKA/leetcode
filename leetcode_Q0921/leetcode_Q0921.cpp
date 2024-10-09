// leetcode_Q0921.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minAddToMakeValid(string s) {
        int open_parents = 0;
        int close_parents = 0;
        int count = 0;

        for (int i = 0; i < size(s); i++) {
            if (s[i] == '(') {
                open_parents++;
            }
            else if (s[i] == ')') {
                close_parents++;
                if (close_parents > open_parents) {
                    count++;
                    open_parents++;
                }
            }
            else {
                throw exception();
            }
        }

        if (open_parents > close_parents) {
            count += open_parents - close_parents;
        }
        return count;
    }
};

void test(string&& s) {
    cout << Solution().minAddToMakeValid(s) << endl;
}

int main()
{
    test("())");
    test("(((");
    return 0;
}