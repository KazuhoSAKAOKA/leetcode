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
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> ans;
        for (int i = 0; i < size(words); i++) {
            if (words[i].find(x) != string::npos) {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};

int main() {
	return 0;
}