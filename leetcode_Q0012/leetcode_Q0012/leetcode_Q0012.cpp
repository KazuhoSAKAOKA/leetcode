// leetcode_Q0012.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:


    void append(string& s, int value, char upperValue, char fiveValue, char unitValue) {
        if (value == 0) {

        }
        else if (value < 4) {
            s.append(value, unitValue);
        }
        else if (value == 4) {
            s += unitValue;
            s += fiveValue;
        }
        else if (value == 5) {
            s += fiveValue;
        }
        else if (value < 9) {
            s += fiveValue;
            s.append(value - 5, unitValue);
        }
        else if (value == 9) {
            s += unitValue;
            s += upperValue;
        }
        else {
            throw 0;
        }
    }


    string intToRoman(int num) {
        string s;

        const auto m = num / 1000;
        const auto dandc = (num % 1000) / 100;
        const auto landx = (num % 100) / 10;
        const auto vandi = num % 10;

        s.append(m, 'M');
        append(s, dandc, 'M', 'D', 'C');
        append(s, landx, 'C', 'L', 'X');
        append(s, vandi, 'X', 'V', 'I');
        return s;
    }
};


int main()
{
    std::cout << Solution().intToRoman(3) << std::endl;
    std::cout << Solution().intToRoman(58) << std::endl;
    std::cout << Solution().intToRoman(1994) << std::endl;
    std::cout << Solution().intToRoman(3) << std::endl;
}

