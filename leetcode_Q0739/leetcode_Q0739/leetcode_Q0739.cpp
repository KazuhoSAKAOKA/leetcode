// leetcode_Q0739.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(), 0);
        stack<int> indexes_stack;

        for (int i = 0; i < temperatures.size(); i++) {
            while(!indexes_stack.empty() && temperatures[indexes_stack.top()] < temperatures[i]){
                ans[indexes_stack.top()] = i - indexes_stack.top();
                indexes_stack.pop();
            }
            indexes_stack.push(i);
        }
        while (!indexes_stack.empty()) {
            ans[indexes_stack.top()] = 0;
            indexes_stack.pop();
        }

        return ans;
    }
};

void test(vector<int>&& temperatures) {
    const auto ans = Solution().dailyTemperatures(temperatures);

    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test({ 73,74,75,71,69,72,76,73 });
    test({ 30,40,50,60 });
    test({ 30,60,90 });

}