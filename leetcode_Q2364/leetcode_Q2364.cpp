// leetcode_Q2364.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static long long brute_force(const vector<int>& nums) {
        long long count = 0;
        for (int i = 0; i < size(nums); i++) {
            for (int j = i + 1; j < size(nums); j++) {
                if (j - i != nums[j] - nums[i]) {
                    count++;
                }
            }
        }
        return count;
    }

    long long countBadPairs(vector<int>& nums) {
        long long count = 0;
        map<int, long long> streak_map{ {nums[0], 1LL} };
        for (long long i = 1; i < size(nums); i++) {
            const auto it = streak_map.find(nums[i] - i);
            if (it != cend(streak_map)) {
                count += (i - it->second);
                it->second++;
            }
            else {
                streak_map.insert({ nums[i] - i , 1 });
                count += i;
            }
        }
        return count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().countBadPairs(nums) << endl;
}

int main()
{
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[1,3,4,5,5]"));
    test(get_list_int("[4,1,3,3]"));
    return 0;
}