// weekly_contest_394.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;


namespace problem1 {

class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char, int> count_map;
        for (auto&& c : word) {
            count_map[c]++;
        }

        int count = 0;
        for (char c = 'a'; c <= 'z'; c++) {
            const char uc = c + ('A' - 'a');
            if (count_map.find(c) != cend(count_map) && count_map.find(uc) != cend(count_map)) {
                count++;
            }
        }

        return count;
    }
};
void test(string&& word) {
    cout << Solution().numberOfSpecialChars(word) << endl;
}
void run() {
    test("aaAbcBC");
    test("abc");
    test("abBCab");
}
}


namespace problem2 {

class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char, size_t> occ_low_map;
        unordered_map<char, size_t> occ_upp_map;
        for (size_t i = 0; i < word.size(); i++) {
            const char c = word[i];
            if ('a' <= c) {
                occ_low_map[c] = i;
            }
            else {
                if (occ_upp_map.find(c) == cend(occ_upp_map)) {
                    occ_upp_map.insert(make_pair(c, i));
                }
            }
        }

        int count = 0;
        for (char c = 'a'; c <= 'z'; c++) {
            const auto it_low = occ_low_map.find(c);
            if (it_low != cend(occ_low_map)) {
                const char uc = c + ('A' - 'a');
                const auto it_upp = occ_upp_map.find(uc);
                if (it_upp != cend(occ_upp_map)) {
                    if (it_low->second < it_upp->second) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};
void test(string&& word) {
    cout << Solution().numberOfSpecialChars(word) << endl;
}
void run() {
    test("aaAbcBC");
    test("abc");
    test("AbBCab");
}
}


namespace problem3 {


class Solution {
public:



    int minimumOperations(vector<vector<int>>& grid) {
        const int h = grid.size();
        const int w = grid.front().size();

        int count = 0;
        vector<unordered_map<int, int>> values(w, unordered_map<int, int>());

        for (int j = 0; j < w; j++) {
            for (int i = 0; i < h; i++) {
                values[j][grid[i][j]]++;
            }
        }
        
        vector<unordered_map<int, int>> dp(w + 1, unordered_map<int, int>());
        dp[0][-1] = h;
        for (auto&& [k, v] : values[0]) {
            dp[0][k] = (h - v);
        }

        for (int j = 1; j < w; j++) {
            for (auto&& [k, v] : values[j]) {
                int min_value = INT_MAX;
                for (auto&& [dpk, dpv] : dp[j - 1]) {
                    if (dpk != k) {
                        min_value = min(min_value, dpv);
                    }
                }
                dp[j][k] = min_value + (h - v);
            }
            int all_of_min = INT_MAX;
            for (auto&& [dpk, dpv] : dp[j - 1]) {
                all_of_min = min(all_of_min, dpv);
            }
            dp[j][-1] = all_of_min + h;
        }
        
        int ans = INT_MAX;
        for (auto&& [k, v] : dp[w - 1]) {
            ans = min(ans, v);
        }
        return ans;


    }
};
void test(vector<vector<int>>&& grid) {
    cout << Solution().minimumOperations(grid) << endl;
}
void run() {
    test({ {1,1,1,} });
    test({ { 5,5,5 }, { 5,5,5, }, { 5,5,5, } });
    test({ {1,0,2,},{1,0,2,} });
    test({ {1,1,1}, {0,0,0,}, });
    test({ {1},{2},{3}, });
}

/*
vector<vector<vector<int>>> dp(h, vector<vector<int>>(w, vector<int>(2, 0)));

dp[h - 1][w - 1][0] = 0;
dp[h - 1][w - 1][1] = 1;

for (int j = w - 2; j >= 0; j--) {
    if (grid[h - 1][j] != grid[h - 1][j + 1]) {
        dp[h - 1][j][0] = dp[h - 1][j + 1][0];
        dp[h - 1][j][1] = dp[h - 1][j + 1][1] + 1;
    }
    else {
        dp[h - 1][j][0] = dp[h - 1][j + 1][1];
        dp[h - 1][j][1] = dp[h - 1][j + 1][0] + 1;
    }
}

for (int i = h - 2; i >= 0; i--) {
    if (grid[i][w - 1] == grid[i + 1][w - 1]) {
        dp[i][w - 1][0] = dp[i + 1][w - 1][0];
        dp[i][w - 1][1] = dp[i + 1][w - 1][1] + 1;
    }
    else {
        dp[i][w - 1][0] = dp[i + 1][w - 1][1];
        dp[i][w - 1][1] = min(dp[i + 1][w - 1][0], dp[i + 1][w - 1][1]) + 1;
    }
}



//for (int i = 0; i < grid.size() - 1; i++) {
//    for (int j = 0; j < grid.front().size() - 1; j++) {
//        if (grid[i][j] == grid[i + 1][j] != grid[i][j] == grid[i][j + 1]) {
//            dp[i][j][0] = dp[i - 1][dp - ]
//        }
//    }
//}

return min(dp[0][0][0], dp[0][0][1]);*/
}



namespace problem4 {

class Solution {
public:

    struct graph {
        struct edge {
            int node_;
            int weight_;
            int index_;
        };
        vector<vector<edge>> nodes_;

        graph(int n) : nodes_(n, vector<edge>()) {}

        void add(int s, int d, int w, int index) {
            nodes_[s].emplace_back(edge{ d, w, index, });
            nodes_[d].emplace_back(edge{ s, w, index, });
        }


        vector<int> dijkstra(int start) {
            vector<int> costs(nodes_.size(), INT_MAX);
            costs[start] = 0;
            struct P {
                int node_;
                int current_cost_;

                bool operator < (const P& other) const {
                    return current_cost_ > other.current_cost_;
                }
            };
            priority_queue<P> p_queue;

            p_queue.push({ start, 0 });

            while (!p_queue.empty()) {
                const auto p = p_queue.top();
                const auto current_node = p.node_;
                const auto current_cost = p.current_cost_;
                p_queue.pop();
                if (costs[current_node] < current_cost) { continue; }
                for (auto&& edge : nodes_[current_node]) {
                    if (costs[edge.node_] > costs[current_node] + edge.weight_) {
                        costs[edge.node_] = costs[current_node] + edge.weight_;
                        p_queue.push({ edge.node_, costs[edge.node_] });
                    }
                }
            }
            return costs;
        }

    };

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        graph g(n);
        for (int i = 0; i < edges.size(); i++) {
            g.add(edges[i][0], edges[i][1], edges[i][2], i);
        }

        const auto costs_start_to_goal = g.dijkstra(0);
        const auto costs_goal_to_start = g.dijkstra(n - 1);
        const auto min_cost = costs_start_to_goal[n - 1];
        vector<bool> ans(edges.size(), false);
        if (min_cost < INT_MAX) {
            for (int i = 0; i < edges.size(); i++) {
                const auto& edge = edges[i];
                const auto s = edge[0];
                const auto e = edge[1];
                const auto w = edge[2];
                if (min(costs_start_to_goal[s] + costs_goal_to_start[e] + w, costs_goal_to_start[s] + costs_start_to_goal[e] + w) == min_cost) {
                    ans[i] = true;
                }
            }
        }
        return ans;
    }
};
void test(int n, vector<vector<int>>&& edges) {
    const auto ans = Solution().findAnswer(n, edges);
    for (auto&& value : ans) {
        cout << (value ? "true" : "false") << ",";
    }
    cout << endl;
}
void run() {
    test(3, { {2,1,6,} });
    test(6, { {0,1,4},{0,2,1},{1,3,2},{1,4,3},{1,5,1},{2,3,1},{3,5,3},{4,5,2} });
    test(4, { {2,0,1},{0,1,1},{0,3,4},{3,2,2} });
}
}


int main()
{
//    problem1::run();
//    problem2::run();
//    problem3::run();
    problem4::run();
}