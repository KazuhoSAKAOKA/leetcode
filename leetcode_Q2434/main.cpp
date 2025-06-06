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
    string robotWithString(string s) {
        map<char, int> freq_map;
        for (auto&& c : s) {
            freq_map[c]++;
        }
        string ans;
        ans.reserve(size(s));
        vector<char> st;
        for(int i=0; i< size(s); i++) {
            while (!st.empty() && st.back() <= cbegin(freq_map)->first) {
                ans += st.back();
                st.pop_back();
            }
            auto it = freq_map.find(s[i]);
            if (it->second == 1) {
                freq_map.erase(it);
            }
            else {
                it->second--;
            }
            st.push_back(s[i]);
        }
        while (!st.empty()) {
            ans += st.back();
            st.pop_back();
        }
        return ans;
    }
};

void test(string&& s) {
    cout << Solution().robotWithString(s) << endl;
}
int main() {
	return 0;
}