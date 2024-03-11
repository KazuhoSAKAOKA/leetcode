// leetcode_Q0791.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string customSortString(string order, string s) {
        unordered_map<char, int> order_map;
        for (int i = 0; i < order.size(); i++) {
            order_map[order[i]] = i;
        }

        stable_sort(begin(s), end(s), [&](const auto& a, const auto& b) { 
                const auto it1 = order_map.find(a);
                const auto it2 = order_map.find(b);
                if (it1 == cend(order_map)) {
                    return false;
                }
                else if (it2 == cend(order_map)) {
                    return true;
                }
                return it1->second < it2->second;
            });

        return s;
    }
};


void test(string&& order, string&& s) {
    cout << Solution().customSortString(order, s) << endl;
}

int main()
{
    test("cba", "fabcd");
    test("cba", "abcd");
    test("bcafg", "abcd");
}