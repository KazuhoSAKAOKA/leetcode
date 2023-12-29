// leetcode_Q0168.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string convertToTitle(int columnNumber) {
        const string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        auto value = columnNumber;
        string temp;
        do
        {
            auto v = value % alphabets.size();
            if (v == 0) {
                temp.push_back(alphabets[alphabets.size() - 1]);
                value--;
            }
            else {
                temp.push_back(alphabets[v - 1]);
            }
            value /= alphabets.size();
        } while (value > 0);

        return string(crbegin(temp), crend(temp));
    }
};


int main()
{
    std::cout << Solution().convertToTitle(1) << std::endl;
    std::cout << Solution().convertToTitle(26) << std::endl;
    std::cout << Solution().convertToTitle(28) << std::endl;
    std::cout << Solution().convertToTitle(701) << std::endl;

}
