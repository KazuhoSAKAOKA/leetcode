// leetcode_q0013.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>

using namespace std;



class Solution {
public:
    int romanToInt(string s) {
        int total = 0;


        for (size_t index = 0; index < s.length(); index++)
        {
            const auto c = s[index];
            const auto value = roman_chars[c];
            if (c == 'I' && index < s.length() - 1 && (s[index + 1] == 'V' || s[index + 1] == 'X'))
            {
                total -= value;
            }
            else if (c == 'X' && index < s.length() - 1 && (s[index + 1] == 'L' || s[index + 1] == 'C'))
            {
                total -= value;
            }
            else if (c == 'C' && index < s.length() - 1 && (s[index + 1] == 'D' || s[index + 1] == 'M'))
            {
                total -= value;
            }
            else
            {
                total += value;
            }
        }
        return total;
    }

    static map<char, int> roman_chars;

};

map<char, int> Solution::roman_chars
{
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000},
};




void test(const std::string& s)
{
    const auto value = Solution().romanToInt(s);
    std::cout << s << "=" << value << std::endl;
}

int main()
{
    test("III");
    test("LVIII");
    test("MCMXCIV");
}

