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
    int maxSum(vector<int>& nums) {
        int cur_sum = 0;
        set<int> exists;
        int count = 0;
        int max_value = INT_MIN;
        for (int i = 0; i < size(nums); i++) {
            if (0 < nums[i] && exists.count(nums[i])==0) {
                cur_sum += nums[i];
                exists.insert(nums[i]);
                count++;
            }
            max_value = max(max_value, nums[i]);
        }
        if (count == 0) {
            return max_value;
        }
        return cur_sum;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().maxSum(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[1,1,0,1,1]"));
    test(get_list_int("[1,2,-1,-2,1,0,-1]"));
}
}
namespace problem2 {
class Solution {
public:

    static int min_distance(int n, const set<int>& values, int index) {
        const auto it = values.find(index);
        auto next_it = next(it);
        int distance = INT_MAX;
        if (next_it == cend(values)) {
            distance = min(distance, *cbegin(values) + n - index);
        }
        else {
            distance = min(distance, *next_it - index);
        }
        if (it == cbegin(values)) {
            auto prev_it = prev(cend(values));
            distance = min(distance, index + n - *prev_it);
        }
        else {
            auto prev_it = prev(it);
            distance = min(distance, index - *prev_it);
        }
        return distance;
    }

    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        const auto n = size(nums);
        map<int, set<int>> index_map;
        for (int i = 0; i < n; i++) {
            index_map[nums[i]].insert(i);
        }
        vector<int> ans(size(queries),-1);
        for (int i = 0; i < size(queries); i++) {
            const auto query = queries[i];
            const auto num = nums[query % n];
            if (size(index_map[num]) > 1) {
                ans[i] = min_distance(n, index_map[num], query);
            }
        }
        return ans;
    }
};
void test(vector<int>&& nums, vector<int>&& queries) {
    output(Solution().solveQueries(nums, queries));
}
static void run() {
    test(get_list_int("[1,3,1,4,1,3,2]"), get_list_int("[0,3,5]"));
    test(get_list_int("[1,2,3,4]"), get_list_int("[0,1,2,3]"));
}
}
namespace problem3 {
class Solution {
public:

    static bool check_rec(const vector<int>& actives, int limit, int index, int num) {
        if (index == limit) {
            return false;
        }
        if (num == actives[index]) { return true; }
        if (num > actives[index]) {
            if (check_rec(actives, limit, index + 1, num - actives[index])) {
                return true;
            }
        }
        return check_rec(actives, limit, index + 1, num);
    }
    static bool check(const vector<int>& actives, int limit, int num) {
        return check_rec(actives, limit, 0, num);
    }
    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
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


    int tle(vector<int>& nums, vector<vector<int>>& queries) {
        map<int, map<int, int>> actives_index_map;
        map<int, vector<int>> actives_map;
        for (int i = 0; i < size(queries); i++) {
            const auto l = queries[i][0];
            const auto r = queries[i][1];
            const auto val = queries[i][2];
            for (int j = l; j <= r; j++) {
                actives_index_map[j].insert({ static_cast<int>(size(actives_map[j])), i + 1 });
                actives_map[j].emplace_back(val);
            }
        }
        int k = 0;

        for (int i = 0; i < size(nums); i++) {
            const auto num = nums[i];
            if (num == 0) {
            }
            else {
                const auto& actives = actives_map[i];
                int ok = size(actives) + 1;
                int ng = 0;
                auto ans = binary_search_meguru<int>(ok, ng, [&](int limit) ->bool {
                    return check(actives, limit, num);
                    });
                if (ans == ok) {
                    return -1;
                }
                k = max(k, actives_index_map[i][ans - 1]);
            }
        }
        return k;
    }

    static int check2(const vector<int>& actives, int num) {
        set<int> before;
        before.insert(0);
        for (int i = 0; i < size(actives); i++) {
            set<int> current(before);
            const auto val = actives[i];
            for (auto&& v : before) {
                if (v  + val== num) { return i + 1; }
                if (v + val < num) {
                    current.insert(val + v);
                }
            }
            swap(before, current);
        }
        return -1;
    }

    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        map<int, map<int, int>> actives_index_map;
        map<int, vector<int>> actives_map;
        for (int i = 0; i < size(queries); i++) {
            const auto l = queries[i][0];
            const auto r = queries[i][1];
            const auto val = queries[i][2];
            for (int j = l; j <= r; j++) {
                actives_index_map[j].insert({ static_cast<int>(size(actives_map[j])), i + 1});
                actives_map[j].emplace_back(val);
            }
        }
        int k = 0;

        for (int i = 0; i < size(nums); i++) {
            const auto num = nums[i];
            if (num == 0) {
            }
            else {
                const auto& actives = actives_map[i];
                const int ans = check2(actives, num);
                if (ans < 0) {
                    return -1;
                }
                k = max(k, actives_index_map[i][ans - 1]);
            }
        }
        return k;
    }
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().minZeroArray(nums, queries) << endl;
}

static void run() {
    test(get_list_int("[2,0,2]"), get_matrix_int("[[0,2,1],[0,2,1],[1,1,3]]"));
    test(get_list_int("[4,3,2,1]"), get_matrix_int("[[1,3,2],[0,2,1]]"));
    test(get_list_int("[1,2,3,2,1]"), get_matrix_int("[[0,1,1],[1,2,1],[2,3,2],[3,4,1],[4,4,1]]"));
    test(get_list_int("[1,2,3,2,6]"), get_matrix_int("[[0,1,1],[0,2,1],[1,4,2],[4,4,4],[3,4,1],[4,4,5]]"));
}
}
namespace problem4 {

class Solution {
public:
    static bool check(int v) {
        long long product = 1;
        long long sum = 0;
        int current = v;
        while (current > 0) {
            auto cur_digit = static_cast<long long>(current % 10);
            product *= cur_digit;
            sum += cur_digit;
            current /= 10;
        }
        return product % sum == 0;
    }
    static int bf(int l, int r) {
        int count = 0;
        for (int i = l; i <= r; i++) {
            if (check(i)) { count++; }
        }
        return count;
    }
    
    static vector<int> get_cols(int value) {
        vector<int> cols;
        int cur = value;
        while (cur > 0) {
            cols.emplace_back(cur % 10);
            cur /= 10;
        }
        return vector<int>(crbegin(cols), crend(cols));
    }

    static int calc(int value) {
        if (value == 0) {
            return 0;
        }

        const vector<int> columns = get_cols(value);
        // dp[column][isupper][sum][prod]=count
        vector<vector<map<int, map<int, int>>>> dp(size(columns), vector<map<int, map<int, int>>>(2));
        for (int c = 1; c < columns[0]; c++) {
            dp[0][0][c][c] = 1;
        }
        dp[0][1][columns[0]][columns[0]] = 1;
        for (int i = 1; i < size(columns); i++) {
            const auto col = columns[i];
            for (auto&& [before_sum, mp] : dp[i - 1][1]) {
                for (auto&& [before_prod, cur_cnt] : mp) {
                    dp[i][1][col + before_sum][col * before_prod] += cur_cnt;
                    for (int j = 0; j < col; j++) {
                        dp[i][0][j + before_sum][j * before_prod] += cur_cnt;
                    }
                }
            }
            for (auto&& [before_sum, mp] : dp[i - 1][0]) {
                for (auto&& [before_prod, cur_cnt] : mp) {
                    for (int j = 0; j <= 9; j++) {
                        dp[i][0][j + before_sum][j * before_prod] += cur_cnt;
                    }
                }
            }
            for (int j = 1; j <= 9; j++) {
                dp[i][0][j][j] += 1;
            }
        }

        int total = 0;
        for (auto&& [sum, mp] : dp.back()[0]) {
            for (auto&& [prod, count] : mp) {
                if (prod % sum == 0) {
                    total += count;
                }
            }
        }
        for (auto&& [sum, mp] : dp.back()[1]) {
            for (auto&& [prod, count] : mp) {
                if (prod % sum == 0) {
                    total += count;
                }
            }
        }
        return total;
    }


    int beautifulNumbers(int l, int r) {
        const auto rval = calc(r);
        const auto lval = calc(l - 1);
        return rval - lval;
    }
};

static void test(int l, int r) {
    cout << Solution().beautifulNumbers(l, r) << endl;
}

static void run() {
    test(1, 15);
    test(10, 20);
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