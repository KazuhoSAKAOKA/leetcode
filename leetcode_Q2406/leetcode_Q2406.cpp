// leetcode_Q2406.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        vector<int> starts(size(intervals));
        vector<int> ends(size(intervals));
        for (int i = 0; i < size(intervals); i++) {
            starts[i] = intervals[i].front();
            ends[i] = intervals[i].back();
        }
        sort(begin(starts), end(starts));
        sort(begin(ends), end(ends));


        int sindex = 0;
        int eindex = 0;
        int current_count = 0;
        int max_count = 0;

        while (sindex < size(starts) && eindex < size(ends)) {
            if (starts[sindex] <= ends[eindex]) {
                sindex++;
                current_count++;
                max_count = max(max_count, current_count);
            }
            else {
                current_count--;
                eindex++;
            }
        }

        return max_count;
    }
};

void test(vector<vector<int>>&& intervals) {
    cout << Solution().minGroups(intervals) << endl;
}

int main()
{
    test(get_matrix_int("[[1,5],[5,10]]"));
    test(get_matrix_int("[[1,1]]"));
    test(get_matrix_int("[[5,10],[6,8],[1,5],[2,3],[1,10]]"));
    test(get_matrix_int("[[1,3],[5,6],[8,10],[11,13]]"));
    return 0;
}