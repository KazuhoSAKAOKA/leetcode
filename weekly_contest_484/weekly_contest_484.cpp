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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int residuePrefixes(string s) {
        set<char> sets;
        int count = 0;

        for (int i = 0; i < size(s); i++) {
            const auto p_len = (i + 1) % 3;
            sets.insert(s[i]);
            if (size(sets) == p_len) {
                count++;
            }
        }

        return count;
    }
};
static void test(string&& s) {
    cout << Solution().residuePrefixes(s) << endl;
}

static void run() {
    test("abc");
    test("dd");
    test("bob");
}
}

namespace problem2 {
class Solution {
public:
    int centeredSubarrays(vector<int>& nums) {
        const auto n = size(nums);
        vector<long long> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + nums[i]; }

        int count = 0;
        for (int i = 0; i < n; i++) {
            set<int> exists;
            for (int len = 1; i + len <= n; len++) {
                exists.insert(nums[i + len - 1]);
                const auto sum = prefix_sums[i + len] - prefix_sums[i];
                if (exists.count(sum) > 0) {
                    count++;
                }
            }
        }

        return count;
    }

};
static void test(vector<int>&& nums) {
    cout << Solution().centeredSubarrays(nums) << endl;
}
static void run() {
    test(get_list_int("[-1,1,0]"));
    test(get_list_int("[2,-3]"));
}
}

namespace problem3 {
class Solution {
public:

    static string convert(const string& word) {
        string ret;
        const auto op_count = (26 - (word[0] - 'a')) % 26;

        for (int i = 0; i < size(word); i++) {
            ret += ((word[i] - 'a' + op_count) % 26) + 'a';
        }
        return ret;
    }

    long long countPairs(vector<string>& words) {
        const auto n = size(words);
        const auto m = size(words[0]);
        long long count = 0;
        map<string, long long> exist_map;
        for (int i = 0; i < n; i++) {
            const auto w = convert(words[i]);
            auto it = exist_map.find(w);
            if (it == cend(exist_map)) {
                exist_map.insert({ w, 1LL });
            }
            else {
                count += it->second;
                it->second++;
            }
        }
        return count;
    }
};
static void test(vector<string>&& words) {
    cout << Solution().countPairs(words) << endl;
}
static void run() {
    test(get_list_str(R"(["fusion","layout"])"));
    test(get_list_str(R"(["ab","aa","za","aa"])"));
}
}

namespace problem4 {
class Solution {
public:
    static int get_msb(int num) {
        int position = -1;
        while (num > 0) {
            num >>= 1;
            position++;
        }
        return position;
    }
    //static vector<int> get_op_counts(int num, int target) {
    //    vector<int> op_counts(31);
    //    const auto msb = get_msb(num);
    //    for (int i = 0; i < msb; i++) {
    //        if (num & (1 << i)) {
    //            op_counts[i] = 0;
    //        }
    //        else {

    //        }
    //    }


    //    return op_counts;
    //}
    /*        constexpr int max_bit = 8;
        vector<vector<int>> operation_counts(max_bit, vector<int>(n));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < max_bit; j++) {
                if (nums[i] & (1 << j)) {
                    operation_counts[j][i] = 0;
                }
                else {
                    const int target = (1 << j);
                    const int mask = target - 1;
                    const int v = nums[i] & mask;
                    const auto op_count = target - v;
                    operation_counts[j][i] = op_count;
                }
            }
        }

        for (int j = 0; j < max_bit; j++) {
            sort(begin(operation_counts[j]), begin(operation_counts[j]));
        }

        int max_value = 0;
        int remain_count = k;
        for (int j = max_bit - 1; j >= 0; j--) {
            int current_ops = 0;
            for (int i = 0; i < m; i++) {
                current_ops += operation_counts[j][i];
            }
            if (current_ops <= remain_count) {
                max_value |= (1 << j);
                remain_count -= current_ops;
            }
        }
*/

    static int get_msb(int num) {
        int position = -1;
        while (num > 0) {
            num >>= 1;
            position++;
        }
        return position;
    }
    int maximumAND(vector<int>& nums, int k, int m) {
        const auto n = size(nums);
        const int upper_limit = *max_element(cbegin(nums), cend(nums)) + k;
        const int max_bit = get_msb(upper_limit);

        int remain_ops = k;
        int ans = 0;
        for (int bit = max_bit; bit >= 0; bit++) {
            int current_ops = 0;
            const int target = 1 << bit;

        }
        return ans;
    }
};
static void test(vector<int>&& nums, int k, int m) {
    cout << Solution().maximumAND(nums, k, m) << endl;
}

static void run() {
    test(get_list_int("[3,1,2]"), 8, 2);
    test(get_list_int("[1,2,8,4]"), 7, 3);
    test(get_list_int("[1,1]"), 3, 2);
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