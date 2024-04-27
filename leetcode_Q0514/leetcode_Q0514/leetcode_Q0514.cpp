// leetcode_Q0514.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

class Solution {
public:

    using memo_key_t = pair<int, int>;
    using memo_t = map<memo_key_t, int>;

    static int rec(int size, const map<char, vector<int>>& ring_map, const string& key, int ring_index, int key_index, memo_t& memo) {
        if (key.size() == key_index) {
            return 0;
        }

        const auto state = memo_key_t(ring_index, key_index);
        const auto it = memo.find(state);
        if (it != cend(memo)) {
            return it->second;
        }
        int count = INT_MAX;
        const auto ring_indexes_it = ring_map.find(key[key_index]);

        for (auto&& index : ring_indexes_it->second) {
            int dial_distance;
            if (ring_index == index) {
                dial_distance = 0;
            }
            else {
                if (ring_index < index) {
                    dial_distance = min(index - ring_index, ring_index + size - index);
                }
                else {
                    dial_distance = min(ring_index - index, index + size - ring_index);
                }
            }

            count = min(count, 1 + dial_distance + rec(size, ring_map, key, index, key_index + 1, memo));
        }

        memo[state] = count;
        return count;
    }

    int findRotateSteps(string ring, string key) {
        map<char, vector<int>> ring_map;

        for (int i = 0; i < ring.size(); i++) {
            ring_map[ring[i]].emplace_back(i);
        }

        memo_t memo;
        return rec(static_cast<int>(ring.size()), ring_map, key, 0, 0, memo);
    }
};

void test(string&& ring, string&& key) {
    cout << Solution().findRotateSteps(ring, key) << endl;
}
int main(){
    test("godding", "gd");
    test("godding", "godding");
}