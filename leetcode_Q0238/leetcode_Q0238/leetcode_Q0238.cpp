// leetcode_Q0238.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int zero_index = -1;
        int total = 1;

        vector<int> ans(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                if (zero_index < 0) {
                    zero_index = i;
                }
                else {
                    return ans;
                }
            }
            else {
                total = total * nums[i];
            }
        }
        if (zero_index < 0) {
            for (int i = 0; i < nums.size(); i++) {
                ans[i] = total / nums[i];
            }
        }
        else {
            ans[zero_index] = total;
        }

        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().productExceptSelf(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}



int main()
{
    test({ 1,2,3,4 });
    test({ -1,1,0,-3,3 });
}