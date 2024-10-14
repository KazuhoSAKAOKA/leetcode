// leetcode_Q2530.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {

        priority_queue<int> pq;
        for (auto&& num : nums) {
            pq.push(num);
        }

        long long total = 0;
        for (int i = 0; i < k; i++) {
            const auto num = pq.top();
            total += static_cast<long long>(num);
            pq.pop();
            pq.push((num + 2) / 3);
        }

        return total;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maxKelements(nums, k) << endl;
}

int main()
{
    test(get_list_int("[10,10,10,10,10]"), 5);
    test(get_list_int("[1,10,3,3,3]"), 3);
    return 0;
}