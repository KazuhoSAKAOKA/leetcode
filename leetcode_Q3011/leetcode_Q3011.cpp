// leetcode_Q3011.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static int counting_bits(int num) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            if ((num & (1 << i)) != 0) {
                count++;
            }
        }
        return count;
    }


    bool canSortArray(vector<int>& nums) {
        unordered_map<int, int> count_map;
        for (auto&& num : nums) {
            auto it = count_map.find(num);
            if (it == cend(count_map)) {
                count_map.insert({num,counting_bits(num)});
            }
        }

        for (int i = 0; i < size(nums); i++) {
            const auto current_num = nums[i];
            const auto current_bits = count_map[current_num];
            for (int j = i + 1; j < size(nums); j++) {
                if (current_num > nums[j]) {
                    if (count_map[nums[j]] != current_bits) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().canSortArray(nums) << endl;
}

int main()
{
    test(get_list_int("[8,4,2,30,15]"));
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[3,16,8,4,2]"));
    return 0;
}