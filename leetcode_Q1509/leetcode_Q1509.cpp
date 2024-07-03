// leetcode_Q1509.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int rec(map<int, int>::iterator it_f, map<int, int>::reverse_iterator it_r, map<int, int>& freq_map, int remain) {
        if (it_f == cend(freq_map) || it_r == crend(freq_map)) {
            return INT_MAX;
        }
        if(remain == 0){
            return abs(it_f->first - it_r->first);
        }
        int min_value = abs(it_f->first - it_r->first);
        it_f->second--;
        if (it_f->second > 0) {
            min_value = min(min_value, rec(it_f, it_r, freq_map, remain - 1));
        }
        else {
            min_value = min(min_value, rec(next(it_f), it_r, freq_map, remain - 1));
        }
        it_f->second++;
        
        it_r->second--;
        if (it_r->second > 0) {
            min_value = min(min_value, rec(it_f, it_r, freq_map, remain - 1));
        }
        else {
            min_value = min(min_value, rec(it_f, next(it_r), freq_map, remain - 1));
        }
        it_r->second++;

        return min_value;
    }


    int minDifference(vector<int>& nums) {
        map<int, int> freq_map;
        for (auto&& value : nums) {
            freq_map[value]++;
        }
        const auto it_f = begin(freq_map);
        const auto it_r = rbegin(freq_map);
        const auto ans = rec(it_f, it_r, freq_map, 3);
        return ans;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minDifference(nums) << endl;
}
int main()
{
    test(get_list_int("[5,3,2,4]"));
    test(get_list_int("[1,5,0,10,14]"));
    test(get_list_int("[3,100,20]"));
    return 0;
}