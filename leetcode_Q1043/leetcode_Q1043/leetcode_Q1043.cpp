// leetcode_Q1043.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class Solution {
public:
    using memo_key_type = int;
    using memo_type = map<memo_key_type, int>;
    int rec(const vector<int>& arr, int k, int index, memo_type& memo) {

        if (arr.size() == index) {
            return 0;
        }

        const auto key = index;
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        const auto arr_it = next(cbegin(arr), index);
        if (arr.size() - k <= index) {
            const auto remain_max = *max_element(arr_it, cend(arr));
            memo[key] = remain_max * (arr.size() - index);
            return remain_max * (arr.size() - index);
        }

        int max_value = 0;
        int current = 0;
        for (int i = 0; i < k; i++) {
            current = *max_element(arr_it, next(arr_it, i + 1)) * (i + 1);
            max_value = max(max_value, current + rec(arr, k, index + i + 1, memo));
        }

        memo[key] = max_value;
        return max_value;
    }



    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memo_type memo;

        return rec(arr, k, 0, memo);
    }
};


void test(vector<int>&& arr, int k) {
    cout << Solution().maxSumAfterPartitioning(arr, k) << endl;
}

int main()
{
    test({ 1,15,7,9,2,5,10 }, 3);
    test({ 1,4,1,5,7,3,6,1,9,9,3 }, 4);
    test({ 1,}, 1);
}