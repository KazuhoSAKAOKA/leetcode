// leetcode_Q1963.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minSwaps(string s) {
        int left_open_brackets = 0;
        int left_close_brackets = 0;
        int right_open_brackets = 0;
        int right_close_brackets = 0;
        int l = 0;
        int r = size(s);

        int count = 0;
        while (l < r) {
            if (s[l] == '[') {
                left_open_brackets++;
            }
            else if (s[l] == ']') {
                left_close_brackets++;
                if (left_close_brackets > left_open_brackets) {

                    while (right_open_brackets <= right_close_brackets) {
                        r--;
                        if (s[r] == '[') {
                            right_open_brackets++;
                        }
                        else if (s[r] == ']') {
                            right_close_brackets++;
                        }
                        else { throw exception(); }
                    }
                    swap(s[l], s[r]);
                    left_open_brackets++;
                    left_close_brackets--;
                    right_open_brackets--;
                    right_close_brackets++;
                    count++;
                }
            }
            else { throw exception(); }
            l++;
        }
        return count;
    }
};

void test(string&& s) {
    cout << Solution().minSwaps(s) << endl;
}

int main()
{
    test("]]][[[");
    test("][][");
    test("[]");
    return 0;
}