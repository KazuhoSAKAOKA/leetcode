// leetcode_Q2838.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "./../utility/leetcode_testcase_helper.h"


using namespace std;
class Solution {
public:
    vector<long long> maximumCoins(vector<int>& heroes, vector<int>& monsters, vector<int>& coins) {
        map<int, long long> monster_vals;
        for (size_t i = 0; i < size(monsters); i++) {
            monster_vals[monsters[i]] += coins[i];
        }
        vector<long long> prefix_sums(size(monster_vals) + 1);
        map<size_t, size_t> power_indexes;

        size_t index = 0;
        for (auto&& [monster_power, coin_sum] : monster_vals) {
            prefix_sums[index + 1] = prefix_sums[index] + coin_sum;
            power_indexes[monster_power] = index + 1;
            index++;
        }
        vector<long long> ans;
        ans.reserve(size(heroes));

        for (auto&& hero_power : heroes) {
            const auto it = power_indexes.upper_bound(hero_power);
            if (it == cbegin(power_indexes)) {
                ans.emplace_back(0);
            }
            else {
                const auto it1 = prev(it);
                ans.emplace_back(prefix_sums[it1->second]);
            }
        }


        return ans;
    }
};

void test(vector<int>&& heroes, vector<int>&& monsters, vector<int>&& coins) {
    output(Solution().maximumCoins(heroes, monsters, coins));
}

int main()
{
    test(get_list_int("[1,4,2]"), get_list_int("[1,1,5,2,3]"), get_list_int("[2,3,4,5,6]"));
    test(get_list_int("[5]"), get_list_int("[2,3,1,2]"), get_list_int("[10,6,5,2]"));
    test(get_list_int("[4,4]"), get_list_int("[5,7,8]"), get_list_int("[1,1,1]"));
    return 0;
}