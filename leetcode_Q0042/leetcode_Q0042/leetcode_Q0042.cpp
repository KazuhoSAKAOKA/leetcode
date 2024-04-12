// leetcode_Q0042.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) { return 0; }
        int total = 0;
        stack<int> height_stack;
        int current_height = height[0];

        for (int i = 1; i < height.size(); i++) {
            if (height[i] == current_height) {
                continue;
            }
            if (current_height < height[i]) {
                height_stack.push(i - 1);
                while (!height_stack.empty() && height[height_stack.top()] <= height[i]) {
                    const int trapped_height = min(height[i], height[height_stack.top()]);
                    total += (trapped_height - current_height) * (i - height_stack.top() - 1);
                    current_height = height[height_stack.top()];
                    height_stack.pop();
                }
                if (!height_stack.empty()) {
                    const int trapped_height = min(height[i], height[height_stack.top()]);
                    total += (trapped_height - current_height) * (i - height_stack.top() - 1);
                }
            }
            else {
                height_stack.push(i - 1);
            }
            current_height = height[i];
        }
        return total;
    }
};

void test(vector<int>&& height) {
    cout << Solution().trap(height) << endl;
}

int main()
{
    test({ 5,5,1,7,1,1,5,2,7,6 });
    test({ 0,1,0,2,1,0,1,3,2,1,2,1,});
    test({ 4,2,0,3,2,5 });
}