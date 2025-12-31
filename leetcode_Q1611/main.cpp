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
#include <unordered_set>

using namespace std;
class Solution {
public:
    static int get_op2_mask(int n) {
        if (n == 0) { return 0; }
        int v = 1;
        while ((n & v) == 0) {
            v = (v << 1);
        }
        return (v << 1);
    }

    int minimumOneBitOperations(int n) {
        queue<pair<int, int>> q;
        q.push({ n,0 });
        unordered_set<int> visited{ n };

        auto try_queue = [&](int v, int count) {
            if (visited.count(v) == 0) {
                visited.insert(v);
                q.push({ v, count });
            }
            };

        while (!q.empty()) {
            const auto [cur, count] = q.front();
            if (cur == 0) {
                return count;
            }
            q.pop();
            if ((cur & 1) != 0) {
                try_queue((cur & (~1)), count + 1);
                if ((cur & 2) != 0) {
                    try_queue((cur & (~2)), count + 1);
                }
                else {
                    try_queue((cur | 2), count + 1);
                }
            }
            else {
                try_queue((cur | 1), count + 1);
                const auto m = get_op2_mask(cur);
                if ((cur & m) != 0) {
                    try_queue((cur & (~m)), count + 1);

                }
                else {
                    try_queue((cur | m), count + 1);
                }
            }
        }
        throw runtime_error("");
    }



    static int tle(int n) {
        queue<pair<int, int>> q;
        q.push({ n,0 });
        unordered_set<int> visited{ n };

        auto try_queue = [&](int v, int count) {
            if (visited.count(v) == 0) {
                visited.insert(v);
                q.push({ v, count });
            }
            };

        while (!q.empty()) {
            const auto [cur, count] = q.front();
            if (cur == 0) {
                return count;
            }
            q.pop();
            if ((cur & 1) != 0) {
                try_queue((cur & (~1)), count + 1);
                if ((cur & 2) != 0) {
                    try_queue((cur & (~2)), count + 1);
                }
                else {
                    try_queue((cur | 2), count + 1);
                }
            }
            else {
                try_queue((cur | 1), count + 1);
                const auto m = get_op2_mask(cur);
                if ((cur & m) != 0) {
                    try_queue((cur & (~m)), count + 1);

                }
                else {
                    try_queue((cur | m), count + 1);
                }
            }
        }
};
static void test(int n) {
    cout << Solution().minimumOneBitOperations(n) << endl;
}
int main() {
    test(6);
    test(3);
	return 0;
}