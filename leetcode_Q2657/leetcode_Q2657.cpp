// leetcode_Q2657.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        map<int, int> freqs;
        vector<int> ans(size(A));
        int count = 0;
        for (int i = 0; i < size(A); i++) {
            freqs[A[i]]++;
            if (freqs[A[i]] == 2) {
                count++;
            }
            freqs[B[i]]++;
            if (freqs[B[i]] == 2) {
                count++;
            }
            ans[i] = count;
        }
        return ans;
    }
};

void test(vector<int>&& A, vector<int>&& B) {
    output(Solution().findThePrefixCommonArray(A, B));
}
int main()
{

    return 0;
}