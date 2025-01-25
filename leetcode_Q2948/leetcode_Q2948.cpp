// leetcode_Q2948.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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


    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        const size_t N = size(nums);
        vector<size_t> indexes(N);
        for (size_t i = 0; i < N; i++) {
            indexes[i] = i;
        }
        sort(begin(indexes), end(indexes), [&](const auto& a, const auto& b) { return nums[a] < nums[b]; });
        int before = nums[indexes[0]];

        map<int, size_t, greater<int>> group_map;
        group_map[nums[indexes[0]]] = 0;
        for (size_t i = 1; i < N; i++) {
            if (nums[indexes[i]] - before > limit) {
                group_map[nums[indexes[i]]] = i;
            }
            before = nums[indexes[i]];
        }

        vector<int> ans(N);

        for (int i = 0; i < N; i++) {
            auto it = group_map.lower_bound(nums[i]);
            ans[i] = nums[indexes[it->second]];
            it->second++;
        }

        return ans;
        /*
        union_find uf(N);
        map<int, size_t> indexes_map;

        vector<size_t> indexes(N);
        for (size_t i = 0; i < N; i++) {
            indexes[i] = i;

            auto already_it = indexes_map.find(nums[i]);
            if (already_it == end(indexes_map)) {
                auto it = indexes_map.lower_bound(nums[i] - limit);
                while (it != cend(indexes_map) && it->first <= nums[i] + limit) {
                    uf.unite(i, it->second);
                    ++it;
                }
                indexes_map[nums[i]] = i;
            }
            else {
                uf.unite(i, already_it->second);
            }
        }

        sort(begin(indexes), end(indexes), [&](const auto& a, const auto& b) { return nums[a] < nums[b]; });


        //map<size_t, map<int, int>> group_map;
        //for (int i = 0; i < N; i++) {
        //    const auto root = uf.root(i);
        //    group_map[root][nums[i]]++;
        //}

        vector<int> ans(N);

        for (size_t i = 0; i < N; i++) {
            const auto root = uf.root(indexes[i]);


            ans[indexes[i]] = 0;
        }
        return ans;
        */
    }
};

void test(vector<int>&& nums, int limit) {
    output(Solution().lexicographicallySmallestArray(nums, limit));
}

int main() {
    test(get_list_int("[1,7,6,18,2,1]"), 3);
    test(get_list_int("[1,5,3,9,8]"), 2);
    test(get_list_int("[1,7,28,19,10]"), 3);
    return 0;
}
