// leetcode_Q2940.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> ans(size(queries));
        vector<int> indexes(size(queries));
        for (int i = 0; i < size(queries); i++) {
            indexes[i] = i;
        }
        for (auto&& query : queries) {
            const int small = min(query.front(), query.back());
            const int large = max(query.front(), query.back());
            query.front() = small;
            query.back() = large;
        }

        sort(begin(indexes), end(indexes), [&](auto a, auto b) { return queries[a].back() > queries[b].back();  });
        
        vector<int> mono_stack_vec;
        int stack_index = size(heights) - 1;


        for (auto&& index : indexes) {
            const auto& query = queries[index];
            const auto small = query.front();
            const auto large = query.back();
            if (small == large) {
                ans[index] = query.front();
            }
            else if(heights[small] < heights[large]){
                ans[index] = large;
            }
            else {
                while (stack_index > large) {
                    while (!mono_stack_vec.empty() && heights[mono_stack_vec.back()] < heights[stack_index]) {
                        mono_stack_vec.pop_back();
                    }
                    mono_stack_vec.push_back(stack_index);
                    stack_index--;
                }
                if (mono_stack_vec.empty()) {
                    ans[index] = -1;
                }
                else {
                    const auto current_min = max(heights[small], heights[large]);
                    if (current_min < heights[mono_stack_vec.back()]) {
                        ans[index] = mono_stack_vec.back();
                    }
                    else {
                        if (heights[mono_stack_vec[0]] <= current_min) {
                            ans[index] = -1;
                        }
                        else {
                            auto bin_search = [&](int ok, int ng, int value)->int {
                                while (abs(ng - ok) > 1) {
                                    const auto mid = (ok + ng) / 2;
                                    if (value < heights[mono_stack_vec[mid]]) {
                                        ok = mid;
                                    }
                                    else {
                                        ng = mid;
                                    }
                                }
                                return ok;
                                };

                            auto result = bin_search(0, size(mono_stack_vec), current_min);
                            ans[index] = mono_stack_vec[result];
                        }
                    }

                }
            }
        }

        return ans;
    }
};

void test(vector<int>&& heights, vector<vector<int>>&& queries) {
    output(Solution().leftmostBuildingQueries(heights, queries));
}
int main()
{
    test(get_list_int("[6,4,8,5,2,7]"), get_matrix_int("[[0,1],[0,3],[2,4],[3,4],[2,2]]"));
    test(get_list_int("[5,3,8,2,6,1,4,6]"), get_matrix_int("[[0,7],[3,5],[5,2],[3,0],[1,6]]"));
    return 0;
}