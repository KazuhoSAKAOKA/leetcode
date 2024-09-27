// leetcode_Q0731.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class MyCalendarTwo {
public:
    MyCalendarTwo() {

    }

    bool book(int start, int end) {
        if (schedule_map_.empty()) {
            schedule_map_.insert({ start, end });
            return true;
        }
        auto begin_it = schedule_map_.lower_bound(start);
        if (begin_it != cbegin(schedule_map_)) {
            begin_it = prev(begin_it);
        }
        auto it = begin_it;

        vector<pair<int, int>> single_ranges;
        vector<pair<int, int>> booking_ranges;
        int before = start;
        while (it != cend(schedule_map_)) {
            const auto cur_start = it->first;
            const auto cur_end = it->second;
            if (end < cur_start) {
                break;
            }
            const auto range_start = max(start, cur_start);
            const auto range_end = min(end, cur_end);
            if (range_start < range_end) {
                booking_ranges.emplace_back(make_pair(range_start, range_end));
                if (before < range_start) {
                    single_ranges.emplace_back(make_pair(before, range_start));
                }
                before = range_end;
            }
            ++it;
        }
        if (before < end) {
            single_ranges.emplace_back(make_pair(before, end));
        }

        for (auto&& [booking_start, booking_end] : booking_ranges) {
            const auto it = booking_map_.lower_bound(start);
            if (it != cend(booking_map_)) {
                if (it->first < end) {
                    return false;
                }
            }
            if (it != cbegin(booking_map_)) {
                const auto prev_it = prev(it);
                if (start < prev_it->second) {
                    return false;
                }
            }
        }
        for (auto&& p : single_ranges) {
            schedule_map_.insert(p);
        }
        for (auto&& p : booking_ranges) {
            booking_map_.insert(p);
        }
        return true;
    }

private:
    map<int, int> schedule_map_;
    map<int, int> booking_map_;
};

void test(vector<pair<int, int>>&& args) {
    MyCalendarTwo target;
    for (auto&& [start, end] : args) {
        cout << target.book(start, end) << endl;
    }
}


int main()
{
    test({ {10, 20} ,{50, 60},{10, 40},{5, 15},{5, 10},{25, 55}, });
    //test({ {10,20},{15,25},{20,30}, });
    return 0;
}