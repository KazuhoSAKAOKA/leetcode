// leetcode_Q0214.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    static bool is_palindrome(const string& s) {
        for (size_t i = 0; i < size(s) / 2; i++) {
            if (s[i] != s[size(s) - 1 - i]) {
                return false;
            }
        }
        return true;
    }

    static string tle(const string& s) {
        if (s.empty()) { return ""; }
        string left_part = "";
        for (int i = 0; i < size(s); i++) {
            const auto current = left_part + s;
            if (is_palindrome(current)) {
                return current;
            }
            left_part += s[size(s) - 1 - i];
        }
        throw exception();
    }

    static bool is_palindrome_part(const string& s, size_t offset, size_t length) {
        for (size_t i = 0; i < length / 2; i++) {
            if (s[i + offset] != s[length - 1 - i + offset]) {
                return false;
            }
        }
        return true;
    }

    static string tle2(const string& s) {
        if (s.empty()) { return ""; }
        const size_t half = size(s) / 2;
        for (size_t i = 0; i < size(s) - 1; i++) {
            if (is_palindrome_part(s, 0, size(s) - i)) {
                const auto right_part = s.substr(size(s) - i);
                string left_part(crbegin(right_part), crend(right_part));
                return left_part + s;
            }
        }
        const auto right_part = s.substr(1);
        string left_part(crbegin(right_part), crend(right_part));
        return left_part + s;
    }

    static size_t find_palindrome_length(const string& s) {
        long long hashBase = 29;
        long long modValue = 1e9 + 7;
        long long forwardHash = 0, reverseHash = 0, powerValue = 1;
        int palindromeEndIndex = -1;

        // Calculate rolling hashes and find the longest palindromic prefix
        for (int i = 0; i < s.length(); ++i) {
            char currentChar = s[i];

            // Update forward hash
            forwardHash =
                (forwardHash * hashBase + (currentChar - 'a' + 1)) % modValue;

            // Update reverse hash
            reverseHash =
                (reverseHash + (currentChar - 'a' + 1) * powerValue) % modValue;
            powerValue = (powerValue * hashBase) % modValue;

            // If forward and reverse hashes match, update palindrome end index
            if (forwardHash == reverseHash) {
                palindromeEndIndex = i;
            }
        }
        return palindromeEndIndex + 1;
    }

    string shortestPalindrome(string s) {
        if (s.empty()) { return ""; }
        const auto len = find_palindrome_length(s);
        const auto right_part = s.substr(len);
        string left_part(crbegin(right_part), crend(right_part));
        return left_part + s;
    }
};

void test(string&& s) {
    cout << Solution().shortestPalindrome(s) << endl;
}

int main()
{
    test("aabba");
    test("");
    test("aacecaaa");
    test("abcd");
    return 0;
}