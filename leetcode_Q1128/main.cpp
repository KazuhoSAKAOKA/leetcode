#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        map<pair<int, int>, int> freqs;
        int total_count = 0;
        for (auto&& domino : dominoes) {
            const pair<int, int> key = { min(domino[0], domino[1]), max(domino[0], domino[1]) };
            const auto it = freqs.find(key);
            if (it != cend(freqs)) {
                total_count += it->second;
                it->second++;
            }
            else {
                freqs.insert({key, 1});
            }
        }
        return total_count;
    }
};


int main() {
	return 0;
}