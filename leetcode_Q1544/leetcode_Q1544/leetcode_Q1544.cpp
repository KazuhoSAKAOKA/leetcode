// leetcode_Q1544.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:

    static bool check_adjacent(char a, char b) {
        if ('a' <= a && a <= 'z') {
            return a - 'a' == b - 'A';
        }
        return a - 'A' == b - 'a';
    }

    string makeGood(string s) {
        string work(s);
        bool exist = true;
        while (work.size() > 1 && exist) {
            exist = false;
            for (int i = 0; i < work.size() - 1; i++) {
                if (check_adjacent(work[i], work[i + 1])) {
                    work = work.substr(0, i) + work.substr(i + 2);
                    exist = true;
                    break;
                }
            }
        }
        return work;
    }
};

void test(string&& s) {
    cout << Solution().makeGood(s) << endl;
}

int main()
{
    test("leEeetcode");
    test("abBAcC");
    test("s");
}