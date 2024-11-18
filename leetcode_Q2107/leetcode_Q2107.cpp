// leetcode_Q2107.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int shareCandies(vector<int>& candies, int k) {
        unordered_map<int, int> freq_map;
        for (auto&& candy : candies) {
            freq_map[candy]++;
        }
        const int uniques = size(freq_map);
        unordered_map<int, int> working_map;
        int current_uniques = uniques;
        for (int i = 0; i < k; i++) {
            working_map[candies[i]]++;
            if (working_map[candies[i]] == freq_map[candies[i]]) {
                current_uniques--;
            }
        }
        int max_uniques = current_uniques;

        for (int i = k; i < size(candies); i++) {
            working_map[candies[i]]++;
            if (working_map[candies[i]] == freq_map[candies[i]]) {
                current_uniques--;
            }

            working_map[candies[i - k]]--;
            if (working_map[candies[i - k]] == freq_map[candies[i - k]] - 1) {
                current_uniques++;
            }
            max_uniques = max(max_uniques, current_uniques);
        }
        return max_uniques;
    }
};
void test(vector<int>&& candies, int k) {
    cout << Solution().shareCandies(candies, k) << endl;
}

int main()
{
    test(get_list_int("[1,2,2,3,4,3]"), 3);
    test(get_list_int("[2,2,2,2,3,3]"), 2);
    test(get_list_int("[2,4,5]"), 0);
    return 0;
}