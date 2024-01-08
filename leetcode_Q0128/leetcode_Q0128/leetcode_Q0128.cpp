// leetcode_Q0128.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int max_value = 0;
        unordered_map<int, int> num_map;

        for (auto&& value : nums) {
            if (num_map[value] == 0) {
                int low_value = 0;
                int high_value = 0;
                if (num_map[value - 1] != 0) {
                    low_value = num_map[value - 1];
                }
                if (num_map[value + 1] != 0) {
                    high_value = num_map[value + 1];
                }

                const int new_value = low_value + high_value + 1;
                num_map[value] = new_value;
                if (low_value!=0) {
                    num_map[value - low_value] = new_value;
                }
                if (high_value!=0) {
                    num_map[value + high_value] = new_value;
                }

                max_value = max(max_value, new_value);

            }
        }
        return max_value;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().longestConsecutive(nums) << endl;
}

int main()
{
    test({ 100,4,200,1,3,2 });
    test({ 0,3,7,2,5,8,4,6,0,1 });
}

