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
    bool reorderedPowerOf2(int n) {
        auto digit_map = [](const string& s)->map<char, int> {
            map<char, int> mp;
            for (auto&& c : s) { mp[c]++; }
            return mp;
            };

        set<map<char, int>> p2_digits;
        for (int i = 0; i < 32; i++) {
            p2_digits.insert(digit_map(to_string(1 << i)));
        }
        return p2_digits.find(digit_map(to_string(n)))!= cend(p2_digits);
    }
};


int main() {



	return 0;
}