// leetcode_Q2285.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        unordered_map<int, vector<int>> graph;
        for (auto&& road : roads) {
            graph[road[0]].emplace_back(road[1]);
            graph[road[1]].emplace_back(road[0]);
        }

        map<int, vector<int>> counts;
        for (auto&& [k, v] : graph) {
            counts[v.size()].emplace_back(k);
        }
        
        long long importance = n;
        vector<long long> importances(n);
        for (auto it = crbegin(counts); it != crend(counts); ++it) {
            const auto& cities = (*it).second;
            for (auto&& city : cities) {
                importances[city] = importance;
                importance--;
            }
        }

        long long total = 0;

        for (auto&& road : roads) {
            total += importances[road[0]] + importances[road[1]];
        }

        return total;
    }
};

void test(int n, vector<vector<int>>&& roads) {
    cout << Solution().maximumImportance(n, roads) << endl;
}

int main()
{
    test(5, get_matrix_int("[[0,1]]"));
    test(5, get_matrix_int("[[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]"));
    test(5, get_matrix_int("[[0,3],[2,4],[1,3]]"));
}