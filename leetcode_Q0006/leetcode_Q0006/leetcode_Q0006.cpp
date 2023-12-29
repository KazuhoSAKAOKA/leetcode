// leetcode_Q0006.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

#include <algorithm>

using namespace std;


class Solution {
public:

    static int nextRowIndex(int numRows, int index) {
        if (numRows == 1) { return 0; }
        else if (numRows == 2) { return index % 2; }
        const auto base = numRows * 2 - 2;
        const auto groupIndex = index / base;
        const auto groupMod = index % base;

        if (groupMod < numRows) {
            return groupMod;
        }
        return numRows - (groupMod - numRows + 1) - 1;
    }

    string convert(string s, int numRows) {
        vector<string> buffer;
        buffer.reserve(numRows);
        for (size_t index = 0; index < numRows; index++) {
            buffer.emplace_back(string());
        }
        for(size_t index = 0; index < s.size(); index++){
            const auto rowIndex = nextRowIndex(numRows, index);
            buffer[rowIndex] += s[index];
        }

        string ans;
        ans.reserve(s.size());
        for (size_t index = 0; index < numRows; index++) {
            const auto& temp = buffer[index];
            ans.append(temp);
        }
        return ans;
    }
};
int main()
{
    cout << Solution().convert("PAYPALISHIRING", 3) << std::endl;
    cout << Solution().convert("PAYPALISHIRING", 4) << std::endl;
    cout << Solution().convert("A", 1) << std::endl;

}
