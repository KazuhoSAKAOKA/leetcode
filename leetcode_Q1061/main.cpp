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

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        union_find uf(26);
        const auto n = size(s1);
        for (int i = 0; i < n; i++) {
            uf.unite(s1[i] - 'a', s2[i] - 'a');
        }
        map<int, char> min_chars;
        for (int i = 0; i < 26; i++) {
            const auto root = uf.root(i);
            auto it = min_chars.find(root);
            if (it == cend(min_chars)) {
                min_chars.insert({ root, static_cast<char>(i + 'a') });
            }
            else {
                it->second = min(static_cast<char>(i + 'a'), it->second);
            }
        }

        string ans;
        ans.reserve(size(baseStr));
        for (auto&& c : baseStr) {
            ans += min_chars[uf.root(c - 'a')];
        }
        return ans;
    }
};

void test(string&& s1, string&& s2, string&& baseStr) {
    cout << Solution().smallestEquivalentString(s1, s2, baseStr) << endl;
}
int main() {
	return 0;
}