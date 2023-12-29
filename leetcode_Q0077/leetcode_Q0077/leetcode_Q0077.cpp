// leetcode_Q0077.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include <vector>

using namespace std;

class Solution {
public:

    void combination(const vector<int>& list, size_t index, int remain, vector<int>& current, vector<vector<int>>& ans) {
        if (remain == 0) {
            ans.emplace_back(current);
            return;
        }

        for (size_t i = index; i < list.size(); i++) {
            current.push_back(list[i]);
            combination(list, i + 1, remain - 1, current, ans);
            current.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ret;
        vector<int> list;
        for (auto i = 0; i < n; i++) {
            list.emplace_back(i + 1);
        }
        vector<int> current;
        combination(list, 0, k, current, ret);
        return ret;
    }
};

void test(int n, int k) {
    const auto ret = Solution().combine(n, k);
    for (auto&& list : ret) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
}

int main()
{
    test(4, 2);
    test(1, 1);
}

