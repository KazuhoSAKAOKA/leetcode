#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    template<typename T>
    struct binary_indexed_tree {

        inline static size_t lsb(size_t i) {
            return i == 0 ? 0 : i & ~(i - 1);
        }

        size_t n;
        vector<T> data;
        //コンストラクタ
        binary_indexed_tree(size_t n) :n(n), data(n + 1, 0) {}

        void add(size_t i, T x) {
            i++;
            if (i == 0) return;
            for (size_t k = i; k <= n; k += (k & -k)) {
                data[k] += x;
            }
        }

        T sum(size_t i, size_t j) {
            return sum_sub(j) - sum_sub(i - 1);
        }

        T sum_sub(size_t i) {
            i++;
            T s = 0;
            if (i == 0) return s;
            for (size_t k = i; k > 0; k -= (k & -k)) {
                s += data[k];
            }
            return s;
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

    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        const auto n = size(nums);
        const auto m = size(queries);
        vector<int> diff_arr(n + 1);
        sort(begin(queries), end(queries), [](const vector<int>& a, const vector<int>& b) { return a.front() < b.front(); });

        int count = 0;
        int current_top = 0;
        int current_value = 0;
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < n; i++) {
            current_value += diff_arr[i];
            while (current_top < m && queries[current_top].front() <= i) {
                pq.push({ queries[current_top].back(), queries[current_top].front() });
                current_top++;
            }
            while (nums[i] > current_value) {
                if (pq.empty()) {
                    return -1;
                }
                const auto [back, front] = pq.top();
                pq.pop();
                if (front <= i && i <= back) {
                    count++;
                    current_value++;
                    diff_arr[back + 1]--;
                }
            }
        }


        return m - count;
    }
}
;
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().maxRemoval(nums, queries) << endl;
}


int main() {
    test(get_list_int("[2,0,2]"), get_matrix_int("[[0,2],[0,2],[1,1]]"));
    test(get_list_int("[1,1,1,1]"), get_matrix_int("[[1,3],[0,2],[1,3],[1,2]]"));
    test(get_list_int("[1,2,3,4]"), get_matrix_int("[[0,3]]"));
    return 0;
}