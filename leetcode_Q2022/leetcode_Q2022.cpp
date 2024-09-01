// leetcode_Q2022.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (size(original) != m * n) {
            return vector<vector<int>>();
        }
        vector<vector<int>> ans(m, vector<int>(n));

        for (int i = 0; i < size(original); i++) {
            int y = i / n;
            int x = i % n;
            ans[y][x] = original[i];
        }
        return ans;
    }
};

void test(vector<int>&& original, int m, int n) {
    const auto ans = Solution().construct2DArray(original, m, n);
    cout << "[";
    for (auto&& values : ans) {
        cout << "[";
        for (auto&& value : values) {
            cout << value << ",";
        }
        cout << "]";
    }
    cout << "]";
    cout << endl;
}

int main()
{
    test(get_list_int("[1,2,3,4]"), 2, 2);
    test(get_list_int("[1,2,3]"), 1, 3);
    test(get_list_int("[1,2]"), 1, 1);
    return 0;
}
