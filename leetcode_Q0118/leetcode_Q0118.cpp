// leetcode_Q0118.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> list;
        if(0 < numRows) {
            list.emplace_back(vector<int>{1});
            auto* before = &list.back();
            for (auto i = 1; i < numRows; i++) {
                vector<int> current_list;
                current_list.reserve(i + 1);
                current_list.emplace_back(1);
                for (auto j = 0; j < before->size() - 1; j++) {
                    current_list.emplace_back((*before)[j] + (*before)[j + 1]);
                }
                current_list.emplace_back(1);
                list.emplace_back(current_list);
                before = &list.back();
            }
        }
        return list;
    }
};


int main()
{
    const auto ret = Solution().generate(5);

    for (auto&& inner : ret) {
        for (auto&& value : inner) {
            std::cout << value << ",";
        }
        std::cout << std::endl;
    }
}

