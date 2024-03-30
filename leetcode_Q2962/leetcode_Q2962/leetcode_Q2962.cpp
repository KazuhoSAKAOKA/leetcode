// leetcode_Q2962.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    static int counting(const vector<int>& nums, int k, int index) {
        if (k == 1) {
            return index + 1;
        }
        int c = 1;
        for (int i = index - 1; i >= 0; i--) {
            if (nums[i] == nums[index]) {
                c++;
                if (c == k) {
                    return i + 1;
                }
            }
        }
        throw exception();
    }

    long long countSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> count_map;
        long long condition_min = 0;
        vector<long long> dp(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            const auto v = ++count_map[nums[i]];
            if (v < k) {
                dp[i + 1] = dp[i] + dp[i];
            }
            else {
                int c = counting(nums, k, i);
                dp[i + 1] = dp[i] + c;
            }
        }

        return dp[nums.size()];
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().countSubarrays(nums, k) << endl;
}


int main()
{
    test({ 1,3,2,3,3 }, 2);
    test({ 1,4, 2,1 }, 4);
}

