// leetcode_Q0169.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, size_t> map;
        for (auto&& value: nums) {
            map[value]++;
        }
        size_t maxcount = 0;
        int maxvalue = 0;
        for (auto [k, v] : map) {
            if (maxcount < v) {
                maxcount = v;
                maxvalue = k;
            }
        }
        return maxvalue;
    }
};

int main()
{

    vector<int> list1{ 3, 2, 3 };
    vector<int> list2{ 2, 2, 1, 1, 1, 2, 2 };
    vector<int> list3{ 6,6,6,7,7 };

//    cout << Solution().majorityElement(list1) << std::endl;
//    cout << Solution().majorityElement(list2) << std::endl;
    cout << Solution().majorityElement(list3) << std::endl;
}

