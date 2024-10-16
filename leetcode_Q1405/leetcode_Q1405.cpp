// leetcode_Q1405.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:

    static int select(int a, int b, int c, int before_index, int current_streak) {
        if (current_streak < 1) {
            if (a < b) {
                if (b < c) {
                    return 2;
                }
                else {
                    return 1;
                }
            }
            else {
                if (a < c) {
                    return 2;
                }
                else {
                    return 0;
                }
            }
        }
        else {
            switch (before_index) {
            case 0:
                return b < c ? 2 : 1;
            case 1: 
                return a < c ? 2 : 0;
            case 2:
                return a < b ? 1 : 0;
            }
            throw exception();
        }
    }
    string longestDiverseString(int a, int b, int c) {
        string ans;
        int current_streak = 0;
        int before_index = -1;
        vector<int> abc{ a,b,c };
        for (;;) {
            int selected = select(abc[0], abc[1], abc[2], before_index, current_streak);
            if (abc[selected] == 0) {
                break;
            }
            if (selected == before_index) {
                current_streak++;
            }
            else {
                current_streak = 0;
                before_index = selected;
            }
            ans += static_cast<char>('a' + selected);
            abc[selected]--;
        }
        return ans;
    }
};

void test(int a, int b, int c) {
    cout << Solution().longestDiverseString(a, b, c) << endl;
}

int main()
{
    test(1, 1, 7);
    test(7, 1, 0);
    return 0;
}