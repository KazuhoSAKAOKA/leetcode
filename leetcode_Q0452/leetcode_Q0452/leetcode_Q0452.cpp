// leetcode_Q0452.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(begin(points), end(points), [](const auto& a, const auto& b) { return a.back() < b.back(); });
        vector<int> arrows;
        int index = 0;
        while (index < points.size()) {
            if (lower_bound(cbegin(arrows), cend(arrows), points[index].front()) == cend(arrows)) {
                arrows.emplace_back(points[index].back());
            }
            index++;
        }
        return static_cast<int>(arrows.size());
    }
};

void test(vector<vector<int>>&& points) {
    cout << Solution().findMinArrowShots(points) << endl;
}

int main()
{
    test({ {10,16},{2,8},{1,6},{7,12} });
    test({ {1,2},{3,4},{5,6},{7,8} });
    test({ {1,2},{2,3},{3,4},{4,5} });
}