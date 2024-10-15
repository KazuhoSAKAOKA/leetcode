// leetcode_Q2938.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    long long minimumSteps(string s) {
        long long count = 0;
        long long current_one_count = 0;

        for (auto&& c : s) {
            if (c == '1') {
                current_one_count++;
            }
            else {
                count += current_one_count;
            }
        }
        return count;
    }
};

void test(string&& s) {
    cout << Solution().minimumSteps(s) << endl;
}

int main()
{
    test("101");
    test("100");
    test("0111");
    return 0;
}