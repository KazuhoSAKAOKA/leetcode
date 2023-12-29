// leetcode_Q0055.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> allowReach(nums.size(), false);

        allowReach[0] = true;

        for (auto i = 0; i < nums.size() - 1; i++) {
            if (allowReach[i]) {
                auto s = min(nums[i] + i + 1, static_cast<int>(nums.size()));
                for (auto j = i + 1; j < s; j++) {
                    allowReach[j] = true;
                }
            }
        }

        return allowReach[nums.size() - 1];
    }
};

void test(vector<int>&& nums) {
    cout << Solution().canJump(nums) << endl;
}

int main()
{
    test({ 2,3,1,1,4 });
    test({ 3,2,1,0,4 });
    test({ 4,0,0,0,4 });
    test({ 3,0,0,0,4 });
    test({ 3,0,0,100,4 });

}

