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

    static int counting(const string& s, int k) {
        int count = 0;
        set<char> distincts;
        if (s.empty()) { return 0; }
        for (auto&& c : s) {
            distincts.insert(c);
            if (size(distincts) > k) {
                distincts.clear();
                distincts.insert(c);
                count++;
            }
        }
        if (!distincts.empty()) {
            count++;
        }

        return count;
    }
    static int tle(string&& s, int k) {
        int max_partitions = 0;
        for (int i = 0; i < size(s); i++) {
            const auto cur = s[i];
            for (int j = 'a'; j <= 'z'; j++) {
                if (j == cur) { continue; }
                s[i] = j;
                max_partitions = max(max_partitions, counting(s, k));
            }
            s[i] = cur;
        }
        return max_partitions;
    }

    int maxPartitionsAfterOperations(string s, int k) {
        const auto n = size(s);
        vector<int> pref(n);
        vector<int> suff(n);
        vector<int> partition_start(n);

        int cur_count = 1;
        set<char> distincts;
        for (int i = 0; i < n; i++) {
            const auto& c = s[i];
            distincts.insert(c);
            if (size(distincts) > k) {
                distincts.clear();
                distincts.insert(c);
                cur_count++;
                pref[i] = cur_count;
            }
            else {
                pref[i] = cur_count;
            }
        }

    }
};

static void test(string&& s, int k) {
    cout << Solution().maxPartitionsAfterOperations(s, k) << endl;
}
int main() {
    test("accca", 2);
    test("aabaab", 3);
    test("xxyz", 1);
    return 0;
}