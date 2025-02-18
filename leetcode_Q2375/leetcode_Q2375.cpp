// leetcode_Q2375.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <set>
using namespace std;
class Solution {
public:
    static char rec(const string& pattern, int index, string& ans, set<char>& digits) {
        if (size(pattern) == index) {
            auto it = begin(digits);
            ans[index] = *it;
            digits.erase(it);
            return ans[index];
        }
        if (pattern[index] == 'I') {
            auto it = begin(digits);
            ans[index] = *it;
            digits.erase(it);
            return ans[index];
        }
        const auto next = rec(pattern, index + 1, ans, digits);
        auto it = digits.upper_bound(next);
        ans[index] = *it;
        digits.erase(it);
        return ans[index];
    }
    string smallestNumber(string pattern) {
        string ans(size(pattern) + 1, ' ');
        set<char> digits;
        for (int i = 0; i <= size(pattern); i++) {
            digits.insert(static_cast<char>(i) + '1');
        }
        for (int i = 0; i <= size(pattern); i++) {
            if (ans[i] == ' ') {
                rec(pattern, i, ans, digits);
            }
        }
        return ans;
    }
};
void test(string&& pattern) {
    cout << Solution().smallestNumber(pattern) << endl;
}
int main()
{
    test("IIIDIDDD");
    test("DDD");
    return 0;
}