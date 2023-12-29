// leetcode_Q0067.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    static int parse_bin(string::const_reverse_iterator& it, const string::const_reverse_iterator end)
    {
        if (it == end) { return 0; }
        const auto value = *it;
        ++it;
        return (value == '0') ? 0 : 1;
    }

    string addBinary(string a, string b) {
        auto left_it = std::crbegin(a);
        auto right_it = std::crbegin(b);
        const auto left_end = std::crend(a);
        const auto right_end = std::crend(b);
        string temp;
        temp.reserve(std::max(a.size(), b.size()) + 1);
        int carry = 0;
        while(!(left_it == left_end && right_it == right_end))
        {
            const auto value = parse_bin(left_it, left_end) + parse_bin(right_it, right_end) + carry;
            switch (value)
            {
            case 0:
                temp.push_back('0');
                carry = 0;
                break;
            case 1:
                temp.push_back('1');
                carry = 0;
                break;
            case 2:
                temp.push_back('0');
                carry = 1;
                break;
            case 3:
                temp.push_back('1');
                carry = 1;
                break;
            default:
                throw 0;
            }
        }
        if (carry != 0)
        {
            temp.push_back('1');
        }
        return string(crbegin(temp), crend(temp));
    }
};


int main()
{
    std::cout << Solution().addBinary("11","1") << std::endl;
    std::cout << Solution().addBinary("1010","1011") << std::endl;
}