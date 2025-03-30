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
    int shortestWay(string source, string target) {
        vector<bool> exists_source(26);
        vector<bool> exists_target(26);
        for (auto&& c : source) {
            exists_source[c - 'a'] = true;
        }
        for (auto&& c : target) {
            exists_target[c - 'a'] = true;
        }
        for (int i = 0; i < 26; i++) {
            if (exists_target[i] && !exists_source[i]) {
                return -1;
            }
        }
        
        int count = 0;
        int source_index = 0;
        for (int i = 0; i < size(target); i++) {
            auto pos = source.find(target[i], source_index);
            if (pos == string::npos) {
                count++;
                pos = source.find(target[i], 0);
            }
            source_index = pos + 1;
        }

        return count + 1;
    }
};

void test(string&& source, string&& target) {
    cout << Solution().shortestWay(source, target) << endl;
}
int main() {
    test("abc", "abcbc");
    test("abc", "acdbc");
    test("xyz", "xzyxz");
    return 0;
}