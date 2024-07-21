// leetcode_Q2392.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static vector<int> topological_sort(int k, const vector<vector<int>>& graph) {
        vector<int> in_count(k);
        for (int i = 0; i < k; i++) {
            for (auto dest : graph[i]) {
                in_count[dest]++;
            }
        }
        
        queue<pair<int,int>> work_queue;
        for (int i = 0; i < k; i++) {
            if (in_count[i] == 0) {
                work_queue.push({ 0,i });
            }
        }
        vector<int> ans;
        while (!work_queue.empty()) {
            const auto [step, current_vertex] = work_queue.front();
            work_queue.pop();
            ans.push_back(current_vertex);
            for (auto&& dest : graph[current_vertex]) {
                in_count[dest]--;
                if (in_count[dest] == 0) {
                    work_queue.push({ step + 1, dest });
                }
            }
        }

        return ans;
    }

    static vector<vector<int>> build_graph(int k, const vector<vector<int>>& conditions) {
        vector<vector<int>> graph(k, vector<int>());
        for (auto&& item : conditions) {
            graph[item.front() - 1].push_back(item.back() - 1);
        }
        return graph;
    }
    static vector<int> make_reverse(int k, const vector<int>& sorted) {
        vector<int> list(k);
        for (int i = 0; i < k; i++) {
            list[sorted[i]] = i;
        }
        return list;
    }

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        const auto row_graph = build_graph(k, rowConditions);
        const auto col_graph = build_graph(k, colConditions);
        const auto sorted_rows = topological_sort(k, row_graph);
        const auto sorted_cols = topological_sort(k, col_graph);
        if (sorted_rows.empty() || sorted_cols.empty() || sorted_rows.size() != k || sorted_cols.size() != k) {
            return vector<vector<int>>();
        }

        const auto row_order_to_no = make_reverse(k, sorted_rows);
        const auto col_order_to_no = make_reverse(k, sorted_cols);

        vector<vector<int>> ans(k, vector<int>(k, 0));

        for (int i = 0; i < k; i++) {
            const int row_index = row_order_to_no[i];
            const int col_index = col_order_to_no[i];
            if (ans[row_index][col_index] != 0) {
                return vector<vector<int>>();
            }
            ans[row_index][col_index] = i + 1;
        }
        return ans;
    }
};

void test(int k, vector<vector<int>>&& rowConditions, vector<vector<int>>&& colConditions) {
    const auto ans = Solution().buildMatrix(k, rowConditions, colConditions);
    cout << "===============" << endl;
    for (auto&& cols : ans) {
        for (auto&& value : cols) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    test(3, get_matrix_int("[[1,2],[3,2]]"), get_matrix_int("[[2,1],[3,2]]"));
    test(3, get_matrix_int("[[1,2],[2,3],[3,1],[2,3]]"), get_matrix_int("[[2,1]]"));
}