// leetcode_Q0122.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) { return 0; }
        int total = 0;
        bool holding = false;
        int before = prices[0];
        int floor_val = INT_MAX;

        for (int i = 1; i < prices.size(); i++) {
            const auto diff = prices[i] - before;
            if (!holding) {
                if (diff > 0) {
                    holding = true;
                    floor_val = before;
                }
            }
            else {
                if (diff < 0) {
                    holding = false;
                    total += before - floor_val;
                }
            }
            before = prices[i];
        }

        if (holding && floor_val < prices.back())
        {
            total += prices.back() - floor_val;
        }
        return total;
    }
};

void test(vector<int>&& prices) {
    cout << Solution().maxProfit(prices) << endl;
}

int main()
{
    test({ 7,1,5,3,6,4 });
    test({ 1,2,3,4,5 });
    test({ 7,6,4,3,1 });
}