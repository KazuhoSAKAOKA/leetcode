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
    string processStr(string s) {
        string ans;
        for (auto&& c : s) {
            if ('a' <= c && c <= 'z') {
                ans += c;
            }
            else if (c == '*') {
                if (!ans.empty()) {
                    ans.pop_back();
                }
            }
            else if (c == '#') {
                ans += ans;
            }
            else if (c == '%') {
                string temp(crbegin(ans), crend(ans));
                ans = temp;
            }
        }
        return ans;
    }
};
static void test(string&& s) {
    cout << Solution().processStr(s) << endl;
}
static void run() {
    test("*%");
    test("a#b%*");
    test("z*#");
}
}
namespace problem2 {
class Solution {
public:
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

    int minCost(int n, vector<vector<int>>& edges, int k) {
        sort(begin(edges), end(edges), [](const vector<int>& a, const vector<int>& b) { return a.back() < b.back(); });
        union_find uf(n);
        int current_components = n;
        int index = 0;
//        vector<int> usings;
        int cost = 0;
        while (current_components > k) {
            const auto u = edges[index][0];
            const auto v = edges[index][1];
            if (uf.same(u, v)) {

            }
            else {
                cost = max(cost, edges[index][2]);
                uf.unite(u, v);
                current_components--;
            }
            index++;
        }
        
        return cost;
    }
};
static void test(int n, vector<vector<int>>&& edges, int k) {
    cout << Solution().minCost(n, edges, k) << endl;
}
static void run() {
    test(4, get_matrix_int("[[0,1,70],[1,2,84],[0,3,73],[0,2,59],[1,3,3]]"), 2);
    test(5, get_matrix_int("[[0,1,4],[1,2,3],[1,3,2],[3,4,6]]"), 2);
    test(4, get_matrix_int("[[0,1,5],[1,2,5],[2,3,5]]"), 1);
}
}
namespace problem3 {
class Solution {
public:

    template <typename T>
    class reversable {
        deque<T> items;
        bool reverse = false;
    public:
        void append(const T& v) {
            if (reverse) {
                items.push_front(v);
            }
            else {
                items.push_back(v);
            }
        }

        T& get_back() {
            if (reverse) {
                return items.front();
            }
            else {
                return items.back();
            }
        }
        void pop_back() {
            if (items.empty()) { return; }
            if (reverse) {
                return items.pop_front();
            }
            else {
                return items.pop_back();
            }
        }
        bool empty() const { return items.empty(); }

        void rev() {
            reverse = true;
        }

        void foreach(function<void(T&)> op) {
            for (auto&& item : items) {
                op(item);
            }
        }

        size_t get_size() const {
            return size(items);
        }
    };
    using line = reversable<char>;
    using block = reversable<line>;
    struct state_t {
        block blocks;

        void append(char c) {
            if (blocks.empty()) {
                blocks.append(line());
            }
            blocks.get_back().append(c);
        }

        void pop_back() {
            if (blocks.empty()) { return; }
            blocks.get_back().pop_back();
        }

        void duplicate() {
            if (blocks.empty()) { return; }
            blocks.append(blocks.get_back());
        }
        void reverse() {
            blocks.rev();
            blocks.foreach([](line& l) { l.rev(); });
        }

        char get_indexof(long long index) {
            
        }

    };


    char processStr(string s, long long k) {
        long long len = 0;
        for (auto&& c : s) {
            if ('a' <= c && c <= 'z') {
                len++;
            }
            else if (c == '*') {
                if (len > 0) {
                    len--;
                }
            }
            else if (c == '#') {
                len *= 2;
            }
        }

        if (len <= k) {
            return '.';
        }
        long long cur_len = len;
        long long target_index = k;
        for (auto it = crbegin(s); it != crend(s); ++it) {
            const auto c = *it;
            if ('a' <= c && c <= 'z') {
                if (cur_len == target_index + 1) {
                    return c;
                }
                cur_len--;
            }
            else if (c == '*') {
                cur_len++;
            }
            else if (c == '#') {
                cur_len /= 2;
                if (cur_len <= target_index) {
                    target_index %= cur_len;
                }
            }
            else if (c == '%') {
                target_index = cur_len - target_index - 1;
            }
        }
        throw exception();
    }
};

static void test(string&& s, long long k) {
    cout << Solution().processStr(s, k) << endl;
}
static void run() {
    test("cd%#*#", 3);
    test("a#b%*", 1);
    test("z*#", 0);
}
}
namespace problem4 {
class Solution {
public:

    static inline bool check_visited(int used_mask, int node) {
        return (used_mask & (1 << node)) != 0;
    }


    static int dfs_dual(int n, const vector<vector<int>>& graph, int a, int b, int used_mask, const string& label, map<int, map<pair<int, int>, int>>& memo) {
        if (a == b) {
            return 1;
        }

        const auto key = make_pair(min(a, b), max(a, b));
        const auto it = memo[used_mask].find(key);
        if (it != cend(memo[used_mask])) {
            return it->second;
        }

        int max_len = 0;
        map<char, vector<int>> froma;
        for (auto&& next : graph[a]) {
            if (!check_visited(used_mask, next)) {
                froma[label[next]].emplace_back(next);
            }
            else {
                if (next == b) {
                    max_len = max(max_len, 2);
                }
            }
        }
        for (auto&& next : graph[b]) {
            if (!check_visited(used_mask, next)) {
                auto it = froma.find(label[next]);
                if (it != cend(froma)) {
                    const auto used_flag_b = 1 << next;
                    for (auto&& next_a : it->second) {
                        if (next == next_a) {
                            max_len = max(max_len, 3);
                        }
                        else {
                            const auto used_flag_a = 1 << next_a;
                            max_len = max(max_len, dfs_dual(n, graph, next_a, next, used_mask | used_flag_b | used_flag_a, label, memo) + 2);
                        }
                    }
                }
            }
        }
        memo[used_mask][key] = max_len;
        return max_len;
    }


    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        map<int, vector<int>> freqs;
        for (int i = 0; i < n; i++) {
            freqs[label[i]].emplace_back(i);
        }
        int max_len = 1;
        map<int, map<pair<int, int>, int>> memo;
        for (auto&& [_, nodes] : freqs) {
            if (size(nodes) > 1) {
                for (int i = 0; i < size(nodes); i++) {
                    const auto u = nodes[i];
                    for (int j = i + 1; j < size(nodes); j++) {
                        const auto v = nodes[j];
                        max_len = max(max_len, dfs_dual(n, graph, u, v, (1 << u) | (1 << v), label, memo));
                    }
                }
            }
        }
        return max_len;
    }
};
static void test(int n, vector<vector<int>>&& edges, string label) {
    cout << Solution().maxLen(n, edges, label) << endl;
}

static void run() {
    test(3, get_matrix_int("[[0,1],[1,2]]"), "aba");
    test(3, get_matrix_int("[[0,1],[0,2]]"), "abc");
    test(4, get_matrix_int("[[0,2],[0,3],[3,1]]"), "bbac");
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