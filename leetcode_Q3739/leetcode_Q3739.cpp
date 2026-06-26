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

    template<typename T>
    class binary_indexed_tree {
        int n;
        std::vector<T> data;

    public:
        binary_indexed_tree(int size) : n(size), data(size + 1, 0) {}

        // i番目にxを加算（0-indexed）
        void add(int i, T x) {
            ++i; // 1-indexedに変換
            while (i <= n) {
                data[i] += x;
                i += i & -i;
            }
        }

        // [0, i) の累積和（0-indexed）
        T sum(int i) const {
            T res = 0;
            while (i > 0) {
                res += data[i];
                i -= i & -i;
            }
            return res;
        }

        // [l, r) の累積和（0-indexed）
        T sum(int l, int r) const {
            return sum(r) - sum(l);
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

    using fenwick_tree = binary_indexed_tree<long long>;

    static pair<vector<long long>, unordered_map<long long, size_t>> compress_coodinates(const vector<long long>& nums) {
        set<long long> val_set(cbegin(nums), cend(nums));
        vector<long long> vals(size(val_set));
        unordered_map<long long, size_t> cc_map;
        auto it_val = cbegin(val_set);
        for (size_t i = 0; i < size(vals); i++) {
            vals[i] = *it_val;
            cc_map.insert({ vals[i], i });
            ++it_val;
        }
        return { vals, cc_map };
    }

    long long countMajoritySubarrays(vector<int>& nums, int target) {
        const auto n = size(nums);
        vector<long long> prefix_sums(n + 1);

        for (size_t i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + (nums[i] == target ? 1LL : -1LL);
        }

        const auto [values, ref_map] = compress_coodinates(prefix_sums);

        const auto m = size(values);
        fenwick_tree ft(m);

        long long ans = 0LL;
        ft.add(ref_map.at(prefix_sums[0]), 1);
        for (size_t i = 0; i < n; i++) {

            auto index = ref_map.at(prefix_sums[i + 1]);
            const auto count = ft.sum(index);
            ans += count;
            ft.add(index, 1);
        }


        return ans;
    }
};

static void test(vector<int>&& nums, int target) {
    cout << Solution().countMajoritySubarrays(nums, target) << endl;
}

int main() {
    test(get_list_int("[1,2,2,3]"), 2);
    test(get_list_int("[1,1,1,1]"), 1);
    test(get_list_int("[1,2,3]"), 4);
    return 0;
}
