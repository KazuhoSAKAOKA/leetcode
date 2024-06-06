// leetcode_Q0846.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        map<int, int> value_map;
        for (auto&& v : hand) {
            value_map[v]++;
        }

        auto erase_item = [](map<int, int>& m, map<int, int>::iterator it) {
                if (it->second == 1) {
                    m.erase(it);
                }
                else {
                    it->second--;
                }
            };

        while (!value_map.empty()) {
            auto it = begin(value_map);
            const auto base = it->first;
            erase_item(value_map, it);
            for (int i = 1; i < groupSize; i++) {
                if (value_map.empty()) { return false; }
                auto it_next = value_map.find(base + i);
                if (it_next == end(value_map)) {
                    return false;
                }
                erase_item(value_map, it_next);
            }
        }

        return true;
    }
};

void test(vector<int>&& hand, int groupSize) {
    cout << Solution().isNStraightHand(hand, groupSize) << endl;
}
int main()
{
    test(get_list_int("[1,2,3,6,2,3,4,7,8]"), 3);
    test(get_list_int("[1,2,3,4,5]"), 4);
    test(get_list_int("[1,2,3,4]"), 4);
}