// leetcode_Q0041.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        set<int> exists;
        for (auto&& value : nums) {
            if (value <= 0) { continue; }
            exists.insert(value);
        }
        for (int i = 0; i < nums.size(); i++) {
            if (exists.find(i + 1) == cend(exists)) {
                return i + 1;
            }
        }
        return *prev(exists.end()) + 1;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().firstMissingPositive(nums) << endl;
}


int main()
{
    test({ 1,2,0, });
    test({ 3,4,-1,1, });
    test({ 7,8,9,11,12, });
}