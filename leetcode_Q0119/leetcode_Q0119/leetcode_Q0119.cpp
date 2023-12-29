// leetcode_Q0119.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> prev{ 1 };
        if (rowIndex == 0) { return prev; }

        int index = 0;
        for (;;) {
            vector<int> current;
            current.emplace_back(1);
            for (int i = 0; i < prev.size() - 1; i++) {
                current.emplace_back(prev[i] + prev[i + 1]);
            }
            current.emplace_back(1);
            if (++index == rowIndex) {
                return current;
            }
            prev = std::move(current);
        }
    }
};


int main()
{
    const auto r = Solution().getRow(3);
    for (auto&& v : r)
    {
        std::cout << v << ",";
    }
    std::cout << std::endl;
}

