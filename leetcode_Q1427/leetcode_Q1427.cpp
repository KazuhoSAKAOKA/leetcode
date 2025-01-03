// leetcode_Q1427.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        const auto N = size(s);
        int current = 0;
        for (auto&& dir_and_amount : shift) {
            const auto dir = dir_and_amount.front();
            const auto amount = dir_and_amount.back();
            if (dir == 0) {
                current += amount;
                current %= N;
            }
            else {
                const auto m = amount % N;
                current += (N - m);
                current %= N;
            }
        }
        return s.substr(current, N - current) + s.substr(0, current);
    }
};

static void test(string&& s, vector<vector<int>>&& shift) {
    cout << Solution().stringShift(s, shift) << endl;
}
int main()
{
    test("abc", get_matrix_int("[[0,1],[1,2]]"));
    test("abcdefg", get_matrix_int("[[1,1],[1,1],[0,2],[1,3]]"));
    return 0;
}