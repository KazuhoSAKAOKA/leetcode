// leetcode_Q0977.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans;
        ans.reserve(nums.size());
        const auto it = upper_bound(cbegin(nums), cend(nums), 0);

        auto forword_index = distance(cbegin(nums), it);
        auto backword_index = forword_index - 1;
        int index = 0;

        while (backword_index >= 0 && forword_index < nums.size()) {
            const auto v1 = nums[backword_index] * nums[backword_index];
            const auto v2 = nums[forword_index] * nums[forword_index];
            if (v1 < v2) {
                ans.emplace_back(v1);
                backword_index--;
            }
            else {
                ans.emplace_back(v2);
                forword_index++;
            }
        }

        if (backword_index >= 0) {
            while (backword_index >= 0) {
                ans.emplace_back(nums[backword_index] * nums[backword_index]);
                backword_index--;
            }
        }
        else {
            while (forword_index < nums.size()) {
                ans.emplace_back(nums[forword_index] * nums[forword_index]);
                forword_index++;
            }
        }

        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().sortedSquares(nums);

    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test({ -4,-1,0,3,10 });
    test({ -7,-3,2,3,11 });
    test({ 0,1,2,3,4 });
    test({ 1,2,3,4 });
    test({ -5,-4,-3,-2,-1, });
}