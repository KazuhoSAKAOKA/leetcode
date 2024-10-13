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
#include <cassert>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    static string itobs(int num) {
        string v;
        bool exist = false;
        for (int i = 31; i >= 0; i--) {
            if ((num & (1 << i)) != 0) {
                v += '1';
                exist = true;
            }
            else {
                if (exist) {
                    v += '0';
                }
            }
        }
        return v;
    }

    int maxGoodNumber(vector<int>& nums) {
        vector<string> bins;
        bins.reserve(size(nums));
        transform(cbegin(nums), cend(nums), back_inserter(bins), itobs);
        int value = 0;
        value = max(value, stoi(bins[0] + bins[1] + bins[2], nullptr, 2));
        value = max(value, stoi(bins[0] + bins[2] + bins[1], nullptr, 2));
        value = max(value, stoi(bins[1] + bins[0] + bins[2], nullptr, 2));
        value = max(value, stoi(bins[1] + bins[2] + bins[0], nullptr, 2));
        value = max(value, stoi(bins[2] + bins[1] + bins[0], nullptr, 2));
        value = max(value, stoi(bins[2] + bins[0] + bins[1], nullptr, 2));
        return value;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().maxGoodNumber(nums) << endl;
}
void run() {
    test(get_list_int("[1,2,3]"));
    test(get_list_int("[2,8,16]"));
}
}
namespace problem2 {
class Solution {
public:


    unordered_set<int> bfs(const vector<vector<int>>& graph, int start) {
        unordered_set<int> arriveds;
        queue<int> q;
        q.push(start);
        arriveds.insert(start);
        while (!q.empty()) {
            const auto current = q.front();
            q.pop();
            for (auto&& next : graph[current]) {
                if (arriveds.count(next) == 0) {
                    arriveds.insert(next);
                    q.push(next);
                }
            }
        }
        return arriveds;
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        vector<vector<int>> graph2(n);
        for (auto&& invocate : invocations) {
            graph[invocate[0]].emplace_back(invocate[1]);
            graph2[invocate[0]].emplace_back(invocate[1]);
            graph2[invocate[1]].emplace_back(invocate[0]);
        }
        unordered_set<int> suspiciouss = bfs(graph, k);
        if (size(suspiciouss) == n) {
            return vector<int>();
        }

        unordered_set<int> remain;

        int firstsafe = -1;
        queue<int> q;


        for (int i = 0; i < n; i++) {
            if (suspiciouss.count(i) == 0) {
                q.push(i);
                remain.insert(i);
            }
        }
        while (!q.empty()) {
            const auto current = q.front();
            q.pop();
            for (auto&& next : graph2[current]) {
                if (remain.count(next)==0) {
                    remain.insert(next);
                    q.push(next);
                }
            }
        }
  
        return vector<int>(cbegin(remain), cend(remain));
    }
};
void test(int n, int k, vector<vector<int>>&& invocations) {
    output(Solution().remainingMethods(n, k, invocations));
}
void run() {
    test(3, 2, get_matrix_int("[[1,0],[2,0]]"));

    test(4, 1, get_matrix_int("[[1,2],[0,1],[3,2]]"));
    test(5, 0, get_matrix_int("[[1,2],[0,2],[0,1],[3,4]]"));
    test(3, 2, get_matrix_int("[[1,2],[0,1],[2,0]]"));
}
}
namespace problem3 {
class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }


        vector<size_t> connecting_edges(n);
        map<size_t, vector<int>> rev_map;
        for (size_t i = 0; i < n; i++) {
            connecting_edges[i] = size(graph[i]);
            rev_map[size(graph[i])].emplace_back(i);
        }
        if (size(rev_map[1]) == 2) {
            //一列
            vector<vector<int>> ans;
            vector<int> inner;
            const int first = rev_map[1].front();
            const int last = rev_map[1].back();
            inner.emplace_back(first);

            auto find_next = [&](int current, int before) {
                for (auto&& next : graph[current]) {
                    if (next != before) {
                        return next;
                    }
                }
                return -1;
                };
            int before = first;
            int cur = find_next(first, -1);
            inner.emplace_back(cur);
            while (cur != last) {
                int temp = find_next(cur, before);
                before = cur;
                cur = temp;
                inner.emplace_back(cur);
            }
            ans.emplace_back(inner);
            return ans;
        }
        else {
            const auto& corners = rev_map[2];
            assert(size(corners) == 4);
            const auto& edges = rev_map[3];
            const auto& inners = rev_map[4];
            const auto edge_counts = size(edges);
            size_t w = 0, h = 0;
            for (size_t i = 0; i < edge_counts / 2; i++) {
                w = 2 + i;
                h = 2 + (edge_counts / 2 - i);
                if (w * h == n) {
                    break;
                }
            }
            assert(w != 0);
            vector<vector<int>> ans(h, vector<int>(w, 0));

            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {

                }
            }
        }
    }
};

void test(int n, vector<vector<int>>&& edges) {
    const auto ans = Solution().constructGridLayout(n, edges);
    for (auto&& l : ans) {
        for (auto&& value : l) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}
void run() {
    test(5, get_matrix_int("[[0,1],[1,3],[2,3],[2,4]]"));
    //test(4, get_matrix_int("[[0,1],[0,2],[1,3],[2,3]]"));
    //test(9, get_matrix_int("[[0,1],[0,4],[0,5],[1,7],[2,3],[2,4],[2,5],[3,6],[4,6],[4,7],[6,8],[7,8]]"));
}
}

namespace problem4 {
void run() {

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