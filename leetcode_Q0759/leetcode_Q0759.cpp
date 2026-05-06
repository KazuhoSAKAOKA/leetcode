#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        set<int> entries;
        for (auto&& employee_schedule : schedule) {
            for (auto&& interval : employee_schedule) {
                entries.insert(interval.start);
                entries.insert(interval.end);
            }
        }
        const auto n = size(entries);
        vector<int> events;
        events.reserve(n);
        map<int, size_t> event_index_map;
        for (auto&& value : entries) {
            event_index_map.insert({ value, size(events) });
            events.push_back(value);
        }

        vector<int> diffs(n);
        for (auto&& employee_schedule : schedule) {
            for (auto&& interval : employee_schedule) {
                diffs[event_index_map[interval.start]]++;
                diffs[event_index_map[interval.end]]--;
            }
        }

        vector<Interval> ans;

        int current_count = 0;
        int before_start = INT_MIN;
        for (size_t i = 0; i < n; i++) {
            const auto new_count = current_count + diffs[i];
            if (new_count == 0 && current_count != 0) {
                before_start = events[i];
            }
            else if (new_count != 0 && current_count == 0) {
                if (before_start != INT_MIN) {
                    ans.emplace_back(Interval(before_start, events[i]));
                }
                before_start = INT_MIN;
            }
            current_count = new_count;
        }
        return ans;
    }
};


int main() {


    return 0;
}