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
    int finalPositionOfSnake(int n, vector<string>& commands) {
        int current = 0;
        for (auto&& command : commands) {
            if (command == "UP") {
                current -= n;
            }
            else if (command == "RIGHT") {
                current += 1;
            }
            else if (command == "DOWN") {
                current += n;
            }
            else if (command == "LEFT") {
                current -= 1;
            }
        }
        return current;
    }
};
void test(int n, vector<string>&& commands) {
    cout << Solution().finalPositionOfSnake(n, commands) << endl;
}
void run() {
    test(2, get_list_str(R"(["RIGHT","DOWN"])"));
    test(3, get_list_str(R"(["DOWN","RIGHT","UP"])"));
}
}
namespace problem2 {
class Solution {
public:

    static int rec(const vector<vector<int>>& graph, int current, int parent, int& ans) {

        vector<int> childs;
        for (auto&& node : graph[current]) {
            if (node == parent) { continue; }
            childs.push_back(rec(graph, node, current, ans));
        }
        if (size(childs) <= 1) {
            ans++;
        }
        else {
            const auto v = childs.front();
            if (all_of(next(cbegin(childs)), cend(childs), [v](const auto& a) { return a == v; })) {
                ans++;
            }
        }
        return accumulate(cbegin(childs), cend(childs), 1);
    }

    int countGoodNodes(vector<vector<int>>& edges) {
        int m = 0;
        for (auto&& edge : edges) {
            for (auto&& nodev : edge) {
                m = max(m, nodev);
            }
        }
        const int n = m + 1;
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int ans = 0;

        rec(graph, 0, -1, ans);

        return ans;
    }
};
void test(vector<vector<int>>&& edges) {
    cout << Solution().countGoodNodes(edges) << endl;
}
void run() {
    test(get_matrix_int("[[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]"));
    test(get_matrix_int("[[0,1],[1,2],[2,3],[3,4],[0,5],[1,6],[2,7],[3,8]]"));
    test(get_matrix_int("[[0,1],[1,2],[1,3],[1,4],[0,5],[5,6],[6,7],[7,8],[0,9],[9,10],[9,12],[10,11]]"));
}
}
namespace problem3 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    using memo_key_t = pair<int, int>;
    using memo_t = map<memo_key_t, int>;
    static int rec(const vector<int>& nums, int index, int last_value, memo_t& memo) {
        if (size(nums) == index) {
            return 1;
        }

        const auto key = memo_key_t(index, last_value);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }
        const int arr2_last = nums[index - 1] - last_value;

        int count = 0;
        for (int i = 0; i <= nums[index]; i++) {
            const int arr2_val = nums[index] - i;
            if (last_value <= i && arr2_val <= arr2_last) {
                count += rec(nums, index + 1, i,memo);
                count %= MODULO;
            }
        }
        memo[key] = count;
        return count;
    }


    int countOfPairs(vector<int>& nums) {
        memo_t memo;

        vector<int> current1, current2;

        int count = 0;
        for (int i = 0; i <= nums[0]; i++) {
            count += rec(nums, 1, i, memo);
            count %= MODULO;
        }
        return count;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().countOfPairs(nums) << endl;
}
void run() {
    test(get_list_int("[2,3,2]"));
    test(get_list_int("[5,5,5,5]"));
}

}
namespace problem4 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    int countOfPairs(vector<int>& nums) {
        vector<vector<long long>> dp(size(nums), vector<long long>(1001));
        dp[0][0] = 1;
        for (int i = 1; i <= nums[0]; i++) {
            dp[0][i] = dp[0][i - 1] + 1;
        }
        for (int i = 1; i < size(nums); i++) {
            for (int j = 0; j <= nums[i]; j++) {
                const int arr2_value = nums[i] - j;
                const auto arr1_max = j;
                const auto arr2_max = nums[i - 1] - arr2_value;
                const auto limit_index = min(arr1_max, arr2_max);
                if (limit_index >= 0) {
                    dp[i][j] = dp[i-1][limit_index];
                }
                if (j > 0) {
                    dp[i][j] += dp[i][j - 1];
                    dp[i][j] %= MODULO;
                }
            }
        }
        return static_cast<int>(dp.back()[nums.back()] % MODULO);
    }
};
void test(vector<int>&& nums) {
    cout << Solution().countOfPairs(nums) << endl;
}
void run() {
    test(get_list_int("[2,3,2]"));
    test(get_list_int("[5,5,5,5]"));
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