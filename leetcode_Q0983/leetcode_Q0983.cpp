// leetcode_Q0983.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int rec(const vector<int>& days, int index, const vector<int>& costs, int before, int remain, map<pair<int, int>, int>& memo) {
        if (size(days) == index) {
            return 0;
        }
        const auto key = make_pair(index, remain);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }
        int cost = INT_MAX;
        const auto elap = days[index] - before;
        if (elap <= remain) {
            const auto after_remain = remain - elap;
            cost = min(cost, rec(days, index + 1, costs, days[index], after_remain, memo));
            cost = min(cost, rec(days, index + 1, costs, days[index], max(after_remain, 6), memo) + costs[1]);
            cost = min(cost, rec(days, index + 1, costs, days[index], max(after_remain, 29), memo) + costs[2]);
        }
        else {
            cost = min(cost, rec(days, index + 1, costs, days[index], 0, memo) + costs[0]);
            cost = min(cost, rec(days, index + 1, costs, days[index], 6, memo) + costs[1]);
            cost = min(cost, rec(days, index + 1, costs, days[index], 29, memo) + costs[2]);
        }
        memo[key] = cost;
        return cost;
    }

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        map<pair<int, int>, int> memo;
        return rec(days, 0, costs, 0, -1, memo);
    }
};

void test(vector<int>&& days, vector<int>&& costs) {
    cout << Solution().mincostTickets(days, costs) << endl;
}

int main()
{
    test(get_list_int("[1,4,6,7,8,20]"), get_list_int("[2,7,15]"));
    test(get_list_int("[1,2,3,4,5,6,7,8,9,10,30,31]"), get_list_int("[2,7,15]"));
    return 0;
}