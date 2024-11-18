// leetcode_Q1652.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        if (k == 0) {
            return vector<int>(size(code), 0);
        }
        const int abs_k = abs(k);
        int current_sum = 0;
        for (int i = 0; i < abs_k; i++) {
            current_sum += code[i];
        }
        const int offset = k > 0 ? size(code) - 1 : abs_k;
        vector<int> ans(size(code));
        for (int i = 0; i < size(code); i++) {
            ans[(i + offset) % size(code)] = current_sum;
            current_sum += code[(i + abs_k) % size(code)];
            current_sum -= code[i];
        }
        return ans;
    }
};

void test(vector<int>&& code, int k) {
    output(Solution().decrypt(code, k));
}

int main()
{
    test(get_list_int("[2,4,9,3]"), -2);
    test(get_list_int("[5,7,1,4]"), 3);
    test(get_list_int("[1,2,3,4]"), 0);
    return 0;
}