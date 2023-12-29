// leetcode_Q0011.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using namespace std;


class Solution {
public:

    int BruteForce(const vector<int>& height) {
        size_t max_amount = 0;

        for (size_t left = 0; left < height.size(); left++) {
            for (size_t right = left + 1; right < height.size(); right++) {
                const auto amount = (right - left) * min(height[left], height[right]);
                max_amount = max(max_amount, amount);
            }
        }
        return max_amount;
    }


    int maxArea(vector<int>& height) {

    }
};



void test(vector<int>&& list)
{
    std::cout << Solution().maxArea(list) << std::endl;
}

int main()
{
    test(vector<int>{1, 8, 6, 2, 5, 4, 8, 3, 7});
    test(vector<int>{1,1,});
    test(vector<int>{});
    test(vector<int>{});
    test(vector<int>{});
    test(vector<int>{});
}

