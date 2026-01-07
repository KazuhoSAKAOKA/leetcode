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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    template<long long MOD>
    struct modint_ex {
        long long modulo;     // 0 <= modulo < MOD
        long long multipled;  // 元の値 = multipled * MOD + modulo

        modint_ex(long long x = 0) {
            // x を multipled と modulo に分解
            multipled = x / MOD;
            modulo = x % MOD;
            if (modulo < 0) {
                modulo += MOD;
                multipled -= 1;
            }
        }

        // 元の値を復元
        long long original_value() const {
            return multipled * MOD + modulo;
        }

        // 加算
        modint_ex& operator+=(const modint_ex& other) {
            modulo += other.modulo;
            if (modulo >= MOD) {
                modulo -= MOD;
                multipled += 1;
            }
            multipled += other.multipled;
            return *this;
        }

        // 減算
        modint_ex& operator-=(const modint_ex& other) {
            modulo -= other.modulo;
            if (modulo < 0) {
                modulo += MOD;
                multipled -= 1;
            }
            multipled -= other.multipled;
            return *this;
        }

        // 乗算
        modint_ex& operator*=(const modint_ex& other) {
            long long new_mod = modulo * other.modulo % MOD;
            long long carry = modulo * other.modulo / MOD;

            multipled = multipled * other.modulo
                + other.multipled * modulo
                + multipled * other.multipled * MOD
                + carry;

            modulo = new_mod;
            return *this;
        }

        friend modint_ex operator+(modint_ex a, const modint_ex& b) { return a += b; }
        friend modint_ex operator-(modint_ex a, const modint_ex& b) { return a -= b; }
        friend modint_ex operator*(modint_ex a, const modint_ex& b) { return a *= b; }

        // 大小比較は original_value ベース
        friend bool operator<(const modint_ex& a, const modint_ex& b) {
            if (a.multipled != b.multipled) { return a.multipled < b.multipled; }
            return a.modulo < b.modulo;
        }
        friend bool operator>(const modint_ex& a, const modint_ex& b) { return b < a; }
        friend bool operator<=(const modint_ex& a, const modint_ex& b) { return !(b < a); }
        friend bool operator>=(const modint_ex& a, const modint_ex& b) { return !(a < b); }
    };
    using modint_v = modint_ex<MODULO>;
    static void dfs(const TreeNode* node, modint_v& total) {
        total += node->val;
        if (node->left != nullptr) {
            dfs(node->left, total);
        }
        if (node->right != nullptr) {
            dfs(node->right, total);
        }
    }

    static modint_v dfs2(const TreeNode* node, const modint_v& total, modint_v& cur_max) {
        modint_v v(node->val);
        if (node->left != nullptr) {
            const auto left_total = dfs2(node->left, total, cur_max);
            const auto remain = total - left_total;
            cur_max = max(cur_max, left_total * remain);
            v += left_total;
        }
        if (node->right != nullptr) {
            const auto right_total = dfs2(node->right, total, cur_max);
            const auto remain = total - right_total;
            cur_max = max(cur_max, right_total * remain);
            v += right_total;
        }
        return v;
    }


    int maxProduct(TreeNode* root) {
        modint_v total(0);
        dfs(root, total);
        modint_v max_value(0);
        dfs2(root, total, max_value);
        return max_value.modulo;
    }
};

static void test(vector<optional<int>>&& values) {
    cout << Solution().maxProduct(create_treenode2(values)) << endl;
}

int main()
{
    test(get_list_optional_int("[1,2,3,4,5,6]"));
    test(get_list_optional_int("[1,null,2,3,4,null,null,5,6]"));
}
