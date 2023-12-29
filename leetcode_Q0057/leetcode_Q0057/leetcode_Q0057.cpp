// leetcode_Q0057.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        const auto newIntervalFront = newInterval.front();
        const auto newIntervalBack = newInterval.back();
        if (intervals.empty()) {
            return vector<vector<int>>{newInterval};
        }

        if (newIntervalBack < intervals.front().front()) {
            vector<vector<int>> ret1;
            ret1.reserve(intervals.size() + 1);
            ret1.emplace_back(newInterval);
            ret1.insert(end(ret1), cbegin(intervals), cend(intervals));
            return ret1;
        }

        if (intervals.back().back() < newIntervalFront) {
            vector<vector<int>> ret2(cbegin(intervals), cend(intervals));
            ret2.emplace_back(newInterval);
            return ret2;
        }
        int start = -1;
        auto it = cbegin(intervals);
        vector<vector<int>> ret;
        for (; it != cend(intervals); ++it) {
            auto& list = *it;
            if (list.back() < newIntervalFront) {
                ret.emplace_back(list);
            }
            else {
                if (newIntervalBack < list.front()) {
                    ret.emplace_back(newInterval);
                    ret.insert(end(ret), it, cend(intervals));
                    return ret;
                }

                start = min(list.front(), newIntervalFront);
                break;
            }
        }
        int currentBack = max(newIntervalBack, it->back());
        bool added = false;
        for (; it != cend(intervals); ++it) {
            auto& list = *it;
            if (currentBack < list.front()) {
                added = true;
                ret.emplace_back(vector<int>{start, currentBack});
                break;
            }
            else {
                currentBack = max(currentBack, list.back());
            }
        }
        if (!added) {
            ret.emplace_back(vector<int>{start, currentBack});
        }
        ret.insert(end(ret), it, cend(intervals));

        return ret;
    }
};

void test(vector<vector<int>>&& intervals, vector<int>&& newInterval) {
    const auto ret = Solution().insert(intervals, newInterval);

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
    test({ {3,5},{12,15} }, { 6,6 });

    test({ {1,5} }, { 2,3 });

    test({}, { 5,7 });
    test({ {1,3},{6,9} }, { 2,5 });
    test({ {1,2},{3,5},{6,7},{8,10},{12,16} }, { 4,8 });
}

