// leetcode_Q2490.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isCircularSentence(string sentence) {
        if (sentence.front() != sentence.back()) {
            return false;
        }
        size_t pos = 0;
        while (pos < size(sentence)) {
            const auto p = sentence.find(' ', pos);
            if (p == string::npos) {
                break;
            }
            if (sentence[p - 1] != sentence[p + 1]) {
                return false;
            }
            pos = p + 1;
        }
        return true;
    }
};

void test(string sentence) {
    cout << Solution().isCircularSentence(sentence) << endl;
}

int main()
{
    test("leetcode exercises sound delightful");
    test("eetcode");
    test("Leetcode is cool");
    return 0;
}