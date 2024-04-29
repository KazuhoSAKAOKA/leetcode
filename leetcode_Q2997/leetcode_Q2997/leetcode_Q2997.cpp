// leetcode_Q2997.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int b = 0;
        for (auto&& v : nums) {
            b ^= v;
        }
        int count = 0;
        for (int i = 0; i < 32; i++) {
            const int bit = 1 << i;
            if ((b & bit) != (k & bit)) {
                count++;
            }
        }

        return count;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().minOperations(nums, k) << endl;
}

int main()
{
    //const int v1 = 0;
    //const int v2 = 1;
    //cout << (v1 ^ v2) << endl;

    test({ 2,1,3,4, }, 1);
    test({ 2,0,2,0, }, 0);
}