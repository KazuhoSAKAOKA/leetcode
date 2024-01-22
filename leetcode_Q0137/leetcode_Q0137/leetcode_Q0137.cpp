// leetcode_Q0137.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int, int> values_map;
        for (auto&& value : nums) {
            values_map[value]++;
            if (values_map[value] == 3) {
                values_map.erase(value);
            }
        }

        return cbegin(values_map)->first;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().singleNumber(nums) << endl;
}

int main()
{
    test({ 2,2,3,2 });
    test({ 0,1,0,1,0,1,99 });
}