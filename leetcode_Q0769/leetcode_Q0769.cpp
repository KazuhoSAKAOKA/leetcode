// leetcode_Q0769.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

struct segment_tree {
    const int INF_;
    int n_;
    vector<int> dat_;
    function<int(int,int)> query_;
    segment_tree(int n, function<int(int,int)> query, int inf) : n_(n), dat_(n * 4, inf), query_(query), INF_(inf) {
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
            dat_[i] = query_(dat_[i * 2 + 1], dat_[i * 2 + 2]);
        }
    }
    int query(int a, int b) { return query_sub(a, b, 0, 0, n_); }
    int query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return INF_;
        }
        else if (a <= l && r <= b) {
            return dat_[k];
        }
        else {
            auto vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            auto vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return query_(vl, vr);
        }
    }
};

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        const int N = static_cast<int>(size(arr));
        segment_tree min_st(N, [](int a, int b) {return min(a, b); }, INT_MAX);
        segment_tree max_st(N, [](int a, int b) {return max(a, b); }, INT_MIN);

        for (int i = 0; i < N; i++) {
            min_st.update(i, arr[i]);
            max_st.update(i, arr[i]);
        }

        int count = 0;
        int current_left = 0;
        for (int i = 0; i < N; i++) {
            const auto cur_min = min_st.query(current_left, i + 1);
            const auto cur_max = max_st.query(current_left, i + 1);
            bool left_ok = false;
            if (current_left == 0) {
                left_ok = true;
            }
            else {
                const auto left_max = max_st.query(0, current_left);
                left_ok = left_max <= cur_min;
            }

            bool right_ok = false;
            if (i == N - 1) {
                right_ok = true;
            }
            else {
                const auto right_min = min_st.query(i + 1, N);
                right_ok = cur_max <= right_min;
            }
            if (left_ok && right_ok) {
                count++;
                current_left = i + 1;
            }
        }
        return count;
    }
};

void test(vector<int>&& arr) {
    cout << Solution().maxChunksToSorted(arr) << endl;
}
int main()
{
    test(get_list_int("[1,2,0,3]"));
    test(get_list_int("[4,3,2,1,0]"));
    test(get_list_int("[1,0,2,3,4]"));
    return 0;
}
