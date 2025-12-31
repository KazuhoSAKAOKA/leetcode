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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {

class Solution {
public:
    int evenNumberBitwiseORs(vector<int>& nums) {
        int value = 0;
        for (auto&& num : nums) {
            if (num % 2 == 0) {
                value |= num;
            }
        }
        return value;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().evenNumberBitwiseORs(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4,5,6]"));
    test(get_list_int("[7,9,11]"));
    test(get_list_int("[1,8,16]"));
}
}
namespace problem2 {
class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        const auto [minit, maxit] = minmax_element(cbegin(nums), cend(nums));
        const auto value = static_cast<long long>(*maxit) - static_cast<long long>(*minit);
        return value * static_cast<long long>(k);
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().maxTotalValue(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,3,2]"), 2);
    test(get_list_int("[4,2,5,1]"), 3);

}
}
namespace problem3 {
class Solution {
public:

    static int rec(vector<int>& nums1, const vector<int>& nums2, int count) {
        if (equal(cbegin(nums2), cend(nums2), cbegin(nums1))) {
            return count;
        }
    }

    static inline bool eq(const vector<int>& nums1, const vector<int>& nums2) {
        return equal(cbegin(nums2), cend(nums2), cbegin(nums1));
    }

    static int check2(vector<int>& nums1, vector<int>& nums2) {
        if (equal(cbegin(nums2), cend(nums2), cbegin(nums1))) {
            return 0;
        }
        else {
            return 1;
        }
    }
    static void cp(const vector<int>& source, int start, int len, vector<int>& destination, int dest_st) {
        for (int i = 0; i < len; i++) {
            destination[dest_st + i] = source[start + i];
        }
    }

    static int checkrec(vector<int>& nums1, const vector<int>& nums2, int depth) {
        if (equal(cbegin(nums2), cend(nums2), cbegin(nums1))) {
            return 0;
        }
        const int n = size(nums1);
        if (depth >= n) {
            return  INT_MAX / 2;
        }
        int min_count = INT_MAX / 2;
        for (int i = 0; i < n; i++) {
            for (int len = 1; len < n - i - 1; i++) {
                for (int j = i + len; j < n; j++) {
                    vector<int> nums_work(n);
                    cp(nums1, 0, i, nums_work, 0);
                    cp(nums1, i + len, j - i, nums_work, i);
                    cp(nums1, i, len, nums_work, j);
                    cp(nums1, j + 1, n - j - 1, nums_work, j + 1);
                    for (int aa = 0; aa < n; aa++) {
                        if (nums_work[aa] == 0) {
                            cout << "err" << endl;
                        }
                    }

                    min_count = min(min_count, checkrec(nums_work, nums2, depth + 1) + 1);
                }
            }
        }
        return min_count;
    }


    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        const auto n = size(nums1);
        if (n == 2) {
            return check2(nums1, nums2);
        }
        else {
            return checkrec(nums1, nums2, 0);
        }
    }
};
static void test(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().minSplitMerge(nums1, nums2) << endl;
}

static void run() {
    test(get_list_int("[1,1,2,3,4,5]"), get_list_int("[5,4,3,2,1,1]"));
    test(get_list_int("[3,1,2]"), get_list_int("[1,2,3]"));
}
}
namespace problem4 {
    class Solution {
    public:
        long long maxTotalValue(vector<int>& nums, int k) {

            auto calc = [&](int left, int right, int limit)->pair<long long, int> {
                const auto b = next(cbegin(nums), left);
                const auto e = next(cbegin(nums), right);
                const auto [minit, maxit] = minmax_element(b, e);
                const auto value = static_cast<long long>(*maxit) - static_cast<long long>(*minit);
                const int min_index = distance(b, minit);
                const int max_index = distance(b, maxit);
                const long long lefts = min(min_index, max_index) - left;
                const long long rights = right - max(min_index, max_index);
                const auto cur_patterns = left * right;
                int count = min(cur_patterns, limit);
                return { value * static_cast<long long>(count), count };
                };


            long long total = 0LL;
            int remain = k;
            queue<pair<int, int>> q;
            q.push({ 0, static_cast<int>(size(nums)) });
            while (remain > 0) {
                auto [cur_left, cur_right] = q.front();
                q.pop();
                const auto [val, remain1] = calc(cur_left, cur_right, remain);
                total += val;
                remain = remain1;
            }
            return total;
        }
    };
    static void test(vector<int>& nums, int k) {
        cout << Solution().maxTotalValue(nums, k) << endl;
    }

    static void run() {
    }
}
int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}