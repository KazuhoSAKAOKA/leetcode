// leetcode_Q0078.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    void subsets_rec(const vector<int>& nums, int index, size_t len, vector<int>& current, vector<vector<int>>& list) {
        if (len == current.size()) {
            list.emplace_back(current);
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            current.push_back(nums[i]);
            subsets_rec(nums, i + 1, len, current, list);
            current.pop_back();
        }
    }


    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        for (size_t len = 0; len <= nums.size(); len++) {
            vector<int> current;
            subsets_rec(nums, 0, len, current, ret);
        }

        return ret;
    }
};

void test(vector<int>&& nums) {
    const auto ret = Solution().subsets(nums);

    for (auto&& list : ret) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    test({ 1,2,3, });
    test({ 0 });
}

