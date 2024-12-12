// leetcode_Q2558.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> pq;
        for (auto&& gift : gifts) {
            pq.push(gift);
        }

        for (int i = 0; i < k; i++) {
            auto top = pq.top();
            pq.pop();
            pq.push(static_cast<int>(sqrt(top)));
        }

        long long total = 0;
        while (!pq.empty()) {
            total += pq.top();
            pq.pop();
        }
        return total;
    }
};

void test(vector<int>&& gifts, int k) {
    cout << Solution().pickGifts(gifts, k) << endl;
}

int main()
{
    test(get_list_int("[25,64,9,4,100]"), 4);
    test(get_list_int("[1,1,1,1]"), 4);
    return 0;
}