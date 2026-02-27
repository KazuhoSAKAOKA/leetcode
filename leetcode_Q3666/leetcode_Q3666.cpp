#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    int minOperations(string s, int k) {
        if (k == 0) { return -1; }
        const auto n = static_cast<int>(size(s));
        const auto ones = static_cast<int>(count_if(cbegin(s), cend(s), [](char c) {return c == '1'; }));
        const auto zeros = n - ones;
        if (zeros == 0) { return 0; }
        if (zeros % k == 0) { return zeros / k; }
        vector<set<int>> candidates(2);
        for (int i = 0; i < n + 1; i++) {
            candidates[i % 2].insert(i);
        }
        constexpr int INF = INT_MAX;
        vector<int> costs(n + 1, INF);
        costs[ones] = 0;
        queue<int> q;
        q.push(ones);

        while (!q.empty()) {
            const auto cur = q.front();
            const auto cur_cost = costs[cur];
            q.pop();
            const int zero_to_one_low = max(0, cur + k - n);
            const auto one_to_zero_high = k - zero_to_one_low;
            const int zero_to_one_high = min(k, cur);
            const auto one_to_zero_low = k - zero_to_one_high;

            const auto next_upper = cur - zero_to_one_low + one_to_zero_high;
            const auto next_lower = cur - zero_to_one_high + one_to_zero_low;
            auto& target = candidates[(cur + k) % 2];
            const auto begin_it = target.lower_bound(next_lower);
            for (auto it = begin_it; it != cend(target) && *it <= next_upper;) {
                if (*it == n) {
                    return cur_cost + 1;
                }
                if (costs[*it] == INF) {
                    costs[*it] = cur_cost + 1;
                    q.push(*it);
                }
                it = target.erase(it);
            }
        }
        return -1;
    }
};

static void test(string&& s, int k) {
    cout << Solution().minOperations(s, k) << endl;
}

int main()
{
    test("110", 1);
    test("0101", 3);
    test("101", 2);
    return 0;
}