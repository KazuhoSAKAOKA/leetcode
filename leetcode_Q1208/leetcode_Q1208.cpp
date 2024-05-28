// leetcode_Q1208.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        vector<int> costs(s.size(), 0);
        for (int i = 0; i < s.size(); i++) {
            costs[i] = abs(static_cast<int>(s[i]) - static_cast<int>(t[i]));
        }

        int max_length = 0;
        int current_cost = 0;
        int l = 0;
        for (int r = 0; r < costs.size(); r++) {
            current_cost += costs[r];
            if (maxCost < current_cost && l < r) {
                current_cost -= costs[l];
                l++;
            }
            if (current_cost <= maxCost) {
                max_length = (r - l) + 1;
            }
        }
        return max_length;
    }
};

void test(string&& s, string&& t, int maxCost) {
    cout << Solution().equalSubstring(s, t, maxCost) << endl;
}
int main(){
    test("abcd", "cdef", 1);
    test("abcd", "bcdf", 3);
    test("abcd", "cdef", 3);
    test("abcd", "acde", 0);
}