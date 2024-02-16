// leetcode_Q1481.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <algorithm>
using namespace std;


class Solution {
public:
    /*
    using memo_key_type = pair<int, int>;
    using memo_type = map<memo_key_type, int>;
    int rec(const map<int, int>& count_map, map<int, int>::const_iterator it, int k, memo_type& memo) {
        if (it == cend(count_map)) {
            if (k != 0) {
                return INT_MAX - 1;
            }
            return 0;
        }

        const auto key = memo_key_type(it->first, k);
        const auto memo_it = memo.find(key);
        if (memo_it != cend(memo)) {
            return memo_it->second;
        }
        const auto next_it = next(it);
        
        int min_value = rec(count_map, next_it, k, memo) + 1;
        for (int i = 1; i <= min(it->second - 1, k); i++) {
            min_value = min(min_value, rec(count_map, next_it, k - i, memo) + 1);
        }
        if (it->second <= k) {
            min_value = min(min_value, rec(count_map, next_it, k - it->second, memo));
        }
        memo[key] = min_value;
        return min_value;
    }
    */


    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        map<int, int> count_map;
        for (auto&& value : arr) {
            count_map[value]++;
        }
        vector<int> count_list;
        count_list.reserve(count_map.size());
        for (auto&& [_, value] : count_map) {
            count_list.emplace_back(value);
        }
        sort(begin(count_list), end(count_list));
        int count = 0;
        int index = 0;
        while (index< count_list.size() && count + count_list[index] <= k) {
            count += count_list[index++];
        }
        return count_list.size() - index;
    }
};


void test(vector<int>&& arr, int k) {
    cout << Solution().findLeastNumOfUniqueInts(arr, k) << endl;
}
int main()
{
    test({ 1 }, 1);
    test({ 5,5,4 },1 );
    test({ 4,3,1,1,3,3,2},3 );
}