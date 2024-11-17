// leetcode_Q0862.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


class Solution {
public:
    static int tle(vector<int>& nums, int k) {
        vector<long long> prefix_sums(size(nums) + 1);
        for (int i = 0; i < size(nums); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }

        int min_length = INT_MAX;
        for (int i = 0; i < size(nums); i++) {
            for (int j = i + 1; j <= size(nums); j++) {
                if (prefix_sums[j] - prefix_sums[i] == k) {
                    min_length = min(min_length, j - i);
                }
            }
        }

        if (min_length == INT_MAX) { return -1; }
        return min_length;
    }

    int shortestSubarray(vector<int>& nums, int k) {
        int min_length = INT_MAX;
        auto compare = [](const pair<long long, int>& a, const pair<long long, int>& b) {
            return a.first > b.first;
            };

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, decltype(compare)> pq(compare);
        long long current_sum = 0;
        for (int r = 0; r < size(nums); r++) {
            current_sum += nums[r];
            if (k <= current_sum) {
                min_length = min(min_length, r + 1);
            }

            while (!pq.empty()) {
                const auto top = pq.top();
                if (current_sum - top.first < k) {
                    break;
                }
                min_length = min(min_length, r - top.second);
                pq.pop();
            }

            pq.push({ current_sum, r });
        }

        if (min_length == INT_MAX) { return -1; }
        return min_length;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().shortestSubarray(nums, k) << endl;
}
int main()
{
    test(get_list_int("[-28,81,-20,28,-29]"), 89);
    test(get_list_int("[84,-37,32,40,95]"), 167);
    test(get_list_int("[2,-1,2]"), 3);
    test(get_list_int("[48,99,37,4,-31]"), 140);
    test(get_list_int("[1]"), 1);
    test(get_list_int("[1,2]"), 4);
    return 0;
}