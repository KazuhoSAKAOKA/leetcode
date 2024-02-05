// leetcode_Q0387.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        struct V{ int index; int count; };
        unordered_map<char, V> index_map;
        for (int i = 0; i < s.size(); i++) {
            auto it = index_map.find(s[i]);
            if (it != cend(index_map)) {
                it->second.count++;
            }
            else {
                index_map.insert(make_pair(s[i], V{ i, 1 }));
            }
        }
        int min_index = INT_MAX;
        for (auto&& kv : index_map) {
            if (kv.second.count == 1) {
                min_index = min(min_index, kv.second.index);
            }
        }
        return min_index == INT_MAX ? -1 : min_index;
    }
};

void test(string&& s) {
    cout << Solution().firstUniqChar(s) << endl;
}

int main()
{
    test("leetcode");
    test("loveleetcode");
    test("aabb");
}