// leetcode_Q2825.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        int index = 0;
        for (auto&& c : str2) {
            bool exist = false;
            while (index < size(str1)) {
                if (str1[index] == c) {
                    exist = true;
                    index++;
                    break;
                }
                if (c == 'a') {
                    if (str1[index] == 'z') {
                        exist = true;
                        index++;
                        break;
                    }
                }
                else {
                    if (str1[index] + 1 == c) {
                        exist = true;
                        index++;
                        break;
                    }
                }
                index++;
            }
            if (!exist) {
                return false;
            }
        }
        return true;
    }
};

void test(string&& str1, string&& str2) {
    cout << Solution().canMakeSubsequence(str1, str2) << endl;
}
int main()
{
    test("abc", "ad");
    test("zc", "ad");
    test("ab", "d");
    return 0;
}