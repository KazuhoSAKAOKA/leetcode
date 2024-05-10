// leetcode_Q0786.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:

    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        auto compare = [&](const auto& a, const auto& b) {
            return ((static_cast<double>(arr[b.front()]) / static_cast<double>(arr[b.back()]) < static_cast<double>(arr[a.front()]) / static_cast<double>(arr[a.back()])));
            };
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> p_queue(compare);

        for (int i = 1; i < arr.size(); i++) {
            p_queue.push({ 0, i });
        }

        int index = 1;
        for (int i = 0; i < k - 1; i++) {
            const auto current = p_queue.top();
            p_queue.pop();
            const int& numerator_index = current.front();
            const int& denominator_index = current.back();
            if (numerator_index < denominator_index - 1) {
                p_queue.push({ numerator_index + 1, denominator_index });
            }
        }
        return vector<int>{arr[p_queue.top().front()], arr[p_queue.top().back()]};
    }
};

void test(vector<int>&& arr, int k) {
    const auto ans = Solution().kthSmallestPrimeFraction(arr, k);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
int main()
{
    test({ 1,2,3,5 }, 6);

    test({ 1,2,3,5 }, 3);
    test({ 1,7 }, 1);
}