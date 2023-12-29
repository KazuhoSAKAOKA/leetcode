// leetcode_Q0163.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>> ret;
        auto before_value = lower - 1;
        if (!nums.empty())
        {
            size_t index = 0;
            for (auto i = 0; i < nums.size(); i++)
            {
                const auto current_value = nums[i];
                const auto diff = current_value - before_value;
                if (diff > 1) {
                    ret.emplace_back(vector<int>{ before_value + 1, current_value - 1, });
                }
                before_value = current_value;
            }
        }
        if ((upper + 1) - before_value > 1)
        {
            ret.emplace_back(vector<int>{ before_value + 1, upper, });
        }
        return ret;
    }
};

int main()
{
    //std::vector <int> list{ 0, 1, 3, 50, 75 };
    //const auto vals = Solution().findMissingRanges(list, 0, 99);

    //std::vector <int> list{ -1 };
    //const auto vals = Solution().findMissingRanges(list, -1, -1);
    std::vector <int> list{ };
    const auto vals = Solution().findMissingRanges(list, 0, 99);

    for (auto&& inner : vals)
    {
        for (auto&& v : inner)
        {
            std::cout << v << ",";
        }
        std::cout << std::endl;
    }
}

