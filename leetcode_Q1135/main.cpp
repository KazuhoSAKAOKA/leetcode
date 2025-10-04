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

    int minimumCost(int n, vector<vector<int>>& connections) {
        union_find uf(n);
        sort(begin(connections), end(connections), [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });

        int total_cost = 0;

        for (auto&& connection: connections) {
            const auto u = connection[0];
            const auto v = connection[1];
            const auto cost = connection[2];
            if (!uf.same(u - 1, v - 1)) {
                total_cost += cost;
                uf.unite(u - 1, v - 1);
                if (uf.size(uf.root(u - 1)) == n) {
                    return total_cost;
                }
            }
        }
        return -1;
    }
};

static void test(int n, vector<vector<int>>&& connections) {

}
int main() {
	return 0;
}