#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;
class Solution {
public:
    string pushDominoes(string dominoes) {
        const auto n = size(dominoes);
        const unordered_map<char, int> dir_map{ {'L',-1},{'R',1} };
        auto update_map = [&](int index, map<int, char>& mp) {
            const auto it = dir_map.find(dominoes[index]);
            if (it == cend(dir_map)) { return; }
            const auto next = index + it->second;
            if (next < 0 || n <= next) { return; }
            if (dominoes[next] != '.') { return; }
            const auto it2 = mp.find(next);
            if (it2 == cend(mp)) {
                mp.insert({ next, dominoes[index]});
            }
            else {
                mp.erase(it2);
            }
            };

        map<int, char> next_map;
        for (int i = 0; i < n; i++) {
            update_map(i, next_map);
        }

        while (!next_map.empty()) {
            map<int, char> current_map;
            for (auto&& [index, c] : next_map) {
                dominoes[index] = c;
            }
            for (auto&& [index, c] : next_map) {
                update_map(index, current_map);
            }
            next_map = current_map;
        }

        return dominoes;
    }
};

void test(string&& dominoes) {
    cout << Solution().pushDominoes(dominoes) << endl;
}
int main() {
    test(".L.R...LR..L..");
    test("RR.L");
    return 0;
}