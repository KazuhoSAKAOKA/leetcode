// leetcode_Q3356.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

template <typename X, typename M>
struct SegTreeLazy {
    using FX = function<X(X, X)>;
    using FA = function<X(X, M)>;
    using FM = function<M(M, M)>;
    int n;
    FX fx;
    FA fa;
    FM fm;
    const X ex;
    const M em;
    vector<X> dat;
    vector<M> lazy;
    SegTreeLazy(int n_, FX fx_, FA fa_, FM fm_, X ex_, M em_)
        : n(), fx(fx_), fa(fa_), fm(fm_), ex(ex_), em(em_), dat(n_ * 4, ex), lazy(n_ * 4, em) {
        int x = 1;
        while (n_ > x) x *= 2;
        n = x;
    }
    void set(int i, X x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }
    /* lazy eval */
    void eval(int k) {
        if (lazy[k] == em) return;  // 更新するものが無ければ終了
        if (k < n - 1) {            // 葉でなければ子に伝搬
            lazy[k * 2 + 1] = fm(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = fm(lazy[k * 2 + 2], lazy[k]);
        }
        // 自身を更新
        dat[k] = fa(dat[k], lazy[k]);
        lazy[k] = em;
    }
    void update(int a, int b, M x, int k, int l, int r) {
        eval(k);
        if (a <= l && r <= b) {  // 完全に内側の時
            lazy[k] = fm(lazy[k], x);
            eval(k);
        }
        else if (a < r && l < b) {                     // 一部区間が被る時
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
            dat[k] = fx(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void update(int a, int b, M x) { update(a, b, x, 0, 0, n); }
    X query_sub(int a, int b, int k, int l, int r) {
        eval(k);
        if (r <= a || b <= l) {  // 完全に外側の時
            return ex;
        }
        else if (a <= l && r <= b) {  // 完全に内側の時
            return dat[k];
        }
        else {  // 一部区間が被る時
            X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fx(vl, vr);
        }
    }
    X query(int a, int b) { return query_sub(a, b, 0, 0, n); }
};

class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        const auto n = size(nums);
        using X = int;
        using M = int;
        auto fx = [](X x1, X x2) -> X { return max(x1, x2); };
        auto fa = [](X x, M m) -> X { return max(0, x - m); };
        auto fm = [](M m1, M m2) -> M { return m1 + m2; };
        constexpr int ex = numeric_limits<int>::min();
        constexpr int em = 0;

        SegTreeLazy<X, M> lazy_st(n, fx, fa, fm, ex, em);
        for (int i = 0; i < n; i++) { lazy_st.set(i, nums[i]); }
        lazy_st.build();
        if (lazy_st.query(0, n) == 0) {
            return 0;
        }
        for (int i = 0; i < size(queries); i++) {
            const auto l = queries[i][0];
            const auto r = queries[i][1];
            const auto v = queries[i][2];
            lazy_st.update(l, r + 1, v);
            if (lazy_st.query(0, n) == 0) {
                return i + 1;
            }
        }
        return -1;
    }
};

void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().minZeroArray(nums, queries) << endl;
}

int main()
{
    test(get_list_int("[79,93]"), get_matrix_int("[[1,1,5],[0,1,5],[0,0,3],[1,1,5],[1,1,4],[0,1,3],[1,1,5],[0,0,2],[0,1,4],[0,1,4],[0,0,1],[0,0,2],[0,0,1],[1,1,2],[0,1,2],[0,1,5],[0,1,3],[0,1,2],[1,1,3],[0,1,2],[1,1,3],[0,1,1],[1,1,4],[0,1,5],[0,0,4],[1,1,1],[1,1,1],[1,1,1],[1,1,1],[0,0,4],[1,1,4],[0,1,3],[0,0,1],[1,1,3],[1,1,3],[0,0,3],[0,0,3],[1,1,3],[1,1,3],[1,1,1],[1,1,4],[0,0,1],[1,1,5],[1,1,5],[0,0,1],[1,1,5],[1,1,4],[0,0,3],[0,1,1],[0,0,2],[0,1,5],[0,0,1],[1,1,5],[1,1,1],[0,1,1],[1,1,3],[1,1,2],[1,1,1],[0,1,1],[0,1,1],[1,1,4],[0,1,5],[0,1,1],[0,0,2],[0,0,4],[1,1,2],[1,1,2],[1,1,5],[1,1,2],[0,1,4],[1,1,1],[1,1,4],[1,1,5],[0,0,1],[1,1,1],[1,1,2],[0,1,1],[1,1,5],[0,0,3],[0,1,5],[1,1,1],[0,0,4],[0,1,4],[1,1,4],[0,1,4],[1,1,5],[1,1,3],[1,1,4],[1,1,2],[0,0,1],[1,1,1],[0,0,5],[1,1,2],[1,1,3],[0,0,2],[1,1,4],[1,1,2],[1,1,4],[0,1,5],[1,1,3],[1,1,4],[0,0,4],[1,1,1],[0,1,5],[0,0,3],[1,1,2],[1,1,5],[0,0,4],[1,1,2],[1,1,3],[1,1,3],[0,1,2],[0,1,3],[1,1,1],[1,1,2],[0,1,3],[1,1,5],[0,0,1],[0,0,4],[1,1,1],[0,1,2],[0,0,1],[0,1,2],[1,1,5],[0,0,2],[0,0,1],[0,1,5],[0,0,4],[1,1,3],[0,0,5],[0,1,2],[0,0,2],[1,1,3],[0,0,1],[0,0,5],[1,1,5],[1,1,2],[1,1,1],[0,0,1],[1,1,4],[0,0,1],[1,1,5],[0,1,3],[1,1,3],[1,1,1],[1,1,4],[0,0,4],[1,1,2],[0,0,3],[1,1,3],[0,1,2],[0,0,2],[1,1,4],[1,1,5],[0,0,4],[1,1,1],[1,1,4],[1,1,5],[1,1,1],[1,1,4],[1,1,5],[1,1,2],[1,1,2],[1,1,1],[1,1,1],[1,1,2],[1,1,2],[0,0,2],[0,1,2],[1,1,3],[0,1,2],[1,1,5],[1,1,5],[0,0,4],[0,1,4],[1,1,5],[0,0,1],[0,1,5],[1,1,4],[1,1,4],[1,1,1],[1,1,3],[0,0,3],[1,1,3],[0,1,2],[1,1,4],[1,1,5],[1,1,3],[0,1,1],[1,1,3],[1,1,4],[1,1,3],[1,1,2],[0,0,5],[1,1,4],[0,0,3],[1,1,5],[0,1,2],[0,0,3],[0,1,2],[0,0,2],[1,1,1]]"));

    test(get_list_int("[2,0,2]"), get_matrix_int("[[0,2,1],[0,2,1],[1,1,3]]"));
    test(get_list_int("[4,3,2,1]"), get_matrix_int("[[1,3,2],[0,2,1]]"));
    return 0;
}