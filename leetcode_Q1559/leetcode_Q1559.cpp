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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static bool dfs(const vector<vector<char>>& grid, const pair<int, int>& current, const pair<int, int>& before, vector<vector<bool>>& visited, vector<vector<bool>>& history) {

        static const vector<pair<int, int>> directions{
            {-1,0},{1,0},{0,-1},{0,1},
        };

        for (auto&& [dy, dx] : directions) {
            const pair<int, int> np{ current.first + dy ,current.second + dx };
            if (0 <= np.first && np.first < size(grid) && 0 <= np.second && np.second < size(grid[0]) && before != np && grid[current.first][current.second] == grid[np.first][np.second]) {
                if (visited[np.first][np.second]) {
                    return true;
                }
                history[np.first][np.second] = true;
                visited[np.first][np.second] = true;
                if (dfs(grid, np, current, visited, history)) {
                    return true;
                }
                visited[np.first][np.second] = false;
            }
        }
        return false;
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

    bool containsCycle(vector<vector<char>>& grid) {
        const long long n = size(grid);
        const long long m = size(grid.front());

        const long long N = n * m;
        union_find uf(N);

        static const vector<pair<long long, long long>> directions{
            {1,0},{0,1},
        };

        auto get_index = [&](long long y, long long x)->size_t {
            return y * m + x;
            };

        for (long long y = 0; y < n; y++) {
            for (long long x = 0; x < m; x++) {
                const auto u = get_index(x, y);
                for (auto&& [dy, dx] : directions) {
                    const auto ny = y + dy;
                    const auto nx = x + dx;
                    if (0 <= ny && ny < n && 0 <= nx && nx < m && grid[y][x] == grid[ny][nx]) {
                        const auto v = get_index(ny, nx);
                        if (uf.same(u, v)) { return true; }
                        uf.unite(u, v);
                    }
                }
            }
        }
        return false;
    }
};

static void test(vector<vector<char>>&& grid) {
    cout << Solution().containsCycle(grid) << endl;
}


#include <filesystem>
#include <fstream>
string get_test_data_from_file(const std::filesystem::path& in_file) {
    ifstream ifs(in_file);
    string test_data;
    ifs >> test_data;
    return test_data;
}

int main() {
    test(get_matrix_char(get_test_data_from_file(filesystem::path("./testdata.txt"))));
    test(get_matrix_char(R"([["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]])"));
    test(get_matrix_char(R"([["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]])"));
    test(get_matrix_char(R"([["a","b","b"],["b","z","b"],["b","b","a"]])"));

    return 0;
}

