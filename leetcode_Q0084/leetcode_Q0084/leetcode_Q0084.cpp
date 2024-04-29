// leetcode_Q0084.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;


class Solution {
public:


    int largestRectangleArea(vector<int>& heights) {
        int max_area = 0;
        vector<int> height_index_stack;
        height_index_stack.push_back(-1);
        for (int i = 0; i < heights.size(); i++) {
            while (height_index_stack.back() != -1 && heights[height_index_stack.back()] >= heights[i]) {
                const int pos = height_index_stack.back();
                height_index_stack.pop_back();
                const auto height = heights[pos];
                const auto pos_depth = height_index_stack.back();
                const auto area = (i - pos_depth - 1) * (height);
                max_area = max(max_area, area);
            }
            height_index_stack.push_back(i);
        }

        while (height_index_stack.back() != -1) {
            const auto pos = height_index_stack.back();
            height_index_stack.pop_back();
            const auto height = heights[pos];
            const auto pos_depth = height_index_stack.back();
            const auto area = (static_cast<int>(heights.size()) - pos_depth - 1) * height;
            max_area = max(max_area, area);
        }
        return max_area;
    }
};


void test(vector<int>&& heights) {
    cout << Solution().largestRectangleArea(heights) << endl;
}

int main()
{
    test({ 2,1,2 });
    test({5,4,1,2,});
    test({ 2,1,5,6,2,3, });
    test({ 2,4, });
}