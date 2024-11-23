// leetcode_Q1861.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {

        const int width = size(box.front());
        const int height = size(box);
        vector<vector<char>> ans(width, vector<char>(height, '.'));

        for (int i = 0; i < height; i++) {
            int index = width - 1;
            int current_bottom = -1;
            const int ans_col = height - i - 1;
            while (index >= 0) {
                const char current_target = box[i][index];
                if (current_target == '.') {
                    if (current_bottom < 0) {
                        current_bottom = index;
                    }
                }
                else if (current_target == '*') {
                    current_bottom = -1;
                    ans[index][ans_col] = '*';
                }
                else {
                    if (current_target != '#') { throw exception(); }
                    if (current_bottom < 0) {
                        ans[index][ans_col] = '#';
                    }
                    else {
                        ans[current_bottom][ans_col] = '#';
                        current_bottom--;
                    }
                }
                index--;
            }
        }
        return ans;
    }
};

void test(vector<vector<char>>&& box) {
    const auto ans = Solution().rotateTheBox(box);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    test(get_matrix_char(R"([["#",".","*","."],["#","#","*","."]])"));
    test(get_matrix_char(R"([["#",".","#"]])"));
    test(get_matrix_char(R"([["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]])"));

    return 0;
}