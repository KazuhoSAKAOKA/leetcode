// leetcode_Q0121.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
using namespace std;


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        std::vector<int> max_ranges(prices.size(), 0);
        int max_price = 0;
        for (auto i = static_cast<int>(prices.size()) - 1; 0 <= i; --i) {
            max_ranges[i] = max_price = max(prices[i], max_price);
        }
        int max_profit = 0;
        for (auto i = 0; i < prices.size() - 1; i++) {
            max_profit = max(max_ranges[i + 1] - prices[i], max_profit);
        }

        return max_profit;
    }
};

int main()
{
    std::vector<int> prices1{ 7,1,5,3,6,4 };
    std::cout << Solution().maxProfit(prices1) << std::endl;
    std::vector<int> prices2{ 7,6,4,3,1 };
    std::cout << Solution().maxProfit(prices2) << std::endl;
    std::vector<int> prices3(2 * 10 ^ 5, 100);
    std::cout << Solution().maxProfit(prices3) << std::endl;
}

