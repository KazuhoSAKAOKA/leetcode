// leetcode_Q1608.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int specialArray(vector<int>& nums) {
        map<int, int> freq_map;
        for (auto&& value : nums) {
            freq_map[value]++;
        }

        vector<int> vals(freq_map.size(), 0);
        vector<int> sums(freq_map.size(), 0);
        int index = 0;
        for (auto&& [k, v] : freq_map) {
            vals[index] = k;
            sums[index] = v;
            index++;
        }

        for (int i = static_cast<int>(sums.size())-2; i >= 0; i--) {
            sums[i] += sums[i + 1];
        }

        auto get_x = [&]() {
                int min_x = 0;
                for (int i = 0; i < vals.size(); i++) {
                    if (vals[i] >= sums[i]) {
                        if (min_x < sums[i]) {
                            return sums[i];
                        }
                    }
                    min_x = vals[i];
                }
                return -1;
            };

        const int x = get_x();

        return x;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().specialArray(nums) << endl;
}

int main()
{
    test(get_list_int("[3]"));

    test(get_list_int("[3,6,7,7,0]"));
    test(get_list_int("[3,5]"));
    test(get_list_int("[0,0]"));
    test(get_list_int("[0,4,3,0,4]"));
}