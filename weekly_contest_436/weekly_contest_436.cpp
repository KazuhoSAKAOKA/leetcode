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
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        const size_t n = size(grid);
        vector<vector<int>> ans(n, vector<int>(n));

        // bottom left
        for (int i = 0; i < n; i++) {
            vector<int> work(i + 1);
            for (int j = 0; j <= i; j++) {
                work[j] = grid[n - i + j - 1][j];
            }
            sort(begin(work), end(work), std::greater<int>());
            for (int j = 0; j <= i; j++) {
                ans[n - i + j - 1][j] = work[j];
            }
        }

        // top right
        for (int i = 0; i < n - 1; i++) {
            vector<int> work(i + 1);
            for (int j = 0; j <= i; j++) {
                work[j] = grid[j][n - i + j - 1];
            }
            sort(begin(work), end(work), std::less<int>());
            for (int j = 0; j <= i; j++) {
                ans[j][n - i + j - 1] = work[j];
            }
        }
        return ans;
            
    }
};

void test(vector<vector<int>>&& grid) {
    output_matrix(Solution().sortMatrix(grid));
}
static void run() {
    test(get_matrix_int("[[1,7,3],[9,8,2],[4,5,6]]©leetcode"));
    test(get_matrix_int("[[0,1],[1,2]]©leetcode"));
}
}
namespace problem2 {
class Solution {
public:
    static vector<int> bf(const vector<int>& groups, const vector<int>& elements) {
        vector<int> ans(size(groups), -1);
        for (int i = 0; i < size(groups); i++) {
            for (int j = 0; j < size(elements); j++) {
                if (groups[i] % elements[j] == 0) {
                    ans[i] = j;
                    break;
                }
            }
        }
        return ans;
    }
    static vector<long long> divisor(long long n) {
        vector<long long> ret;
        for (long long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                ret.push_back(i);
                if (i * i != n) ret.push_back(n / i);
            }
        }
        return ret;
    }

    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        map<long long, int> element_map;

        for (int i = 0; i < size(elements); i++) {
            auto it = element_map.find(elements[i]);
            if (it == cend(element_map)) {
                element_map.insert({ static_cast<long long>(elements[i]), i });
            }
        }

        vector<int> ans(size(groups), -1);
        for (int i = 0; i < size(groups); i++) {
            const auto divisors = divisor(groups[i]);

            int index = INT_MAX;
            for (auto&& div : divisors) {
                const auto it = element_map.find(div);
                if (it != cend(element_map)) {
                    index = min(index, it->second);
                }
            }
            if (index != INT_MAX) {
                ans[i] = index;
            }
        }

        return ans;
    }
};
void test(vector<int>&& groups, vector<int>&& elements) {
    output(Solution().assignElements(groups, elements));
}

static void run() {
    test(get_list_int("[8,4,3,2,4]"), get_list_int("[4,2]"));
    test(get_list_int("[2,3,5,7]"), get_list_int("[5,3,3]"));
    test(get_list_int("[10,21,30,41]"), get_list_int("[2,1]"));
}
}
namespace problem3 {
class Solution {
public:

    static long long cal3(const string& s, int len) {
        long long count = 0;
        long long cur_sum = 0;
        for (int i = 0; i < len; i++) {
            int index = len - 1 - i;
            cur_sum += static_cast<long long>(s[index] - '0');
            if (cur_sum % 3 == 0) {
                count++;
            }
        }
        return count;
    }

    static long long cal4(const string& s, int len) {
        long long count = 0;
        if (len >= 2) {
            const auto v = s.substr(len - 2, 2);
            const auto value = stoi(v);
            if (value % 4 == 0) {
                count += len - 2 + 1;
            }
        }
        if (s[len - 1] == '4' || s[len - 1] == '8') {
            count++;
        }
        return count;
    }

    static long long cal6(const string& s, int len) {
        const auto cur_digit = static_cast<long long>(s[len - 1] - '0');
        if (cur_digit % 2 != 0) {
            return 0;
        }
        long long count = 0;
        if (cur_digit % 3 == 0) {
            count++;
        }
        long long cur_sum = cur_digit;
        for (int i = 1; i < len; i++) {
            int index = len - 1 - i;
            cur_sum += static_cast<long long>(s[index] - '0');
            if (cur_sum % 3 == 0) {
                count++;
            }
        }
        return count;
    }

    static bool check7(const string& s, int offset, int length) {
        long long even_groups = 0;
        long long odd_groups = 0;
        for (int i = 0; i < (length + 2) / 3; i++) {
            auto index = length - (i + 1) * 3;
            auto len = 3;
            if (index < 0) {
                len += index;
                index = 0;
            }
            const auto temp = s.substr(offset + index, len);
            const auto value = stoi(temp);
            if (i % 2 == 0) {
                even_groups += value;
            }
            else {
                odd_groups += value;
            }
        }

        const auto diff = max(even_groups, odd_groups) - min(even_groups, odd_groups);
        return (diff % 7) == 0;
    }

    static long long cal7(const string& s, int len) {
        long long count = 0;
        for (int i = 0; i < len; i++) {
            if (check7(s, i, len - i)) {
                count++;
            }
        }
        return count;
    }

    static long long cal8(const string& s, int len) {
        long long count = 0;
        if (len >= 3) {
            const auto v = s.substr(len - 3, 3);
            const auto value = stoi(v);
            if (value % 8 == 0) {
                count += len - 3 + 1;
            }
        }
        if (len >= 2) {
            const auto v = s.substr(len - 2, 2);
            const auto value = stoi(v);
            if (value % 8 == 0) {
                count++;
            }
        }
        if (s[len - 1] == '8') {
            count++;
        }
        return count;
    }

    static long long cal9(const string& s, int len) {
        long long count = 0;
        long long cur_sum = 0;
        for (int i = 0; i < len; i++) {
            int index = len - 1 - i;
            cur_sum += static_cast<long long>(s[index] - '0');
            if (cur_sum % 9 == 0) {
                count++;
            }
        }
        return count;
    }

    long long countSubstrings(string s) {
        long long total = 0;

        for (long long i = 0; i < size(s); i++) {
            const long long cur_digit = static_cast<long long>(s[i] - '0');
            if (cur_digit == 0) {
                continue;
            }
            switch (cur_digit) {
            case 1:
                total += i + 1;
                break;
            case 2:
                if (cur_digit % 2 == 0) {
                    total += i + 1;
                }
                break;
            case 3:
                total += cal3(s, i + 1);
                break;
            case 4:
                total += cal4(s, i + 1);
                break;
            case 5:
                if (cur_digit % 5 == 0) {
                    total += i + 1;
                }
                break;
            case 6:
                total += cal6(s, i + 1);
                break;
            case 7:
                total += cal7(s, i + 1);
                break;
            case 8:
                total += cal8(s, i + 1);
                break;
            case 9:
                total += cal9(s, i + 1);
                break;
            default:
                throw exception();
            }
        }
        return total;
    }
};
void test(string&& s) {
    cout << Solution().countSubstrings(s) << endl;
}

static void run() {
    test("123456789123456789");

    test("5701283");
    test("1010101010");
    test("12936");
}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}