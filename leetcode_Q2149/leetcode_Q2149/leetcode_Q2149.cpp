// leetcode_Q2149.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        queue<int> positive_queue;
        queue<int> negative_queue;
        vector<int> ans;
        ans.reserve(nums.size());
        bool positive = true;

        for (auto&& value : nums) {
            if (value < 0) {
                negative_queue.push(value);
            }
            else {
                positive_queue.push(value);
            }

            for (;;) {
                if (positive && !positive_queue.empty()) {
                    ans.emplace_back(positive_queue.front());
                    positive_queue.pop();
                    positive = false;
                }
                else if (!positive && !negative_queue.empty()) {
                    ans.emplace_back(negative_queue.front());
                    negative_queue.pop();
                    positive = true;
                }
                else {
                    break;
                }
            }
        }

        while (!positive_queue.empty() || !negative_queue.empty())
        {
            if (positive) {
                ans.emplace_back(positive_queue.front());
                positive_queue.pop();
                positive = false;
            }
            else {
                ans.emplace_back(negative_queue.front());
                negative_queue.pop();
                positive = true;
            }
        }

        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().rearrangeArray(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test({ 3,1,-2,-5,2,-4 });
    test({ -1,1 });

    test({ -1,-2,-3,-4, 4,3,2,1 });
}