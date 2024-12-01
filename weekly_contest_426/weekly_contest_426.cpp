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
    int smallestNumber(int n) {
        int value = 1;
        int bit = 0;
        while (value < n) {
            bit++;
            value |= (1 << bit);
        }
        return value;
    }
};
static void test(int n) {
    cout << Solution().smallestNumber(n) << endl;
}
static void run() {
    test(5);
    test(10);
    test(3);
}
}


namespace problem2 {
template <typename TIT, typename T>  TIT find_exact(const TIT& b,const TIT& e, const T& value) {
    auto it = std::lower_bound(b, e, value); if (it != e && !(value < *it)) {
        return it;
    }
    else {
        return e;
    }
}

class Solution {
public:


    int getLargestOutlier(vector<int>& nums) {
        sort(begin(nums), end(nums));
        const int total = accumulate(cbegin(nums), cend(nums), 0);
        int max_outlier = INT_MIN;
        for (auto outlier_candidate_it = cbegin(nums); outlier_candidate_it != cend(nums); ++outlier_candidate_it) {
            const auto remain = total - *outlier_candidate_it;
            if (remain % 2 != 0) { continue; }
            const auto expect_sum = remain / 2;
            const auto it = find_exact(cbegin(nums), cend(nums), expect_sum);
            if (it != cend(nums)) {
                if (it == outlier_candidate_it) {
                    const auto next_it = next(it);
                    if (next_it != cend(nums) && *next_it == *it) {
                        max_outlier = max(max_outlier, *outlier_candidate_it);
                    }
                }
                else {
                    max_outlier = max(max_outlier, *outlier_candidate_it);
                }
            }
        }

        return max_outlier;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().getLargestOutlier(nums) << endl;
}
static void run() {
    test(get_list_int("[752,678,-483,-583,201,0,-886,-474,-171]"));
    test(get_list_int("[-108,-108,-517]"));
    test(get_list_int("[2,3,5,10]"));
    test(get_list_int("[-2,-1,-3,-6,4]"));
    test(get_list_int("[1,1,1,1,1,5,5]"));
}
}
namespace problem3 {
class Solution {
public:

    static int dfs(const vector<vector<int>>& graph, int remain, int node, int from) {
        if (remain == 0) {
            return 1;
        }
        int count = 1;
        for (auto&& target : graph[node]) {
            if (target == from) { continue; }
            count += dfs(graph, remain - 1, target, node);
        }
        return count;
    }

    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        const auto n = size(edges1) + 1;
        const auto m = size(edges2) + 1;

        vector<vector<int>> graph1(n);
        for (auto&& edge : edges1) {
            graph1[edge.front()].emplace_back(edge.back());
            graph1[edge.back()].emplace_back(edge.front());
        }
        vector<vector<int>> graph2(m);
        for (auto&& edge : edges2) {
            graph2[edge.front()].emplace_back(edge.back());
            graph2[edge.back()].emplace_back(edge.front());
        }


        vector<int> targets(n);
        for (int i = 0; i < n; i++) {
            targets[i] = dfs(graph1, k, i, -1);
        }

        vector<int> dests(m);
        if (k > 0) {
            for (int i = 0; i < m; i++) {
                dests[i] = dfs(graph2, k - 1, i, -1);
            }
        }
        int max_targets = 0;
        for (int j = 0; j < m; j++) {
            max_targets = max(max_targets, dests[j]);
        }
        vector<int> ans;
        ans.reserve(n);
        for (int i = 0; i < n; i++) {
            ans.emplace_back(targets[i] + max_targets);
        }

        return ans;
    }
};
static void test(vector<vector<int>>&& edges1, vector<vector<int>>&& edges2, int k) {
    output(Solution().maxTargetNodes(edges1, edges2, k));
}
static void run() {
    test(get_matrix_int("[[0,1]"), get_matrix_int("[[0,1]"), 0);
    test(get_matrix_int("[[0,1],[0,2],[2,3],[2,4]]"), get_matrix_int("[[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]"), 2);
    test(get_matrix_int("[[0,1],[0,2],[0,3],[0,4]]"), get_matrix_int("[[0,1],[1,2],[2,3]]"), 1);
}
}
namespace problem4 {
class Solution {
public:
    static void dfs(const vector<vector<int>>& graph, int distance, int node, int from, vector<int>& colors) {
        colors[node] = distance % 2;
        for (auto&& target : graph[node]) {
            if (target == from) { continue; }
            dfs(graph, distance + 1, target, node, colors);
        }
    }
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        const auto n = size(edges1) + 1;
        const auto m = size(edges2) + 1;

        vector<vector<int>> graph1(n);
        for (auto&& edge : edges1) {
            graph1[edge.front()].emplace_back(edge.back());
            graph1[edge.back()].emplace_back(edge.front());
        }
        vector<vector<int>> graph2(m);
        for (auto&& edge : edges2) {
            graph2[edge.front()].emplace_back(edge.back());
            graph2[edge.back()].emplace_back(edge.front());
        }


        vector<int> colors1(n);
        dfs(graph1, 0, 0, -1, colors1);
        vector<int> colors2(m);
        dfs(graph2, 0, 0, -1, colors2);

        const int graph1_even = count_if(cbegin(colors1), cend(colors1), [](auto a) {return a == 0; });
        const int graph1_odd = n - graph1_even;

        const int graph2_even = count_if(cbegin(colors2), cend(colors2), [](auto a) {return a == 0; });
        const int graph2_odd = m - graph2_even;

        int max_targets = max(graph2_even, graph2_odd);
        vector<int> ans;
        ans.reserve(n);
        for (int i = 0; i < n; i++) {
            ans.emplace_back((colors1[i] == 0 ? graph1_even : graph1_odd) + max_targets);
        }

        return ans;
    }
};
static void test(vector<vector<int>>&& edges1, vector<vector<int>>&& edges2) {
    output(Solution().maxTargetNodes(edges1, edges2));
}
static void run() {
    test(get_matrix_int("[[0,1],[0,2],[2,3],[2,4]]"), get_matrix_int("[[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]"));
    test(get_matrix_int("[[0,1],[0,2],[0,3],[0,4]]"), get_matrix_int("[[0,1],[1,2],[2,3]]"));
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