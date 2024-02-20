// leetcode_Q0268.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int64_t total = 0;
        for (auto&& value : nums) {
            total += static_cast<int64_t>(value);
        }
        int64_t n = static_cast<int64_t>(nums.size()) + 1;
        int64_t expected = n * (n - 1) / 2;
        return static_cast<int>(expected - total);
    }
};

void test(vector<int>&& nums) {
    cout << Solution().missingNumber(nums) << endl;
}

int main()
{
    test({ 3,0,1 });
    test({ 0,1 });
    test({ 9,6,4,2,3,5,7,0,1 });

}