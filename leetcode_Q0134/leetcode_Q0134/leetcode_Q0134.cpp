// leetcode_Q0134.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:

    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        map<int, int> segments;
        int tank = 0;
        int start = 0;
        for(int i = 0; i < gas.size(); i++){
            const int current_diff = gas[i] - cost[i];
            if (tank + current_diff < 0) {
                segments[i] = tank + current_diff;
                tank = 0;
                start = i + 1;
            }
            else {
                tank += current_diff;
            }
        }

        if (segments.empty()) { return 0; }

        for (auto&& kv :  segments) {
            tank += kv.second;
            if (tank < 0) {
                return -1;
            }
        }
        return start;
    }
};

void test(vector<int>&& gas, vector<int>&& cost) {
    cout << Solution().canCompleteCircuit(gas, cost) << endl;
}
int main()
{
    test({ 1,2,3,4,5 }, { 3,4,5,1,2 });
    test({ 2,3,4 }, { 3,4,3 });
}