// leetcode_Q0539.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static int convert(const string& timestr) {
        const auto hour = timestr.substr(0, 2);
        const auto minute = timestr.substr(3, 2);
        const auto minute_val = stoi(hour) * 60 + stoi(minute);
        return minute_val;
    }
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutes;
        minutes.reserve(size(timePoints));
        for (auto&& time : timePoints) {
            minutes.emplace_back(convert(time));
        }
        sort(begin(minutes), end(minutes));
        int min_difference = INT_MAX;
        for (int i = 0; i < size(minutes) - 1; i++) {
            min_difference = min(min_difference, minutes[i + 1] - minutes[i]);
        }
        constexpr int TIME_MAX = 24 * 60;
        min_difference = min(min_difference, TIME_MAX - minutes.back() + minutes.front());
        return min_difference;
    }
};

void test(vector<string>&& timePoints) {
    cout << Solution().findMinDifference(timePoints) << endl;
}
int main()
{
    test(get_list_str(R"(["23:59","00:00"])"));
    test(get_list_str(R"(["00:00","23:59","00:00"])"));
    return 0;
}