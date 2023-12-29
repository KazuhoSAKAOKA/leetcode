// leetcode_Q0125.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;


bool alphabets(const string& s, size_t index) {
    const auto v = s[index];
    if (('a' <= v && v <= 'z') || ('A' <= v && v <= 'Z') || ('0' <= v && v <= '9')) {
        return true;
    }
    return false;
}

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.length() == 0) { return true; }
        int forword_index = 0;
        int backword_index = static_cast<int>(s.length()) - 1;
        for (;;) {
            while (!alphabets(s, forword_index)) {
                ++forword_index;
                if (s.length() <= forword_index) { break; }
            }
            while (!alphabets(s, backword_index)) {
                --backword_index;
                if (backword_index < 0) { break; }
            }
            if (backword_index <= forword_index) {
                break;
            }
            if (tolower(s[forword_index]) != tolower(s[backword_index])) {
                return false;
            }
            ++forword_index;
            --backword_index;
            if (backword_index <= forword_index) {
                break;
            }
        }
        return true;
    }
};
int main()
{
    string s = "A man, a plan, a canal: Panama";
    std::cout << Solution().isPalindrome(s) << std::endl;
    std::cout << Solution().isPalindrome(" ") << std::endl;
    std::cout << Solution().isPalindrome("") << std::endl;
}

