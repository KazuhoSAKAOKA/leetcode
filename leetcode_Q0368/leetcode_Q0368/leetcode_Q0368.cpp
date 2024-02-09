// leetcode_Q0368.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Solution {
public:

    void rec(const vector<int>& nums, int index, vector<int>& subset, vector<int>& max_subset) {
        if (nums.size() == index) {
            return;
        }

        for (int i = index; i < nums.size(); i++) {

        }
    }


    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<int> ans;

        unordered_map<int, vector<int>> dpmap;
        int max_index = 0;
        int max_length = 0;
        for (int i = 0; i < nums.size(); i++) {
            int current_max_index = i + 1;
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] % nums[j] == 0) {
                    auto& list = dpmap[j + 1];
                    if (dpmap[current_max_index].size() < list.size() + 1) {
                        current_max_index = j + 1;
                    }
                }
            }
            auto copied = dpmap[current_max_index];
            copied.emplace_back(nums[i]);
            dpmap[i + 1] = copied;
            if (max_length < copied.size()) {
                max_index = i + 1;
                max_length = copied.size();
            }
        }

        return dpmap[max_index];
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().largestDivisibleSubset(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test({ 1,2,3, });
    test({ 1,2,4,8, });
    test({ 1,2,4,8,19, 38, 76, 152, 304, });
}