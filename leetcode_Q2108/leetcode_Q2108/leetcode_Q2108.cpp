// leetcode_Q2108.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    static bool is_palindrome(const string& word) {
        for (size_t i = 0; i < word.size() / 2; i++) {
            if (word[i] != word[word.size() - i - 1]) {
                return false;
            }
        }
        return true;
    }


    string firstPalindrome(vector<string>& words) {
        for (auto&& word : words) {
            if (is_palindrome(word)) {
                return word;
            }
        }
        return "";
    }
};

void test(vector<string>&& words) {
    cout << Solution().firstPalindrome(words) << endl;
}


int main()
{
    test({ "abc","car","ada","racecar","cool" });
    test({ "notapalindrome","racecar" });
    test({ "def","ghi" });
    test({ "qac","aa" });

    test({ "d","aa" });
}