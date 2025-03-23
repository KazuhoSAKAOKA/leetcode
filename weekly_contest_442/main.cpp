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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int maxContainers(int n, int w, int maxWeight) {
        return min(n * n, maxWeight / w);
    }
};

void test(int n, int w, int maxWeight) {
    cout << Solution().maxContainers(n, w, maxWeight) << endl;
}

static void run() {
    test(2, 3, 15);
    test(3, 5, 20);
}
}
namespace problem2 {
class Solution {
public:

    static int intersect(const vector<int>& a, const vector<int>& b) {
        set<int> s;
        for (auto&& v : a) {
            s.insert(v);
        }
        for (auto&& v : b) {
            s.insert(v);
        }
        return static_cast<int>(size(s));
    }


    static int intersect(const set<int>& a, const set<int>& b) {
        int count = 0;
        for (auto&& v : a) {
            if (b.find(v) != cend(b)) {
                count++;
            }
        }
        return count;
    }
    struct union_find {

        std::vector<size_t> parents_;
        std::vector<size_t> sizes_;

        union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
            for (size_t i = 0; i < n; i++) {
                parents_[i] = i;
            }
        }

        size_t root(size_t x) {
            if (x == parents_[x]) { return x; }
            parents_[x] = root(parents_[x]);
            return parents_[x];
        }

        bool same(size_t x, size_t y) {
            return root(x) == root(y);
        }

        void unite(size_t x, size_t y) {
            const auto rootx = root(x);
            const auto rooty = root(y);
            if (rootx == rooty) { return; }
            if (sizes_[rootx] < sizes_[rooty]) {
                parents_[rootx] = rooty;
                sizes_[rooty] += sizes_[rootx];
            }
            else {
                parents_[rooty] = rootx;
                sizes_[rootx] += sizes_[rooty];
            }
        }

        size_t size(size_t x) {
            return sizes_[root(x)];
        }

        bool is_root(size_t x) {
            return root(x) == x;
        }
    };

    int numberOfComponents(vector<vector<int>>& properties, int k) {
        const auto n = size(properties);

        vector<set<int>> properties2(n);
        for (int i = 0; i < n; i++) {
            properties2[i].insert(cbegin(properties[i]), cend(properties[i]));
        }
        union_find uf(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(properties2[i], properties2[j]) >= k) {
                    uf.unite(i, j);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (uf.is_root(i)) {
                count++;
            }
        }
        return count;
    }
};
void test(vector<vector<int>>&& properties, int k) {
    cout << Solution().numberOfComponents(properties, k) << endl;
}
static void run() {
    test(get_matrix_int("[[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]]"), 1);
    test(get_matrix_int("[[1,2,3],[2,3,4],[4,3,5]]"), 2);
    test(get_matrix_int("[[1,1],[1,1]]"), 2);
}
}
namespace problem3 {
class Solution {
public:


    long long minTime(vector<int>& skill, vector<int>& mana) {
        const auto n = size(skill);
        const auto m = size(mana);
        //sort(begin(mana), end(mana), [](auto a, auto b) { return a > b; });
        vector<vector<long long>> times(m, vector<long long>(n + 1));

        for (int i = 0; i < n; i++) {
            times[0][i + 1] = times[0][i] + skill[i] * mana[0];
        }
        for (int j = 1; j < m; j++) {
            long long delay = 0;
            long long before_begin_time = times[j - 1][n];
            for (int i = n - 2; i >= 0; i--) {
                const long long time = skill[i] * mana[j];
                const long long my_end_time = times[j - 1][i + 1] + time;
                if (before_begin_time < my_end_time) {
                    delay = max(delay, my_end_time - before_begin_time);
                }
                before_begin_time -= time;
            }

            times[j][n] = times[j - 1][n] + skill[n - 1] * mana[j] + delay;
            for (int i = n - 2; i >= 0; i--) {
                times[j][i + 1] = times[j][i + 2] - skill[i + 1] * mana[j];
            }
        }
        return times[m - 1][n];
    }
};
void test(vector<int>&& skill, vector<int>&& mana) {
    cout << Solution().minTime(skill, mana) << endl;
}
static void run() {
    test(get_list_int("[1,5,2,4]"), get_list_int("[5,1,4,2]"));
    test(get_list_int("[1,1,1]"), get_list_int("[1,1,1]"));
    test(get_list_int("[1,2,3,4]"), get_list_int("[1,2]"));
}
}
namespace problem4 {
class Solution {
public:

    static inline void op(priority_queue<int>& pq, int v) {
        const int vf4 = v / 4;
        if (vf4 > 0) {
            pq.push(vf4);
        }
    }
    static long long min_zero(int l, int r) {
        priority_queue<int> pq;
        long long count = 0;
        for (int i = l; i <= r; i++) {
            pq.push(i);
        }
        while (!pq.empty()) {
            const auto v = pq.top();
            pq.pop();
            if (!pq.empty()) {
                const auto u = pq.top();
                pq.pop();
                op(pq, u);
            }
            op(pq, v);
            count++;
        }
        return count;
    }

    static long long get_min_zero(int v, unordered_map<int, long long>& memo) {
        if (v == 0) {
            return 0;
        }
        auto it = memo.find(v);
        if (it != cend(memo)) {
            return it->second;
        }
        long long count = get_min_zero(v / 4, memo) + 1;
        memo[v] = count;
        return count;
    }

    static long long min_zero2(int l, int r, map<int, long long>& memo) {
        long long count = 0;
        auto it = memo.lower_bound(l);
        long long cur_low = l;
        while (it!= cend(memo) && cur_low <= r) {
            const long long cur_counts = min(static_cast<long long>(it->first), static_cast<long long>(r)) - cur_low + 1;
            count += cur_counts * it->second;
            cur_low = it->first + 1;
            ++it;
        }
        return count / 2 + count % 2;
    }


    long long minOperations(vector<vector<int>>& queries) {
        long long total = 0;
        int max_r = 0;
        for (auto&& query : queries) {
            max_r = max(max_r, query.back());
        }

        map<int, long long> memo{ {0,0LL}, };
        int v = 4;
        long long op_count = 1;
        for (;;) {
            memo.insert({ v - 1, op_count });
            if (max_r < v - 1) {
                break;
            }
            op_count++;
            v *= 4;
        }
        for (auto&& query : queries) {
            total += min_zero2(query.front(), query.back(), memo);
        }
        return total;
    }
};
void test(vector<vector<int>>&& queries) {
    cout << Solution().minOperations(queries) << endl;
}
static void run() {
    test(get_matrix_int("[[2,4]]"));
    test(get_matrix_int("[[16,24]]"));
    test(get_matrix_int("[[1,2],[2,4]]"));
    test(get_matrix_int("[[2,6]]"));
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}