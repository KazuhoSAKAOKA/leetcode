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
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"

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

    string findTheString(vector<vector<int>>& lcp) {
        const auto n = size(lcp);
        string ans(n, ' ');
        set<char> alphabets;
        for (char c = 'a'; c <= 'z'; c++) {
            alphabets.insert(c);
        }
        map<int, char> defineds;
        union_find uf(n);

        for (int i = 0; i < n; i++) {
            if (ans[i] == ' ') {
                auto it = defineds.find(uf.root(i));
                if (it == cend(defineds)) {
                    if (alphabets.empty()) { return ""; }
                    const auto target = *cbegin(alphabets);
                    alphabets.erase(begin(alphabets));
                    ans[i] = target;
                    defineds[i] = target;
                }
                else {
                    ans[i] = it->second;
                }
            }

 
            for (int j = 0; j < n; j++) {
                if (n - i < lcp[i][j] || n - j < lcp[i][j]) {
                    return "";
                }

                if (i == j) {
                    if (lcp[i][j] != n - i) {
                        return "";
                    }
                }
                else {

                    for (int k = 0; k < lcp[i][j]; k++) {
                        if (ans[i + k] != ' ') {
                            if (ans[j + k] != ' ') {
                                if (ans[i + k] != ans[j + k]) {
                                    return "";
                                }
                            }
                            else {
                                if (uf.same(i + k, j + k)) {
                                    ans[j + k] = ans[i + k];
                                }
                                else {
                                    if (defineds.find(j + k) != cend(defineds)) {
                                        return "";
                                    }
                                    uf.unite(i + k, j + k);
                                    ans[j + k] = ans[i + k];
                                    defineds[uf.root(i + k)] = ans[i + k];
                                }
                            }
                        }
                        else {
                            if (ans[j + k] != ' ') {
                                if (uf.same(i + k, j + k)) {
                                    ans[i + k] = ans[j + k];
                                }
                                else {
                                    if (defineds.find(i + k) != cend(defineds)) {
                                        return "";
                                    }
                                    uf.unite(i + k, j + k);
                                    ans[i + k] = ans[j + k];
                                    defineds[uf.root(i + k)] = ans[j + k];
                                }
                            }
                            else {
                                uf.unite(i + k, j + k);
                            }
                        }
                    }

                    if (i + lcp[i][j] < n && j + lcp[i][j] < n) {
                        if (uf.same(i + lcp[i][j], j + lcp[i][j])) {
                            return "";
                        }
                    }
                }
            }
        }


        return ans;
    }
};

static void test(vector<vector<int>>&& lcp) {
    cout << Solution().findTheString(lcp) << endl;
}
int main()
{
    test(get_matrix_int("[[3,0,2],[0,2,1],[2,1,1]]"));

    test(get_matrix_int("[[4,1,1,1],[1,3,1,1],[1,1,2,1],[1,1,1,1]]"));

    test(get_matrix_int("[[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]"));
    test(get_matrix_int("[[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]"));
    test(get_matrix_int("[[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]"));
    return 0;
}