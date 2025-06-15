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
    static int digit_sum(int num) {
        if (num == 0) { return 0; }
        int cur = num;
        int value = 0;
        while (cur > 0) {
            value += cur % 10;
            cur /= 10;
        }
        return value;
    }
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < size(nums); i++) {
            if (digit_sum(nums[i]) == i) {
                return i;
            }
        }
        return -1;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().smallestIndex(nums) << endl;
}

static void run() {
    test(get_list_int("[1,3,2]"));
    test(get_list_int("[1,10,11]"));
    test(get_list_int("[1,2,3]"));
}
}
namespace problem2 {
class Solution {
public:


    template<typename T>
    struct binary_indexed_tree {

        inline static size_t lsb(size_t i) {
            return i == 0 ? 0 : i & ~(i - 1);
        }

        size_t n;
        vector<T> data;
        //コンストラクタ
        binary_indexed_tree(size_t n) :n(n), data(n + 1, 0) {}

        void add(size_t i, T x) {
            i++;
            if (i == 0) return;
            for (size_t k = i; k <= n; k += (k & -k)) {
                data[k] += x;
            }
        }

        T sum(size_t i, size_t j) {
            return sum_sub(j) - sum_sub(i - 1);
        }

        T sum_sub(size_t i) {
            i++;
            T s = 0;
            if (i == 0) return s;
            for (size_t k = i; k > 0; k -= (k & -k)) {
                s += data[k];
            }
            return s;
        }

        size_t lower_bound(T x) {
            if (x <= 0) {
                //xが0以下の場合は該当するものなし→0を返す
                return 0;
            }
            else {
                size_t i = 0; size_t r = 1;
                //最大としてありうる区間の長さを取得する
                //n以下の最小の二乗のべき(BITで管理する数列の区間で最大のもの)を求める
                while (r < n) r = r << 1;
                //区間の長さは調べるごとに半分になる
                for (int len = r; len > 0; len = len >> 1) {
                    //その区間を採用する場合
                    if (i + len < n && data[i + len] < x) {
                        x -= data[i + len];
                        i += len;
                    }
                }
                return i;
            }
        }
    };

    static int digit_sum(int num) {
        if (num == 0) { return 0; }
        int cur = num;
        int value = 0;
        while (cur > 0) {
            value += cur % 10;
            cur /= 10;
        }
        return value;
    }

    static int get_cycle(vector<bool>& visited, const vector<int>& indexes, int start) {
        int s = 0;
        int current = start;
        while (!visited[current]) {
            visited[current] = true;
            current = indexes[current];
            s++;
        }

        return s;
    }

    int minSwaps(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> digit_sums;
        digit_sums.reserve(n);
        transform(cbegin(nums), cend(nums), back_inserter(digit_sums), digit_sum);

        vector<int> indexes(n);

        auto compare = [&](int a, int b)->bool {
            if (digit_sums[a] != digit_sums[b]) {
                return digit_sums[a] < digit_sums[b];
            }
            return nums[a] < nums[b];
            };
        for (int i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), compare);
        vector<bool> visited(n);
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i] || indexes[i] == i) { continue; }
            count += get_cycle(visited, indexes, i) - 1;
        }
        return count;
    }
}; 
void static test(vector<int>&& nums) {
    cout << Solution().minSwaps(nums) << endl;
}
static void run() {
    test(get_list_int("[18,43,34,16]"));
    test(get_list_int("[37,100]"));
    test(get_list_int("[22,14,33,7]"));
}

}
namespace problem3 {
class Solution {
public:
    int minMoves(vector<string>& matrix) {
        const auto m = size(matrix.front());
        const auto n = size(matrix);
        struct state {
            int y;
            int x;
            int step;
        };
        auto compare = [](const state& s1, const state& s2) {
            return s1.step > s2.step;
            };
        priority_queue<state, vector<state>, decltype(compare)> q(compare);

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        visited[0][0] = true;

        map<char, vector<pair<int, int>>> telepotation_groups;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] >= 'A' && matrix[i][j] <= 'Z') {
                    telepotation_groups[matrix[i][j]].emplace_back(make_pair(i, j));
                }
            }
        }
        auto do_next = [&](int y, int x, int step) {
            visited[y][x] = true;
            q.push(state{ y,x, step });
            if (matrix[y][x] >= 'A' && matrix[y][x] <= 'Z') {
                const auto& points = telepotation_groups[matrix[y][x]];
                for (auto&& [yy, xx] : points) {
                    if (!visited[yy][xx]) {
                        visited[yy][xx] = true;
                        q.push(state{ yy,xx, step });
                    }
                }
            }
            };
        const vector<pair<int, int>> directions = { {-1,0},{1,0},{0,-1},{0,1} };
        do_next(0, 0, 0);

        while (!q.empty()) {
            const state current_state = q.top();
            q.pop();
            if (current_state.y == n - 1 && current_state.x == m - 1) {
                return current_state.step;
            }
            for (auto&& [dy, dx] : directions) {
                const auto nexty = current_state.y + dy;
                const auto nextx = current_state.x + dx;
                if (0 <= nexty && nexty < n && 0 <= nextx && nextx < m && matrix[nexty][nextx] != '#' && !visited[nexty][nextx]) {
                    do_next(nexty, nextx, current_state.step + 1);
                }
            }
        }
        return -1;
    }
};
void test(vector<string>&& matrix) {
    cout << Solution().minMoves(matrix) << endl;
}

static void run() {
    test(get_list_str(R"(["A..",".A.","..."])"));
    test(get_list_str(R"([".#...",".#.#.",".#.#.","...#."])"));
}

}
namespace problem4 {
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

    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const auto n = size(edges) + 1;
        vector<int> ans;
        auto compare = [](const vector<int>& a, const vector<int>& b) { return a.back() < b.back(); };
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            union_find uf(n);
        }

        return ans;
    }
};
static void test(vector<vector<int>>&& edges, vector<vector<int>>&& queries) {
}
static void run() {
    test(get_matrix_int("[[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]]"), get_matrix_int("[[2,3,4],[0,2,5]]"));
    test(get_matrix_int("[[1,0,8],[0,2,7]]"), get_matrix_int("[[0,1,2]]"));
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