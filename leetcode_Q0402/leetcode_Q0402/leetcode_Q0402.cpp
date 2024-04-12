// leetcode_Q0402.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans;

        auto it = cbegin(num);
        auto it_e = next(it, k);

        for (; it_e != cend(num);) {
            const auto it1 = min_element(it, next(it_e));
            if (!(ans.empty() && *it1 == '0')) {
                ans.push_back(*it1);
            }
            it = next(it1);
            ++it_e;
        }

        if (ans.empty()) {
            ans.push_back('0');
        }
        return ans;
    }
};
void test(string&& num, int k) {
    cout << Solution().removeKdigits(num, k) << endl;
}
int main()
{
    test("1432219", 3);
    test("10200", 1);
    test("10", 2);
}