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
    static bool is_valid_code(const string& code) {
        if (code.empty()) { return false; }
        return all_of(cbegin(code), cend(code), [](char c) {
            return isalnum(c) || c == '_';
            });
    }
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        vector<int> indexes;
        map<string, int> orderes{ {"electronics",0}, {"grocery",1}, {"pharmacy",2}, {"restaurant",3} };
        for (int i = 0; i < size(code); i++) {
            if (is_valid_code(code[i]) && orderes.find(businessLine[i])!= cend(orderes) && isActive[i]) {
                indexes.emplace_back(i);
            }
        }
        sort(begin(indexes), end(indexes), [&](int a, int b) {
            if (businessLine[a] != businessLine[b]) {
                return code[a] < code[b];
            }
            return orderes[businessLine[a]] < orderes[businessLine[b]];
            });
        vector<string> ans(size(indexes));
        for (int i = 0; i < size(indexes); i++) {
            ans[i] = code[indexes[i]];
        }
        return ans;
    }
};

void test(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
    output(Solution().validateCoupons(code, businessLine, isActive));
}
static void run() {
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
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        union_find uf(c);

        for (auto&& conn : connections) {
            uf.unite(conn.front() - 1, conn.back() - 1);
        }
        map<int, set<int>> actives;
        for (int i = 0; i < c; i++) {
            actives[uf.root(i)].insert(i);
        }
        vector<bool> states(c, true);
        vector<int> ans;
        for (auto&& query : queries) {
            const auto q = query.front();
            const auto x = query.back();
            if (q == 1) {
                if (states[x - 1]) {
                    ans.emplace_back(x);
                }
                else {
                    auto& temp = actives[uf.root(x - 1)];
                    if (temp.empty()) {
                        ans.emplace_back(-1);
                    }
                    else {
                        ans.emplace_back(*cbegin(temp) + 1);
                    }
                }
            }
            else {
                states[x - 1] = false;
                actives[uf.root(x - 1)].erase(x - 1);
            }
        }

        return ans;
    }
};
void test(int c, vector<vector<int>>&& connections, vector<vector<int>>&& queries) {
    output(Solution().processQueries(c, connections, queries));
}
static void run() {
    test(5, get_matrix_int("[[1,2],[2,3],[3,4],[4,5]]"), get_matrix_int("[[1,3],[2,1],[1,1],[2,2],[1,2]]"));
    test(3, get_matrix_int("[]"), get_matrix_int("[[1,1],[2,1],[1,1]]"));
}
}
namespace problem3 {
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
    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }
    int minTime(int n, vector<vector<int>>& edges, int k) {
        auto check = [&](int time) {
            union_find uf(n);
            for (auto&& edge : edges) {
                if (edge.back() <= time) { continue; }
                uf.unite(edge[0], edge[1]);
            }
            int count = 0;
            for (int i = 0; i < n; i++) {
                if (uf.is_root(i)) { count++; }
            }
            return k <= count;
            };
        union_find uf(n);
        int max_time = 0;
        for (auto&& edge : edges) {
            uf.unite(edge[0], edge[1]);
            max_time = max(max_time, edge[2]);
        }
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (uf.is_root(i)) { count++; }
        }
        if (k <= count) {
            return 0;
        }
        return binary_search_meguru<int>(max_time, 0, check);
    }
};
static void test(int n, vector<vector<int>>&& edges, int k) {
    cout << Solution().minTime(n, edges, k) << endl;
}
static void run() {
    test(3, get_matrix_int("[[2,0,4242],[2,1,7212]]"), 2);
    test(2, get_matrix_int("[[0,1,3]]"), 2);
    test(3, get_matrix_int("[[0,1,2],[1,2,4]]"), 3);
    test(3, get_matrix_int("[[0,2,5]]"), 2);
}
}
namespace problem4 {
    class Solution {
    public:
        int minMoves(int sx, int sy, int tx, int ty) {
            set<pair<int, int>> visited{ {tx,ty} };
            struct state { int x; int y; int moves; };
            queue<state> q;
            q.push(state{ tx,ty, 0 });
            while (!q.empty()) {
                const state current = q.front();
                if (current.x == sx && current.y == sy) {
                    return current.moves;
                }
                q.pop();

                vector<pair<int, int>> nexts;
                if (current.x % 2 == 0 && (current.x / 2) >= current.y) {
                    nexts.emplace_back(make_pair(current.x / 2, current.y));
                }
                if (current.y % 2 == 0 && (current.y / 2) >= current.x) {
                    nexts.emplace_back(make_pair(current.x, current.y / 2));
                }
                if (current.y - current.x <= current.x) {
                    nexts.emplace_back(make_pair(current.x, current.y - current.x));
                }
                if (current.x - current.y <= current.y) {
                    nexts.emplace_back(make_pair(current.x - current.y, current.y));
                }

                for (auto&& next : nexts) {
                    if (sx <= next.first && sy <= next.second && visited.find(next) == cend(visited)) {
                        visited.insert({ next });
                        q.push(state{ next.first, next.second, current.moves + 1 });
                    }
                }
            }
            return -1;
        }
    };
    static void test(int sx, int sy, int tx, int ty) {
        cout << Solution().minMoves(sx, sy, tx, ty) << endl;
    }
    static void run() {
        test(1, 1, 3, 1);
        test(1, 1, 2, 2);
        test(1, 2, 5, 4);
        test(0, 1, 2, 3);
        test(5, 1, 350824, 287008);
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