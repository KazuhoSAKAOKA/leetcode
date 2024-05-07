// leetcode_Q0011.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using namespace std;


class Solution {
public:


    int maxArea(vector<int>& height) {
        int max_amount = 0;

        int left = 0;
        int right = height.size() - 1;

        while(left < right) {
            const int current_amount = min(height[left], height[right]) * (right - left);
            max_amount = max(max_amount, current_amount);
            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }
        }
        return max_amount;
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

