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

    static long long past(vector<int>& nums, int k) {
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


    long long countSubarrays(vector<int>& nums, int k) {
        const auto max_num = *max_element(cbegin(nums), cend(nums));
        long long count_sub_arr = 0;
        int cur_count = 0;

        long long l = 0;
        for (long long r = 0; r < size(nums); r++) {
            if (nums[r] == max_num) {
                cur_count++;
            }
            while (l < r && cur_count >= k) {
                if (nums[l] == max_num) {
                    if (cur_count == k) {
                        break;
                    }
                    cur_count--;
                }
                l++;
            }
            if (cur_count >= k) {
                count_sub_arr += l + 1;
            }
        }
        return count_sub_arr;
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

