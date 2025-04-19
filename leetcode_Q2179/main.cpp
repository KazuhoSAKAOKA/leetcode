#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:

    static long long tle(const vector<int>& nums1, vector<int>& nums2) {
        const auto n = size(nums1);

        unordered_map<int, int> mp1;
        unordered_map<int, int> mp2;
        for (int i = 0; i < n; i++) {
            mp1[nums1[i]] = i;
            mp2[nums2[i]] = i;
        }


        long long count = 0;
        for (int x = 0; x < n; x++) {
            const auto pos1x = mp1[x];
            const auto pos2x = mp2[x];
            for (int y = 0; y < n; y++) {
                if (x != y) {
                    const auto pos1y = mp1[y];
                    const auto pos2y = mp2[y];
                    for (int z = 0; z < n; z++) {
                        if (x != z && y != z) {
                            const auto pos1z = mp1[z];
                            const auto pos2z = mp2[z];
                            if (pos1x < pos1y && pos1y < pos1z && pos2x < pos2y && pos2y < pos2z) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
        return count;
    }


    struct binary_indexed_tree {

        inline static size_t lsb(size_t i) {
            return i == 0 ? 0 : i & ~(i - 1);
        }

        size_t n;
        vector<long long> data;
        //コンストラクタ
        binary_indexed_tree(long long n) :n(n), data(n + 1, 0) {}

        void add(long long i, long long x) {
            i++;
            if (i == 0) return;
            for (long long k = i; k <= n; k += (k & -k)) {
                data[k] += x;
            }
        }

        long long sum(long long i, long long j) {
            return sum_sub(j) - sum_sub(i - 1);
        }

        long long sum_sub(long long i) {
            i++;
            long long s = 0;
            if (i == 0) return s;
            for (long long k = i; k > 0; k -= (k & -k)) {
                s += data[k];
            }
            return s;
        }

        long long lower_bound(long long x) {
            if (x <= 0) {
                //xが0以下の場合は該当するものなし→0を返す
                return 0;
            }
            else {
                long long i = 0; long long r = 1;
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

    using fenwick_tree = binary_indexed_tree;


    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        const auto n = size(nums1);
        unordered_map<int, int> mp1;
        for (int i = 0; i < n; i++) {
            mp1[nums1[i]] = i;
        }
        vector<long long> left_to_rights(n);
        fenwick_tree fwt_left(n);
        for (int i = 1; i < n - 1; i++) {
            const auto prev = nums2[i - 1];
            const auto pos_prev = mp1[prev];
            fwt_left.add(pos_prev, 1);

            const auto current = nums2[i];
            const auto pos_current = mp1[current];
            left_to_rights [i] = fwt_left.sum(0, pos_current);
        }

        vector<long long> right_to_lefts(n);
        fenwick_tree fwt_right(n);
        for (int i = n - 2; i >= 1; i--) {
            const auto prev = nums2[i + 1];
            const auto pos_prev = mp1[prev];
            fwt_right.add(pos_prev, 1);

            const auto current = nums2[i];
            const auto pos_current = mp1[current];
            right_to_lefts[i] = fwt_right.sum(pos_current, n - 1);
        }

        long long count = 0;
        for (int i = 1; i < n - 1; i++) {
            count += left_to_rights[i] * right_to_lefts[i];
        }

        return count;
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().goodTriplets(nums1, nums2) << endl;
}
int main() {
    test(get_list_int("[4,0,1,3,2]"), get_list_int("[4,1,0,2,3]"));
    test(get_list_int("[2,0,1,3]"), get_list_int("[0,1,2,3]"));
    test(get_list_int("[13,14,10,2,12,3,9,11,15,8,4,7,0,6,5,1]"), get_list_int("[8,7,9,5,6,14,15,10,2,11,4,13,3,12,1,0]"));
    return 0;
}