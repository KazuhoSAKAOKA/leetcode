// leetcode_Q1791.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_map<int, int> graph;
        for (auto&& edge : edges) {
            graph[edge[0]]++;
            graph[edge[1]]++;
        }
        const auto it = max_element(cbegin(graph), cend(graph), [](const auto& a, const auto& b) { return a.second < b.second; });
        return it->first;
    }
};

void test(vector<vector<int>>&& edges) {
    cout << Solution().findCenter(edges) << endl;
}

int main()
{
    test(get_matrix_int("[[1,2],[2,3],[4,2]]"));
    test(get_matrix_int("[[1,2],[5,1],[1,3],[1,4]]"));
}