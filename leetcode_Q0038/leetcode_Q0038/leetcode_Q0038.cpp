// leetcode_Q0038.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) { return "1"; }
        auto value = countAndSay(n - 1);

        string temp;
        int streak = 1;
        char before = value[0];
        for (auto i = 1; i < value.size(); i++) {
            if (before == value[i]) {
                streak++;
            }
            else {
                if (streak < 10) {
                    temp += (streak + '0');
                    temp += before;
                }
                else {
                    throw;
                }
                streak = 1;
                before = value[i];
            }
        }
        if (streak < 10) {
            temp += (streak + '0');
            temp += before;
        }
        else {
            throw;
        }

        return temp;
    }
};

int main()
{
    for (auto i = 1; i <= 30; i++) {
        cout << Solution().countAndSay(i) << endl;
    }
}

