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
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        if (k > 1) {
            for (int xx = 0; xx < k / 2; xx++) {
                const int upx = x + xx;
                const int lowx = x + k - 1 - xx;
                for (int yy = 0; yy < k; yy++) {
                    const int cury = y + yy;
                    swap(grid[upx][cury], grid[lowx][cury]);
                }
            }
        }
        return grid;
    }
};
static void test(vector<vector<int>>&& grid, int x, int y, int k) {
    output_matrix(Solution().reverseSubmatrix(grid, x, y, k));
}
static void run() {
    test(get_matrix_int("[[14,3,18,16],[2,14,11,20],[19,19,4,15],[11,15,18,6]]"), 0, 0, 4);
    test(get_matrix_int("[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]"), 1, 0, 3);
    test(get_matrix_int("[[3,4,2,3],[2,3,4,2]]"), 0, 2, 2);
}
}
namespace problem2 {
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> orderd(n);
        for (int i = 0; i < n; i++) { orderd[i] = i; }
        int max_value = 0x7fffffff;
        bool exist = false;
        for (int i = 0; i < n; i++) {
            if (nums[i] != orderd[i]) {
                max_value &= nums[i];
                max_value &= orderd[i];
                exist = true;
            }
        }
        if (exist) {
            return max_value;
        }
        return 0;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().sortPermutation(nums) << endl;
}

static void run() {
    test(get_list_int("[0,3,2,1]"));
    test(get_list_int("[0,1,3,2]"));
    test(get_list_int("[3,2,1,0]"));
}
}
namespace problem3 {
class Solution {
public:
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        const auto n = size(value);
        map<int, vector<int>> limit_map;
        for (int i = 0; i < n; i++) {
            limit_map[limit[i]].emplace_back(value[i]);
        }

        long long total = 0;
        for (auto&& [k, l] : limit_map) {
            sort(begin(l), end(l), greater<int>());
            const auto s = min(static_cast<int>(size(l)), k);
            for (int i = 0; i < s; i++) {
                total += l[i];
            }

        }
        return total;
    }
};
static void test(vector<int>&& value, vector<int>&& limit) {
    cout << Solution().maxTotal(value, limit) << endl;
}
static void run() {
    test(get_list_int("[4,1,5,2]"), get_list_int("[3,3,2,3]"));
    test(get_list_int("[3,5,8]"), get_list_int("[2,1,3]"));
    test(get_list_int("[4,2,6]"), get_list_int("[1,1,1]"));
}
}
namespace problem4 {
class Solution {
public:
    //static void create_odd_sub(const vector<long long>& digits, size_t len, size_t index, vector<long long>& cur, long long odd, vector<vector<long long>>& total) {
    //    if (size(digits) == index) {
    //        if (size(cur) == len) {
    //            total.emplace_back(cur);
    //        }
    //        return;
    //    }
    //    create_sub(digits, len, index + 1, cur, total);
    //    const auto cur_digit = digits[index];
    //    const auto cur_digit_count = cur_digit / 2;
    //    if (size(cur) + cur_digit_count <= len) {
    //        for (int i = 0; i < cur_digit_count; i++) {
    //            cur.emplace_back(cur_digit);
    //        }
    //        create_odd_sub(digits, len, index + 1, cur, odd, total);
    //        for (int i = 0; i < cur_digit_count; i++) {
    //            cur.pop_back();
    //        }
    //    }
    //}


    static void create_sub(const vector<long long>& digits, size_t len, size_t index, vector<long long>& cur, vector<vector<long long>>& total) {
        if (size(digits) == index) {
            if (size(cur) == len) {
                total.emplace_back(cur);
            }
            return;
        }
        create_sub(digits, len, index + 1, cur, total);
        const auto cur_digit = digits[index];
        const auto cur_digit_count = cur_digit / 2;
        if (size(cur) + cur_digit_count <= len) {
            for (int i = 0; i < cur_digit_count; i++) {
                cur.emplace_back(cur_digit);
            }
            create_sub(digits, len, index + 1, cur, total);
            for (int i = 0; i < cur_digit_count; i++) {
                cur.pop_back();
            }
        }
    }
    static vector<vector<long long>> create_odd(const vector<long long>& digits, size_t len, long long odd) {
        vector<vector<long long>> digitss;
        vector<long long> cur;
        for (long long i = 0; i < (odd / 2); i++) {
            cur.emplace_back(odd);
        }
        create_sub(digits, len, 0, cur, digitss);
        return digitss;
    }
    static vector<vector<long long>> create(const vector<long long>& digits, size_t len) {
        vector<vector<long long>> digitss;
        vector<long long> cur;
        create_sub(digits, len, 0, cur, digitss);
        return digitss;
    }

    static long long convert_even(const vector<long long>& digits) {
        long long value = 0LL;
        long long base = 1;
        for (auto it = crbegin(digits); it != crend(digits); ++it) {
            value += *it * base;
            base *= 10;
        }
        for (auto it = cbegin(digits); it != cend(digits); ++it) {
            value += *it * base;
            base *= 10;
        }
        return value;
    }
    static long long convert_odd(const vector<long long>& digits, long long center) {
        long long value = 0LL;
        long long base = 1;
        for (auto it = crbegin(digits); it != crend(digits); ++it) {
            value += *it * base;
            base *= 10;
        }
        value += center * base;
        base *= 10;
        for (auto it = cbegin(digits); it != cend(digits); ++it) {
            value += *it * base;
            base *= 10;
        }
        return value;
    }
    static vector<long long> create_odds(size_t len) {
        vector<long long> even_digits;
        for (long long i = 2; i <= min(static_cast<size_t>(9), len); i += 2) {
            even_digits.emplace_back(i);
        }
        vector<long long> values;
        for (long long i = 1; i <= min(static_cast<size_t>(9), len); i += 2) {
            auto digitss = create_odd(even_digits, len / 2, i);
            for (auto&& digits : digitss) {
                sort(begin(digits), end(digits));
                do {
                    values.emplace_back(convert_odd(digits, i));
                } while (next_permutation(begin(digits), end(digits)));
            }
        }
        sort(begin(values), end(values));
        return values;
    }


    static vector<long long> create_evens(size_t len) {
        vector<long long> even_digits;
        for (long long i = 2; i <= min(static_cast<size_t>(9), len); i += 2) {
            even_digits.emplace_back(i);
        }
        auto digitss = create(even_digits, len / 2);
        vector<long long> values;
        for (auto&& digits : digitss) {
            sort(begin(digits), end(digits));
            do {
                values.emplace_back(convert_even(digits));
            } while (next_permutation(begin(digits), end(digits)));
        }
        sort(begin(values), end(values));
        return values;
    }
    long long specialPalindrome(long long n) {
        if (n == 0) { return 1LL; }
        const auto s = to_string(n);
        auto len = size(s);

        for (;;) {
            if (len % 2 == 0) {
                const auto cand = create_evens(len);
                auto it = upper_bound(cbegin(cand), cend(cand), n);
                if (it != cend(cand)) {
                    return *it;
                }
            }
            else {
                const auto cand = create_odds(len);
                auto it = upper_bound(cbegin(cand), cend(cand), n);
                if (it != cend(cand)) {
                    return *it;
                }
            }
            len++;
        }

    }
};
static void test(long long n) {
    cout << Solution().specialPalindrome(n) << endl;
}
static void run() {
    test(9331491632);
    test(23670);
    test(216);
    test(2);
    test(33);
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