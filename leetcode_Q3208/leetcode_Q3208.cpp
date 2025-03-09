// leetcode_Q3208.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static bool judge(const vector<int>& red_colors, const vector<int>& blue_colors, int head_color, int top_index) {
        const vector<int>& even_colors = head_color == 0 ? red_colors : blue_colors;
        const vector<int>& odd_colors = head_color == 1 ? red_colors : blue_colors;
        const auto check_even_index = (top_index + 1) % 2;
        const auto check_odd_index = (top_index + 0) % 2;
        return even_colors[check_even_index] == 0 && odd_colors[check_odd_index] == 0;
    }

    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int count = 0;

        vector<int> red_colors(2);
        vector<int> blue_colors(2);
        for (int i = 0; i < k; i++) {
            const auto index = i % 2;
            if (colors[i] == 0) {
                red_colors[index]++;
            }
            else {
                blue_colors[index]++;
            }
        }
        if (judge(red_colors, blue_colors, colors[0], 0)) {
            count++;
        }

        for (int i = k; i < size(colors) + k - 1; i++) {
            const auto index = i % 2;
            if (colors[i % size(colors)] == 0) {
                red_colors[index]++;
            }
            else {
                blue_colors[index]++;
            }
            const auto index1 = (i - k) % 2;
            if (colors[(i - k) % size(colors)] == 0) {
                red_colors[index1]--;
            }
            else {
                blue_colors[index1]--;
            }
            if (judge(red_colors, blue_colors, colors[i % size(colors)], i)) {
                count++;
            }
        }
        return count;
    }
};

void test(vector<int>&& colors, int k) {
    cout << Solution().numberOfAlternatingGroups(colors, k) << endl;
}
int main()
{
    test(get_list_int("[0,1,0,1,0]"), 3);
    test(get_list_int("[0,1,0,0,1,0,1]"), 6);
    test(get_list_int("[1,1,0,1]"), 4);
    return 0;
}