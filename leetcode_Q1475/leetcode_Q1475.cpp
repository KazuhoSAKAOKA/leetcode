// leetcode_Q1475.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

constexpr int INF = INT_MAX;
struct segment_tree {
    int n_;
    vector<int> dat_;
    segment_tree(int n) : n_(n), dat_(n * 4, INF){
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n_ = x;
    }
    void update(int i, int x) {
        i += n_ - 1;
        dat_[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat_[i] = min(dat_[i * 2 + 1], dat_[i * 2 + 2]);
        }
    }
    int query(int a, int b) { return query_sub(a, b, 0, 0, n_); }
    int query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return INF;
        }
        else if (a <= l && r <= b) {
            return dat_[k];
        }
        else {
            auto vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            auto vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        segment_tree st(1001);
        vector<int> ans(size(prices));
        for (int i = size(prices) - 1; i >= 0; i--) {
            const auto price = prices[i];
            const auto index = st.query(0, price + 1);
            if (index < INT_MAX) {
                ans[i] = price - prices[index];
            }
            else {
                ans[i] = price;
            }
            st.update(price, i);
        }
        return ans;
    }
};
void test(vector<int>&& prices) {
    output(Solution().finalPrices(prices));
}
int main()
{
    test(get_list_int("[8,4,6,2,3]"));
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[10,1,1,6]"));
    return 0;
}