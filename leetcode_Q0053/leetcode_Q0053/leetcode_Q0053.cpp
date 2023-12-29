// leetcode_Q0053.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class Solution {
public:

    int brute_force(const vector<int>& nums) {
        vector<int64_t> sumArr;
        sumArr.reserve(nums.size() + 1);
        int64_t total = 0;
        sumArr.emplace_back(0);
        for (auto&& value : nums) {
            total += value;
            sumArr.emplace_back(total);
        }
        int64_t ans = INT64_MIN;
        for (auto i = 0; i < nums.size(); i++) {
            for (auto j = i; j < nums.size(); j++) {
                ans = max(ans, sumArr[j + 1] - sumArr[i]);
            }
        }
        return ans;
    }

    int solve(const vector<int>& nums){
        int64_t currentMax = nums[0];
        int64_t currentTotal = nums[0];
        for (auto i = 1; i < nums.size(); i++) {
            currentTotal = max(static_cast<int64_t>(nums[i]), currentTotal + nums[i]);
            currentMax = max(currentMax, currentTotal);
        }
        return currentMax;
    }


    int maxSubArray(vector<int>& nums) {
        return solve(nums);
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maxSubArray(nums) << endl;
}

int main()
{
    test({ -2,1,-3,4,-1,2,1,-5,4 });
    test({1});
    test({ 5,4,-1,7,8 });
}

