// leetcode_Q1792.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    
    static double get_diff(int pass, int total) {
        const auto cur = static_cast<double>(pass) / static_cast<double>(total);
        const auto added = static_cast<double>(pass + 1) / static_cast<double>(total + 1);
        return added - cur;
    }
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        vector<int> extra_students_addes(size(classes));

        priority_queue<pair<double,int>> pq;

        for (int i = 0; i < size(classes); i++) {
            pq.push({ get_diff(classes[i].front(), classes[i].back()), i});
        }

        for (int i = 0; i < extraStudents; i++) {
            const auto [total, index] = pq.top();
            pq.pop();
            extra_students_addes[index]++;
            pq.push({ get_diff(classes[index].front() + extra_students_addes[index], classes[index].back() + extra_students_addes[index]), index });
        }

        double total_ratio = 0.0;
        for (int i = 0; i < size(classes); i++) {
            const auto ratio = static_cast<double>(classes[i].front() + extra_students_addes[i]) / static_cast<double>(classes[i].back() + extra_students_addes[i]);
            total_ratio += ratio;
        }
        return total_ratio / static_cast<double>(size(classes));
    }
};

void test(vector<vector<int>>&& classes, int extraStudents) {
    cout << Solution().maxAverageRatio(classes, extraStudents) << endl;
}
int main()
{
    test(get_matrix_int("[[1,2],[3,5],[2,2]]"), 2);
    test(get_matrix_int("[[2,4],[3,9],[4,5],[2,10]]"), 4);
    return 0;
}