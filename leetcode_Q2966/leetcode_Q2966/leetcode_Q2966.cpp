// leetcode_Q2966.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:


    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        vector<vector<int>> ans;
        sort(begin(nums), end(nums));
        
        int index = 0;
        while ((index + 2) < nums.size()) {
            if (nums[index + 2] - nums[index] <= k) {
                ans.emplace_back(vector<int>{ nums[index], nums[index + 1] ,nums[index + 2] ,});
                index += 3;
            }
            else {
                return vector<vector<int>>();
            }
        }
        return ans;
    }
};


void test(vector<int>&& nums, int k) {
    const auto ans = Solution().divideArray(nums, k);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    test({ 1,3,4,8,7,9,3,5,1 },2 );
    test({ 1,3,3,2,7,3 },3 );
}