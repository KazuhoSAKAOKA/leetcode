// leetcode_Q0525.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> count_map;

        int max_len = 0;
        count_map[0] = -1;
        int current = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                current--;
            }
            else {
                current++;
            }
            const auto it = count_map.find(current);
            if (it == cend(count_map)) {
                count_map[current] = i;
            }
            else {
                max_len = max(max_len, i - it->second);
            }
        }
        return max_len;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().findMaxLength(nums) << endl;
}

int main()
{
    test({ 0, 0, 1, 0, 0, 0, 1, 1, });
    test({0,1});
    test({0,1,0});
}