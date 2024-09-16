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

    static string itoa2(int value)
    {
        if (value == 0) {
            return "0";
        }
        static const char table[] = "01";
        string work;

        for (; value != 0; value /= 2) {
            work += table[value % 2];
        }
        return string(crbegin(work), crend(work));
    }

    string convertDateToBinary(string date) {
        const auto year_str = date.substr(0, 4);
        const auto month_str = date.substr(5, 2);
        const auto day_str = date.substr(8, 2);
        const auto year_val = stoi(year_str);
        const auto month_val = stoi(month_str);
        const auto day_val = stoi(day_str);


        const auto year_bin_rep = itoa2(year_val);
        const auto month_bin_rep = itoa2(month_val);
        const auto day_bin_rep = itoa2(day_val);
        return year_bin_rep + "-" + month_bin_rep + "-" + day_bin_rep;
    }
};

void test(string&& date) {
    cout << Solution().convertDateToBinary(date) << endl;
}
void run() {
    test("2100-12-31");
    test("2080-02-29");
    test("1900-01-01");
}
}
namespace problem2 {
class Solution {
public:
    static int tle(vector<int>& start, int d) {
        sort(begin(start), end(start));
        if (size(start) == 2) {
            return start.back() + d - start.front();
        }
        vector<vector<int>> dp(size(start) - 1, vector<int>(d + 1, INT_MAX));

        for (int i = 0; i <= d; i++) {
            dp[0][i] = start[1] + i - start[0];
        }

        for (int i = 1; i < size(start) - 1; i++) {
            for (int j = 0; j <= d; j++) {
                int temp = 0;
                for (int k = 0; k <= d; k++) {
                    temp = max(temp, min((start[i + 1] + j) - (start[i] + k), dp[i - 1][k]));
                }
                dp[i][j] = temp;
            }
        }

        int ans = 0;
        for (int i = 0; i <= d; i++) {
            ans = max(ans, dp[size(start) - 2][i]);
        }
        return ans;
    }

    int maxPossibleScore(vector<int>& start, int d) {
        sort(begin(start), end(start));
        if (size(start) == 2) {
            return start.back() + d - start.front();
        }

        auto check = [&](const int gap) {
            long long before = start[0];
            for (int i = 1; i < size(start); i++) {
                const auto temp = before + static_cast<long long>(gap);
                if (start[i] + d < temp) {
                    return false;
                }
                before = max(static_cast<long long>(start[i]), before + gap);
            }
            return true;
            };
        int ng = start.back() + d + 1;
        int ok = 0;
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
};

void test(vector<int>&& start, int d) {
    cout << Solution().maxPossibleScore(start, d) << endl;
}

void run() {
    test(get_list_int("[4,0,1]"), 8);
    test(get_list_int("[5,1,9]"), 10);
    test(get_list_int("[6,0,3]"), 2);
    test(get_list_int("[2,6,13,13]"), 5);
}
}
namespace problem3 {
    class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        long long total = 0;
        long long current_max = 0;
        for (long long i = 0; i < size(nums) - 1; i++) {
            current_max = max(current_max, static_cast<long long>(nums[i]));
            total += current_max;
        }
        return total;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().findMaximumScore(nums) << endl;
}

void run() {
    test(get_list_int("[1,3,1,5]"));
    test(get_list_int("[4,3,1,3,2]"));
}
}
namespace problem4 {
void run() {
}
}

int main()
{
    //problem1::run();
    problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}