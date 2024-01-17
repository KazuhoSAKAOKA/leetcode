// leetcode_Q1207.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> count_map;

        for (auto&& value : arr) {
            count_map[value]++;
        }
        unordered_set<int> count_set;
        for (auto&& kv : count_map) {
            if (count_set.find(kv.second) != cend(count_set)) {
                return false;
            }
            count_set.insert(kv.second);
        }

        return true;
    }
};

void test(vector<int>&& arr) {
    cout << Solution().uniqueOccurrences(arr) << endl;
}

int main()
{
    test({ 1,2,2,1,1,3 });
    test({ 1,2 });
    test({ -3,0,1,-3,1,1,1,-3,10,0 });
}