// weekly_contest_392.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;


namespace problem1 {
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {

        int max_len_si = 0;
        int max_len_sd = 0;
        int len_si = 0;
        int len_sd = 0;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i - 1] < nums[i]) {
                len_si++;
                max_len_si = max(max_len_si, len_si);
                len_sd = 0;
            }
            else if (nums[i - 1] > nums[i]) {
                len_sd++;
                max_len_sd = max(max_len_sd, len_sd);
                len_si = 0;
            }
            else {
                len_si = 0;
                len_sd = 0;
            }
        }
        return max(max_len_si, max_len_sd) + 1;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().longestMonotonicSubarray(nums) << endl;
}

void run() {
    test({ 1,4,3,3,2, });
    test({ 3,3,3,3, });
    test({ 3,2,1, });
}
}

namespace problem2 {
class Solution {
public:
    /*
    static int distance(const string& s1, const string& s2) {
        int total = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] == s2[i]) { continue; }
            const auto large = max(s1[i], s2[i]);
            const auto small = min(s1[i], s2[i]);
            const auto dist = min(large - small, small + 'a' - large);
            total += dist;
        }
        return total;
    }
    */
    static pair<char, int> get_lexicographically_smallest(char c, int k) {
        const auto f = c - 'a';
        const auto b = 'z' - c + 1;
        if (b < f && b <= k) {
            return make_pair('a', b);
        }
        const auto dist = min(k, f);
        return make_pair(c - dist, dist);
    }

    string getSmallestString(string s, int k) {
        string t(s);
        int remain = k;
        for (int i = 0; i < t.size(); i++) {
            const auto [c, use] = get_lexicographically_smallest(s[i], remain);
            t[i] = c;
            remain -= use;
        }
        return t;
    }
};

void test(string&& s, int k) {
    cout << Solution().getSmallestString(s, k) << endl;
}

}

namespace problem3 {
class Solution {
public:
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));

        long long op_count = 0;
        int mid_index;
        if (nums.size() % 2 != 0) {
            mid_index = nums.size() / 2;
            op_count += abs(nums[mid_index] - k);
        }
        else {
            mid_index = nums.size() / 2;
            op_count += abs(nums[mid_index] - k);
        }

        for (int i = mid_index + 1; i < nums.size();i++) {
            if (k <= nums[i]) {
                break;
            }
            op_count += abs(nums[i] - k);
        }

        for (int i = mid_index - 1; i >= 0; i--) {
            if (nums[i] <= k) {
                break;
            }
            op_count += abs(nums[i] - k);
        }

        return op_count;
    }
};
    
void test(vector<int>&& nums, int k) {
    cout << Solution().minOperationsToMakeMedianK(nums, k) << endl;
}
void run() {
    test({ 2,5,6,8,5 }, 4);
    test({ 2,5,6,8,5 }, 7);
    test({ 1,2,3,4,5,6 }, 4);
}
}


namespace problem4 {
class Solution {
public:

    static int dfs(int n, const unordered_map<int, vector<vector<int>>>& edges, int goal, int current, int current_cost) {
        if (current == goal) {
            return current_cost;
        }

        const auto it = edges.find(current);
        if (it != cend(edges)) {
            int min_cost = INT_MAX;
            for (auto&& edge : it->second) {
                const auto v = edge[1];
                const auto w = edge[2];
                const auto cost = dfs(n, edges, goal, v, current_cost & w);
                if (0 <= cost) {
                    min_cost = min(min_cost, cost);
                }
            }
            return min_cost;
        }
        return -1;
    }



    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int> ans;
        unordered_map<int, vector<vector<int>>> edges_map;
        for (auto&& edge : edges) {
            edges_map[edge[0]].push_back(edge);
        }
        for (auto&& q : query) {
            ans.emplace_back(dfs(n, edges_map, q[1], q[0], 0xffffffff));
        }
        return ans;
    }
};

void test(int n, vector<vector<int>>&& edges, vector<vector<int>>&& query) {
    const auto ans = Solution().minimumCost(n, edges, query);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test(5, { {0,1,7, },{1,3,7,},{1,2,1 } }, { {0,3,},{3,4} });
    test(3, { {0,2,7, },{0,1,5,},{1,2,6 } }, { {1,2} });
}
}


int main()
{
//    problem1::run();
//    problem2::run();
//    problem3::run();
    problem4::run();
}