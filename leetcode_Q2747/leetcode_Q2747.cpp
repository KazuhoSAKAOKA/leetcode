#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        const int Q = size(queries);
        vector<int> qindexes(Q);
        for (int i = 0; i < Q; i++) { qindexes[i] = i; }
        sort(begin(qindexes), end(qindexes), [&](int a, int b)-> bool { return queries[a] < queries[b]; });

        const int m = size(logs);
        vector<int> lindexes(m);
        for (int i = 0; i < m; i++) { lindexes[i] = i; }
        sort(begin(lindexes), end(lindexes), [&](int a, int b)-> bool { return logs[a][1] < logs[b][1]; });

        vector<int> ans(Q);

        map<int, int> exists;
        int index = 0;
        int l = 0;
        int r = 0;
        for (int i = 0; i < Q; i++) {
            const auto rtime = queries[qindexes[i]];
            while (r < m && logs[lindexes[r]][1] <= rtime) {
                auto it = exists.find(logs[lindexes[r]][0]);
                if (it != end(exists)) {
                    it->second++;
                }
                else {
                    exists.insert({ logs[lindexes[r]][0], 1 });
                }
                r++;
            }
            const int ltime = rtime - x;
            while (l < m && logs[lindexes[l]][1] < ltime) {
                auto it = exists.find(logs[lindexes[l]][0]);
                if (it->second == 1) {
                    exists.erase(it);
                }
                else {
                    it->second--;
                }
                l++;
            }
            ans[qindexes[i]] = n - static_cast<int>(size(exists));
        }
        return ans;
    }
};
static void test(int n, vector<vector<int>>&& logs, int x, vector<int>&& queries) {
    output(Solution().countServers(n, logs, x, queries));
}
static void run() {
    test(3, get_matrix_int("[[1,3],[2,6],[1,5]]"), 5, get_list_int("[10,11]"));
    test(3, get_matrix_int("[[2,4],[2,1],[1,2],[3,1]]"), 2, get_list_int("[3,4]"));
    test(3, get_matrix_int("[[1,35],[1,32],[1,11],[1,39],[2,29]]"), 8, get_list_int("[38,30,23,33,15,31,34,22,11,14]"));
}

int main() {
	run();
	return 0;
}
