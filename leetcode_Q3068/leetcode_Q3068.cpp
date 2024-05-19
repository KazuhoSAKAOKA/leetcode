// leetcode_Q3068.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static long long brute_force(const vector<int>& nums, int k, const vector<vector<int>>& edges) {
        vector<bool> sw(edges.size(), false);

        auto get_next = [](vector<bool>& sw)->bool {
            int index = 0;
            while (index < sw.size() && sw[index]) {
                sw[index] = false;
                index++;
            }
            if (index == sw.size()) {
                return false;
            }
            sw[index] = true;
            return true;
            };
        bool first = true;
        long long max_value = 0;
        while (first || get_next(sw)) {
            first = false;
            auto work(nums);
            for (int i = 0; i < edges.size(); i++) {
                if (sw[i]) {
                    work[edges[i].front()] ^= k;
                    work[edges[i].back()] ^= k;
                }
            }
            long long current = 0;
            for (int i = 0; i < work.size(); i++) {
                current += static_cast<long long>(work[i]);
            }
            max_value = max(max_value, current);
        }
        return max_value;
    }
    static long long wrong_answer(const vector<int>& nums, int k, const vector<vector<int>>& edges) {
        vector<vector<long long>> dp(edges.size(), vector<long long>(2, 0LL));
        long long current_sum = accumulate(cbegin(nums), cend(nums), 0LL, [](const long a, const long b) { return a + b; });
        dp[0][0] = current_sum;
        dp[0][1] = current_sum - nums[edges[0].front()] + (nums[edges[0].front()] ^ k) - nums[edges[0].back()] + (nums[edges[0].back()] ^ k);

        for (int i = 1; i < edges.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            const long long diff = -nums[edges[i].front()] + (nums[edges[i].front()] ^ k) - nums[edges[i].back()] + (nums[edges[i].back()] ^ k);
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + diff;
        }

        const auto ans = max(dp[edges.size() - 1][0], dp[edges.size() - 1][1]);
        if (ans != brute_force(nums, k, edges)) {
            cout << "invalid!" << endl;
        }
        return ans;
    }

    static void rec(const vector<int>& nums, int k, const unordered_map<int, vector<int>>& graph, int node, int parent, vector<vector<long long>>& dp) {

        const auto it = graph.find(node);
        if (it == cend(graph)) {
            throw std::exception();
        }
        const auto& nodes1 = it->second;

        vector<int> nodes;
        for (int i = 0; i < nodes1.size(); i++) {
            if (nodes1[i] != parent) {
                nodes.emplace_back(nodes1[i]);
            }
        }

        if (nodes.empty()) {
            dp[node][0] = static_cast<long long>(nums[node]);
            dp[node][1] = static_cast<long long>(nums[node] ^ k);
            return;
        }

        for (auto&& child_node : nodes) {
            rec(nums, k, graph, child_node, node, dp);
        }

        vector<bool> sw(nodes.size(), false);
        auto get_next = [](vector<bool>& sw)->bool {
            int index = 0;
            while (index < sw.size() && sw[index]) {
                sw[index] = false;
                index++;
            }
            if (index == sw.size()) {
                return false;
            }
            sw[index] = true;
            return true;
            };
        bool first = true;
        int child_val_even = 0;
        int child_val_odd = 0;
        while (first || get_next(sw)) {
            first = false;
            int current = 0;
            int current_count = 0;
            for (int i = 0; i < nodes.size(); i++) {
                if (sw[i]) {
                    current += dp[nodes[i]][1];
                    current_count++;
                }
                else {
                    current += dp[nodes[i]][0];
                }
            }
            if (current_count % 2 == 1) {
                child_val_odd = max(child_val_odd, current);
            }
            else {
                child_val_even = max(child_val_even, current);
            }
        }
        const auto self_val_even = static_cast<long long>(nums[node]);
        const auto self_val_odd = static_cast<long long>(nums[node] ^ k);

        dp[node][0] = max(child_val_even + self_val_even, child_val_odd + self_val_odd);
        dp[node][1] = max(child_val_even + self_val_odd, child_val_odd + self_val_even);
    }


    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> graph;
        for (auto&& edge : edges) {
            graph[edge.front()].emplace_back(edge.back());
            graph[edge.back()].emplace_back(edge.front());
        }
        vector<vector<long long>> dp(nums.size(), vector<long long>(2, 0LL));
        rec(nums, k, graph, 0, -1, dp);
        
        return dp[0][0];
    }
};

void test(vector<int>&& nums, int k, vector<vector<int>>&& edges) {
    cout << Solution().maximumValueSum(nums, k, edges) << endl;
}

int main()
{
    test(get_list_int("[1,2,1]"), 3, get_matrix_int("[[0,1],[0,2]]"));

    test(get_list_int("[0,92,56,3,34,23,56]"), 7, get_matrix_int("[[2,6],[4,1],[5,0],[1,0],[3,1],[6,3]]"));


    test(get_list_int("[24,78,1,97,44]"), 6, get_matrix_int("[[0,2],[1,2],[4,2],[3,4]]"));
    test(get_list_int("[2,3]"), 7, get_matrix_int("[[0,1]]"));
    test(get_list_int("[7,7,7,7,7,7]"), 3, get_matrix_int("[[0,1],[0,2],[0,3],[0,4],[0,5]]"));
}