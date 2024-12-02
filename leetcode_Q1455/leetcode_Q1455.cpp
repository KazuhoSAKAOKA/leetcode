// leetcode_Q1455.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    static bool check(const string& sentence, const string searchWord, size_t offset) {
        const auto len = size(searchWord);
        const auto remain = size(sentence) - offset;
        if (remain < len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (sentence[offset + i] != searchWord[i]) {
                return false;
            }
        }
        return true;
    }

    int isPrefixOfWord(string sentence, string searchWord) {
        size_t index = 0;
        int word_index = 0;
        bool check_prefix = true;
        while (index < size(sentence)) {
            if (sentence[index] == ' ') {
                word_index++;
                check_prefix = true;
            }
            else {
                if (check_prefix) {
                    if (check(sentence, searchWord, index)) {
                        return word_index + 1;
                    }
                    check_prefix = false;
                }
            }
            index++;
        }
        return -1;
    }
};

void test(string&& sentence, string&& searchWord) {
    cout << Solution().isPrefixOfWord(sentence, searchWord) << endl;
}
int main()
{
    test("i love eating burger", "i");
    test("i love eating burger", "burgers");
    test("i love eating burger", "burg");
    test("this problem is an easy problem", "pro");
    test("i am tired", "you");
    return 0;
}