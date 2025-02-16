// leetcode_Q1718.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    static bool rec(int n, vector<bool>& used, vector<int>& ans, int ans_index) {
        if (size(ans) == ans_index) {
            return true;
        }
        if (ans[ans_index] != 0) {
            return rec(n, used, ans, ans_index + 1);
        }


        for (int i = n; i >= 2; i--) {
            if (!used[i - 1]) {
                if (size(ans) <= ans_index + i) {
                    return false;
                }
                if (ans[ans_index + i] == 0) {
                    used[i - 1] = true;
                    ans[ans_index] = i;
                    ans[ans_index + i] = i;
                    if (rec(n, used, ans, ans_index + 1)) {
                        return true;
                    }
                    ans[ans_index] = 0;
                    ans[ans_index + i] = 0;
                    used[i - 1] = false;
                }
            }
        }
        if (!used[0]) {
            used[0] = true;
            ans[ans_index] = 1;
            if (rec(n, used, ans, ans_index + 1)) {
                return true;
            }
            ans[ans_index] = 0;
            used[0] = false;
        }
        return false;
    }

    vector<int> constructDistancedSequence(int n) {
        vector<int> ans((n - 1) * 2 + 1);
        vector<bool> used(n);
        rec(n, used, ans, 0);
        return ans;
    }
};
void test(int n) {
    output(Solution().constructDistancedSequence(n));
}
int main()
{
    test(3);
    test(5);
    return 0;
}