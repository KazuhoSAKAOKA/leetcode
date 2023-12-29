// leetcode_Q0056.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(begin(intervals), end(intervals), [](const auto& l, const auto& r)
            {
                return l.front() < r.front();
            });

        int beforeStart = intervals.front().front();
        int beforeEnd = intervals.front().back();
        vector<vector<int>> ret;
        for (int i = 1; i < intervals.size(); i++) {
            auto& list = intervals[i];
            if (beforeEnd < list.front()) {
                ret.emplace_back(vector<int>{beforeStart, beforeEnd});
                beforeStart = list.front();
                beforeEnd = list.back();
            }
            else {
                beforeEnd = max(beforeEnd, list.back());
            }
        }
        ret.emplace_back(vector<int>{beforeStart, beforeEnd});
        return ret;
    }
};

void test(vector<vector<int>>&& intervals) {
    const auto ret = Solution().merge(intervals);

    for (auto&& list : ret) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    test({ {1,4}, {2,3},});
    test({{1,3},{2,6},{8,10},{15,18} });

    test({ {1,4},{4,5} });

}

