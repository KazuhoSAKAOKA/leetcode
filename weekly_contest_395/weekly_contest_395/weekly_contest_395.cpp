// weekly_contest_395.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;

namespace problem1 {

class Solution {
public:
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(begin(nums1), end(nums1));
        sort(begin(nums2), end(nums2));

        return nums2[0] - nums1[0];
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().addedInteger(nums1, nums2) << endl;
}

void run() {
    test({ 2,6,4, }, { 9,7,5, });
    test({ 10, }, { 5, });
    test({ 1,1,1,1, }, { 1,1,1,1, });
}

}

namespace problem2 {

class Solution {
public:
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {

        sort(begin(nums1), end(nums1));
        sort(begin(nums2), end(nums2));
        const int INF = INT_MAX;
        vector<vector<int>> dp(nums2.size(), vector<int>(3, INF));

        dp[0][0] = nums2[0] - nums1[0];
        dp[0][1] = nums2[0] - nums1[1];
        dp[0][2] = nums2[0] - nums1[2];

        for (int i = 1; i < nums2.size(); i++) {

            {
                const auto diff = nums2[i] - nums1[i];
                if (diff == dp[i - 1][0]) {
                    dp[i][0] = diff;
                }
            }

            {
                const auto diff = nums2[i] - nums1[i + 1];
                if (diff == dp[i - 1][0] || diff == dp[i - 1][1]) {
                    dp[i][1] = diff;
                }
            }
            {
                const auto diff = nums2[i] - nums1[i + 2];
                if (diff == dp[i - 1][0] || diff == dp[i - 1][1] || diff == dp[i - 1][2]) {
                    dp[i][2] = diff;
                }
            }
        }

        int min_value = INF;
        for (int i = 0; i < 3; i++) {
            min_value = min(min_value, dp[nums2.size() - 1][i]);
        }
        return min_value;
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().addedInteger(nums1, nums2) << endl;
}

void run() {
    test({ 9,4,3,9,4, }, { 7,8,8, });


    test({ 4,7,5, }, { 5, });
    test({ 4,20,16,12,8, }, { 14,18,10, });
    test({ 3,5,5,3, }, { 7,7, });
}

}


namespace problem3 {

class Solution {
public:


    static long long counting_tle(int n, int x) {
        long long count = 0;
        for (int i = 1; i <= n; i++) {
            if ((i & x) == x) {
                count++;
            }
        }
        return count;
    }

    static long long counting(int n, int x) {
        if (n < x) { return 0LL; }
        int columns = 0;
        vector<int> defcolums;
        int v = n;
        while (v > 0) {
            defcolums.emplace_back(v % 16);
            v /= 16;
            columns++;
        }

        reverse(begin(defcolums), end(defcolums));
        vector<int> targets(defcolums.size(), 0);

        for (int i = 0; i < defcolums.size(); i++) {
            targets[i] = (x & (0x0000000F << (8 * i)) >> (8 * 1));
        }
        vector<vector<long long>> dp(columns, vector<long long>(2, 0));
        long long count = 0;
        dp[0][0] = (defcolums[0] & targets[0]) == targets[0] ? 1 : 0;
        dp[0][1] = (defcolums[0] & targets[0]) == targets[0] ? 1 : 0;


        return dp[columns - 1][0] + dp[columns - 1][1];
    }

    static long long binary_search(int n, int x) {
        long long l = 1;
        long long r = 100;// LLONG_MAX;

        while (l < r) {
            const auto mid = (l + r) / 2;
            const auto num = counting(mid, x);
            if (num < n) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }
        return counting(l, x) == n ? l : r;
    }


    long long minEnd(int n, int x) {
        int bits_index = 0;
        long long bits = static_cast<long long>(n - 1);
        long long target_value = static_cast<long long>(x);
        int bit_index = 0;

        for (int i = 0; i < 64; i++) {
            const long long bit = 1LL << i;
            if ((target_value & bit) == 0) {
                if ((bits & (1LL << bits_index)) != 0) {
                    target_value |= bit;
                }
                bits_index++;
            }
        }

        return target_value;
    }
};

void test(int n, int x) {
    cout << Solution().minEnd(n, x) << endl;
}

void run() {
    test(3, 4);
    test(2, 7);
}

}


namespace problem4 {

class Solution {
public:
    static int tle(vector<int>& nums) {
        vector<int> subarray_length;
        vector<set<int>> before;
        before.emplace_back(set<int>{nums[0]});
        subarray_length.emplace_back(1);
        for (int i = 1; i < nums.size(); i++) {
            vector<set<int>> current;
            for (auto&& subarray : before) {
                subarray.insert(nums[i]);
                subarray_length.emplace_back(subarray.size());
                current.emplace_back(subarray);
            }
            current.emplace_back(set<int>{nums[i]});
            subarray_length.emplace_back(1);
            swap(current, before);
        }
        sort(begin(subarray_length), end(subarray_length));
        return subarray_length[subarray_length.size() / 2 + (subarray_length.size() % 2 == 0 ? -1 : 0)];
    }




    static bool check(const vector<int>& nums, int needed) {
        unordered_map<int, int> freq_map;
        long long total = 0;
        int forward = 0;
        int backward = 0;
        while(forward < nums.size()) {
            freq_map[nums[forward]]++;
            while (freq_map.size() > needed) {
                freq_map[nums[backward]]--;
                if (freq_map[nums[backward]] == 0) { freq_map.erase(nums[backward]); }
                backward++;
            }
            total += forward - backward + 1;
            forward++;
        }
        return total >= nums.size() * (nums.size() + 1) / 2;
    }


    int medianOfUniquenessArray(vector<int>& nums) {
        int l = 1;
        int r = nums.size();
        int ans = r;
        while(l <= r){
            const auto mid = (l + r) / 2;
            if (check(nums, mid)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        return ans;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().medianOfUniquenessArray(nums) << endl;
}

void run() {
    test({ 1,2,3, });
    test({ 3,4,3,4,5, });
    test({ 4,3,5,4, });
}

}


int main()
{
//    problem1::run();
//    problem2::run();
//    problem3::run();
    problem4::run();
}