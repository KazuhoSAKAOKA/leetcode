// leetcode_Q0907.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <stack>

using namespace std;



class Solution {
public:
    //using memo_key_type = pair<int, int>;
    //using memo_type = map<memo_key_type, int>;
    //int64_t rec(const vector<int>& arr, int index, int min_value, memo_type& memo) {
    //    const auto key = memo_key_type(index, min_value);
    //    const auto it = memo.find(key);
    //    if (it != cend(memo)) {
    //        return it->second;
    //    }

    //    const auto current_min_value = min(min_value, arr[index]);
    //    int64_t sum = 0;
    //    sum += current_min_value;
    //    if (index < arr.size() - 1) {
    //        sum += rec(arr, index + 1, current_min_value, memo);
    //    }
    //    memo[key] = sum;
    //    return sum;
    //}
    //int a(const vector<int>& arr)
    //{
    //    memo_type memo;
    //    int64_t sum = 0;
    //    vector<int> current;
    //    for (int i = 0; i < arr.size(); i++)
    //    {
    //        sum += rec(arr, i, INT_MAX, memo);
    //        sum %= mod;
    //    }
    //    return sum;
    //}
    int sumSubarrayMins(vector<int>& arr) {
        vector<int> dp(arr.size(), 0);
        stack<int> monotonic_stack;
        dp[0] = arr[0];
        monotonic_stack.push(0);
        for (int i = 1; i < arr.size(); i++) {
            while (!monotonic_stack.empty() && arr[i] < arr[monotonic_stack.top()]) {
                monotonic_stack.pop();
            }
            if (arr[i - 1] < arr[i]) {
                dp[i] = dp[i - 1] + arr[i];
            }
            else {
                if (monotonic_stack.empty()) {
                    dp[i] = (i + 1) * arr[i];
                }
                else{
                    dp[i] = dp[monotonic_stack.top()] + (i - monotonic_stack.top()) * arr[i];
                }
            }
            monotonic_stack.push(i);
        }
        constexpr int64_t mod = 1000000007;
        return accumulate(cbegin(dp), cend(dp), 0, [](const auto& t, const auto& v) { return (t + v) % mod; });
    }
};

void test(vector<int>&& arr) {
    cout << Solution().sumSubarrayMins(arr) << endl;
}

int main()
{
    test({ 3,1,2,4 });
    test({ 11,81,94,43,3 });

}