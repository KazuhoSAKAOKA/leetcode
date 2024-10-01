// leetcode_Q1497.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        vector<size_t> mod_exists(k);
        vector<size_t> pair_indexes(k);
        pair_indexes[0] = 0;
        for (size_t i = 1; i < k; i++) {
            pair_indexes[i] = k - i;
        }
        size_t count = 0;
        for (auto&& value : arr) {

            const auto v = ((value % k) + k) % k;

            if (mod_exists[pair_indexes[v]]) {
                count++;
                mod_exists[pair_indexes[v]]--;
            }
            else {
                mod_exists[v]++;
            }
        }
        return count * 2 == size(arr);
    }
};

void test(vector<int>&& arr, int k) {
    cout << Solution().canArrange(arr, k) << endl;
}

int main()
{
    test(get_list_int("[-4,-7,5,2,9,1,10,4,-8,-3]"), 3);
    test(get_list_int("[1,2,3,4,5,10,6,7,8,9]"), 5);
    test(get_list_int("[1,2,3,4,5,6]"), 7);
    test(get_list_int("[1,2,3,4,5,6]"), 10);

    return 0;
}