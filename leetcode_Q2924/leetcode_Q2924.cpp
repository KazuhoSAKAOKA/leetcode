// leetcode_Q2924.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        unordered_set<int> teams;
        for (int i = 0; i < n; i++) {
            teams.insert(i);
        }

        for (auto&& edge : edges) {
            teams.erase(edge.back());
        }
        if (size(teams) == 1) {
            return *(cbegin(teams));
        }
        return -1;
    }
};

static void test(int n, vector<vector<int>>&& edges) {
    cout << Solution().findChampion(n, edges) << endl;
}

int main()
{
    test(3, get_matrix_int("[[0,1],[1,2]]"));
    test(3, get_matrix_int("[[0,2],[1,3],[1,2]]"));
    return 0;
}