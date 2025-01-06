// leetcode_Q1769.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> minOperations(string boxes) {
        const auto N = size(boxes);
        vector<int> ans(N);
        int left_costs = 0;
        int left_balls = 0;
        int right_costs = 0;
        int right_balls = 0;

        for (int i = 0; i < N; i++) {
            ans[i] += left_costs;
            ans[N - i - 1] += right_costs;
            if (boxes[i] == '1') {
                left_balls++;
            }
            left_costs += left_balls;

            if (boxes[N - i - 1] == '1') {
                right_balls++;
            }
            right_costs += right_balls;
        }
        return ans;
    }
};

void test(string&& boxes) {
    output(Solution().minOperations(boxes));
}

int main()
{
    test("110");
    test("001011");
    return 0;
}