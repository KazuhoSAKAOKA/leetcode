// leetcode_Q2832.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <stack>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

constexpr int INF = INT_MIN;

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
            dat_[i] = max(dat_[i * 2 + 1], dat_[i * 2 + 2]);
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
            return max(vl, vr);
        }
    }
};

int binary_search_meguru(int ok, int ng, std::function<bool(int)> check) {
    while (abs(ng - ok) > 1) {
        const auto mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        }
        else {
            ng = mid;
        }
    }
    return ok;
}

class Solution {
public:

    static vector<int> tle(vector<int>& nums) {
        segment_tree st(size(nums));
        for (int i = 0; i < size(nums); i++) {
            st.update(i, nums[i]);
        }
        vector<int> ans;
        ans.reserve(size(nums));

        for (int i = 0; i < size(nums); i++) {
            const auto left_index = binary_search_meguru(i, -1, [&](int v)->bool {
                return st.query(v, i + 1) <= nums[i];
                });
            const auto right_index = binary_search_meguru(i, size(nums), [&](int v)->bool {
                return st.query(i, v + 1) <= nums[i];
                });
            ans.emplace_back(right_index - left_index + 1);
        }
        return ans;
    }

    vector<int> maximumLengthOfRanges(vector<int>& nums) {
        stack<int> mono_stack_left_to_right;
        mono_stack_left_to_right.push(-1);
        vector<int> left_to_right(size(nums));
        
        for (int i = 0; i < size(nums); i++) {
            while (mono_stack_left_to_right.top() >= 0 && nums[mono_stack_left_to_right.top()] < nums[i]) {
                mono_stack_left_to_right.pop();
            }
            const auto left_len = i - mono_stack_left_to_right.top();
            left_to_right[i] = left_len;
            mono_stack_left_to_right.push(i);
        }

        stack<int> mono_stack_right_to_left;
        mono_stack_right_to_left.push(size(nums));
        vector<int> right_to_left(size(nums));
        for (int i = size(nums) - 1; i >= 0; i--) {
            while (mono_stack_right_to_left.top() < size(nums) && nums[mono_stack_right_to_left.top()] < nums[i]) {
                mono_stack_right_to_left.pop();
            }
            const auto right_len = mono_stack_right_to_left.top() - i;
            right_to_left[i] = right_len;
            mono_stack_right_to_left.push(i);
        }

        vector<int> ans;
        ans.reserve(size(nums));
        for (int i = 0; i < size(nums); i++) {
            ans.emplace_back(left_to_right[i] + right_to_left[i] - 1);
        }

        return ans;
    }
};

void test(vector<int>&& nums) {
    output(Solution().maximumLengthOfRanges(nums));
}
int main()
{
    test(get_list_int("[1,5,4,3,6]"));
    test(get_list_int("[1,2,3,4,5]"));
    return 0;
}