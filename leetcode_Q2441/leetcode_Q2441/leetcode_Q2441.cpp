// leetcode_Q2441.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int findMaxK(vector<int>& nums) {
        set<int> positives;
        unordered_set<int> negatives;

        for (auto&& value : nums) {
            if (value < 0) {
                negatives.insert(value);
            }
            else {
                positives.insert(value);
            }
        }
        for (auto it = crbegin(positives); it != crend(positives); ++it) {
            const auto value = *it;
            if (negatives.find(-value) != cend(negatives)) {
                return value;
            }
        }
        return -1;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().findMaxK(nums) << endl;
}

int main(){
    test({ -1,2,-3,3 });
    test({ -1,10,6,7,-7,1 });
    test({ -10,8,6,7,-2,-3 });
}