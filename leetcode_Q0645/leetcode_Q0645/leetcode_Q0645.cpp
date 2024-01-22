// leetcode_Q0645.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        unordered_set<int> remain;
        for (int i = 0; i < nums.size(); i++) {
            remain.insert(i + 1);
        }
        unordered_set<int> values;
        int duplicated = -1;
        for (auto&& num : nums) {
            if (values.find(num) != cend(values)) {
                duplicated = num;
            }
            else {
                values.insert(num);
                remain.erase(num);
            }
        }
        return { duplicated, *cbegin(remain) };
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().findErrorNums(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test({ 1,2,2,4 });
    test({1,1});
}