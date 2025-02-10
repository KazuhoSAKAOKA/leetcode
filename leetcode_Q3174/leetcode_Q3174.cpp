// leetcode_Q3174.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string clearDigits(string s) {
        vector<int> nondigit_indexes;
        vector<bool> deletes(size(s));
        for (int i = 0; i < size(s); i++) {
            if (isdigit(s[i])) {
                deletes[i] = true;
                const auto nondigit = nondigit_indexes.back();
                deletes[nondigit] = true;
                nondigit_indexes.pop_back();
            }
            else {
                nondigit_indexes.emplace_back(i);
            }
        }

        string ans;
        ans.reserve(size(s));
        for (int i = 0; i < size(s); i++) {
            if (!deletes[i]) {
                ans += s[i];
            }
        }
        return ans;
    }
};

void test(string&& s) {
    cout << Solution().clearDigits(s) << endl;
}
int main()
{
    test("abc");
    test("cb34");
    return 0;
}