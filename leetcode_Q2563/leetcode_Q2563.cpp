// leetcode_Q2563.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

struct segment_tree {
    const long long INF_ = 0;
    int n_;
    vector<long long> dat_;
    segment_tree(int n) : n_(n), dat_(n * 4){
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n_ = x;
    }
    void add(int i, long long x) {
        i += n_ - 1;
        dat_[i] += x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat_[i] = dat_[i * 2 + 1] + dat_[i * 2 + 2];
        }
    }
    long long query(int a, int b) { return query_sub(a, b, 0, 0, n_); }
    long long query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return INF_;
        }
        else if (a <= l && r <= b) {
            return dat_[k];
        }
        else {
            long long vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            long long vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }
};

class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        map<int, int> index_map;
        for (int i = 0; i < size(nums); i++) {
            index_map[nums[i]]++;
        }
        int index = 0;
        for (auto&& [k, v] : index_map) {
            v = index++;
        }

        segment_tree st(size(index_map));
        long long count = 0;
        st.add(index_map[nums[0]], 1);

        for (int i = 1; i < size(nums); i++) {
            const auto lower_limit = lower - nums[i];
            const auto upper_limit = upper - nums[i];
            const auto lower_it = index_map.lower_bound(lower_limit);
            if (lower_it != cend(index_map)) {
                const auto upper_it = index_map.upper_bound(upper_limit);
                const auto c1 = st.query(lower_it->second, upper_it != cend(index_map) ? upper_it->second : size(index_map) + 1);
                count += c1;
            }
            st.add(index_map[nums[i]], 1);
        }

        return count;
    }
};

void test(vector<int>&& nums, int lower, int upper) {
    cout << Solution().countFairPairs(nums, lower, upper) << endl;
}

int main()
{
    test(get_list_int("[-5,-7,-5,-7,-5]"), -12, -12);
    test(get_list_int("[0,1,7,4,4,5]"), 3, 6);
    test(get_list_int("[1,7,9,2,5]"), 11, 11);
    return 0;
}