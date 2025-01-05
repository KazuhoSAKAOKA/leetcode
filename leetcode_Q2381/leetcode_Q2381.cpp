// leetcode_Q2381.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static char get_shift(char c, int direction) {
        if (direction == 1) {
            if (c == 'z') {
                return 'a';
            }
            return c + 1;
        }
        else {
            if (c == 'a') {
                return 'z';
            }
            return c - 1;
        }
    }
    static void update(string& s, int start, int end_include, int direction) {
        for (int i = start; i <= end_include; i++) {
            s[i] = get_shift(s[i], direction);
        }
    }
    static string tle(string s, vector<vector<int>>& shifts) {
        for (auto&& shift : shifts) {
            const auto st = shift[0];
            const auto en = shift[1];
            const auto direction = shift[2];
            update(s, st, en, direction);
        }
        return s;
    }

    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        vector<int> prefix_sums(size(s) + 1);
        for (auto&& shift : shifts) {
            const auto st = shift[0];
            const auto en = shift[1];
            const auto direction = shift[2];
            const auto shift_val = direction == 1 ? 1 : -1;
            prefix_sums[st] += shift_val;
            prefix_sums[en + 1] -= shift_val;
        }
        string ans;
        ans.reserve(size(s));
        int current = 0;

        auto shift = [](char c, int value) {
            auto v = ((c -  'a') + value) % 26;
            if (v < 0) {
                v += 26;
            }
            return v + 'a';
            };

        for (int i = 0; i < size(s); i++) {
            current += prefix_sums[i];
            ans += shift(s[i], current);
        }

        return ans;
    }
};

void test(string&& s, vector<vector<int>>&& shifts) {
    cout << Solution().shiftingLetters(s, shifts) << endl;
}
int main()
{
    test("abc", get_matrix_int("[[0,1,0],[1,2,1],[0,2,1]]"));
    test("dztz", get_matrix_int("[[0,0,0],[1,1,1]]"));
    return 0;
}