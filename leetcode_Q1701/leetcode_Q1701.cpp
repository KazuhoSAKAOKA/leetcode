// leetcode_Q1701.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        if (customers.empty()) {
            return 0.0;
        }
        long long total_wait = 0;
        int current_time = 0;
        for (auto&& values : customers) {
            const int arrive = values[0];
            const int time = values[1];
            const int begin = max(current_time, arrive);
            const int wait = begin + time - arrive;
            total_wait += static_cast<long long>(wait);
            current_time = begin + time;
        }

        return static_cast<double>(total_wait) / static_cast<double>(customers.size());
    }
};

void test(vector<vector<int>>&& customers) {
    cout << Solution().averageWaitingTime(customers) << endl;
}

int main() {
    test(get_matrix_int("[[1,2],[2,5],[4,3]]"));
    test(get_matrix_int("[[5,2],[5,4],[10,3],[20,1]]"));
    return 0;
}