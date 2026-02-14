// leetcode_Q0799.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double> before(1, poured);
        for (int i = 0; i < query_row; i++) {
            vector<double> current(size(before) + 1, 0.0);
            for (int j = 0; j < size(before); j++) {
                if (before[j] > 1.0) {
                    const auto v = before[j] - 1.0;
                    current[j] += v / 2;
                    current[j + 1] += v / 2;
                }
            }
            swap(before, current);
        }
        return min(1.0, before[query_glass]);
    }
};

static void test(int poured, int query_row, int query_glass) {
    cout << Solution().champagneTower(poured, query_glass, query_glass) << endl;
}

int main()
{
    test(1, 1, 1);
    test(2, 1, 1);
    test(100000009, 33, 17);
    return 0;
}