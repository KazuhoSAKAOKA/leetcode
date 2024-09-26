// leetcode_Q0729.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class MyCalendar {
public:
    MyCalendar() {
    }

    bool book(int start, int end) {
        if (!schedule_map_.empty()) {
            const auto it = schedule_map_.lower_bound(start);
            if (it != cend(schedule_map_)) {
                if (it->first < end) {
                    return false;
                }
            }
            if (it != cbegin(schedule_map_)) {
                const auto prev_it = prev(it);
                if (start < prev_it->second) {
                    return false;
                }
            }
        }
        schedule_map_.insert({ start, end });
        return true;
    }
private:
    map<int, int> schedule_map_;
};

void test(vector<pair<int,int>>&& args) {
    MyCalendar target;
    for (auto&& [start, end] : args) {
        cout << target.book(start, end) << endl;
    }
}


int main()
{
    test({ {10,20},{10,11},{9, 11},{19,20}, });
    test({ {10,20},{15,25},{20,30}, });
    return 0;
}