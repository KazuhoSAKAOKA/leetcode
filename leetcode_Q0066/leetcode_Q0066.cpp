// leetcode_Q0066.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> temp;
        temp.reserve(digits.size() + 1);
        auto it = crbegin(digits);

        bool carry = false;
        if (*it == 9)
        {
            carry = true;
            temp.push_back(0);
        }
        else
        {
            temp.push_back(*it + 1);
        }
        ++it;
        for (; it != crend(digits); ++it)
        {
            if (carry)
            {
                if (*it == 9)
                {
                    carry = true;
                    temp.push_back(0);
                }
                else
                {
                    carry = false;
                    temp.push_back(*it + 1);
                }
            }
            else
            {
                temp.push_back(*it);
            }
        }
        if (carry)
        {
            temp.push_back(1);
        }

        return vector<int>(crbegin(temp), crend(temp));
    }
};

void output(const vector<int>& list)
{
    for (auto&& value : list)
    {
        std::cout << value << ",";
    }
    std::cout << std::endl;
}


int main()
{
    vector<int> digits1{ 1,2,3, };
    vector<int> digits2{ 4,3,2,1, };
    vector<int> digits3{ 9, };
    vector<int> digits4{ 1,8,9,9, 9, };


    output(Solution().plusOne(digits1));
    output(Solution().plusOne(digits2));
    output(Solution().plusOne(digits3));
    output(Solution().plusOne(digits4));
}

