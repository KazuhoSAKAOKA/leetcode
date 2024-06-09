// leetcode_Q0974.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        if (k == 0) { return 0; }
        unordered_map<int, int> prefix_mod_map;
        prefix_mod_map[0] = 1;
        long long prefix_sums = 0;
        for (int i = 0; i < nums.size(); i++) {
            prefix_sums += nums[i];
            const auto modulo = prefix_sums % k;
            prefix_mod_map[modulo]++;
        }
        int total = 0;

        for (auto&& [k, v] : prefix_mod_map) {
            if(v > 1){
                total += (v - 1) * v / 2;
            }
        }

        return total;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().subarraysDivByK(nums, k) << endl;
}

int main()
{
    test(get_list_int("[4,5,0,-2,-3,1]"), 5);
    test(get_list_int("[5]"), 9);
}