// leetcode_Q1229.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

int binary_search(const vector<vector<int>>& slots, int start1) {
    int right = size(slots);
    int left = 0;
    while (right - left > 1) {
        const auto mid = (left + right) / 2;
        if (start1 <= slots[mid][1]) {
            right = mid;
        }
        else {
            left = mid;
        }
    }
    return left;
}
class Solution {
public:

    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(begin(slots1), end(slots1), [](const auto& a, const auto& b) { return a.front() < b.front(); });
        sort(begin(slots2), end(slots2), [](const auto& a, const auto& b) { return a.front() < b.front(); });

        for (int i = 0; i < size(slots1); i++) {
            const auto start1 = slots1[i][0];
            const auto end1 = slots1[i][1];
            auto index2 = binary_search(slots2, start1);
            if (index2 == size(slots2)) {
                continue;
            }
            while (index2 < size(slots2) && slots2[index2][0] <= end1) {
                const auto range_start = max(start1, slots2[index2][0]);
                const auto range_end = min(end1, slots2[index2][1]);
                if (range_end - range_start >= duration) {
                    return vector<int>{range_start, range_start + duration};
                }
                index2++;
            }
        }
        return vector<int>();
    }
};

void test(vector<vector<int>>&& slots1, vector<vector<int>>&& slots2, int duration) {
    output(Solution().minAvailableDuration(slots1, slots2, duration));
}
int main()
{
    test(get_matrix_int("[[0,1],[100,1000100]]"), get_matrix_int("[[90,1000100],[0,2]]"), 1000000);
    test(get_matrix_int("[[10,50],[60,120],[140,210]]"), get_matrix_int("[[0,15],[60,70]]"), 8);
    test(get_matrix_int("[[10,50],[60,120],[140,210]]"), get_matrix_int("[[0,15],[60,70]]"), 12);
    return 0;
}