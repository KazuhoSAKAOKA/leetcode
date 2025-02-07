// leetcode_Q3160.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        map<int, int> ball_colors;
        map<int, int> colors_counts;
        int distincts = 0;
        colors_counts[0] = limit + 1;

        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            const auto ball = query.front();
            const auto color = query.back();
            const auto it = ball_colors.find(ball);
            int cur_color;
            if (it == end(ball_colors)) {
                cur_color = 0;
            }
            else {
                cur_color = it->second;
                colors_counts[cur_color]--;
                if (colors_counts[cur_color] == 0) {
                    distincts--;
                }
            }
            if (color != 0) {
                if (colors_counts[color] == 0) {
                    distincts++;
                }
            }
            colors_counts[color]++;
            ball_colors[ball] = color;
            ans.emplace_back(distincts);
        }
        return ans;
    }
};

void test(int limit, vector<vector<int>>&& queries) {
    output(Solution().queryResults(limit, queries));
}
int main()
{
    test(4, get_matrix_int("[[0,1],[1,2],[2,2],[3,4],[4,5]]"));
    test(4, get_matrix_int("[[1,4],[2,5],[1,3],[3,4]]"));
    return 0;
}