#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


class LogSystem {
    map<string, vector<int>> data_;
public:
    LogSystem() {

    }

    void put(int id, string timestamp) {
        data_[timestamp].push_back(id);
    }

    static const string convert(const string& target, const string& granularity, bool is_max_value) {
        const string min_value_year = "0000";
        const string max_value_year = "9999";
        const string min_value_month = "01";
        const string max_value_month = "12";
        const string min_value_day = "01";
        const string max_value_day = "31";
        const string min_value_hour = "00";
        const string max_value_hour = "23";
        const string min_value_min_sec = "00";
        const string max_value_min_sec = "59";
        static const unordered_map<string, tuple<int, string, string>> tag_map{
            {"Year",{0,min_value_year, max_value_year }},
            {"Month",{1,min_value_month,max_value_month}},
            {"Day",{2,min_value_day,max_value_day}},
            {"Hour",{3,min_value_hour,max_value_hour}},
            {"Minute",{4,min_value_min_sec,max_value_min_sec}},
            {"Second",{5,min_value_min_sec,max_value_min_sec}},
        };
        static const vector<string> orders{ "Year","Month", "Day","Hour","Minute","Second", };
        auto it1 = tag_map.find(granularity);
        if (it1 == cend(tag_map)) { throw runtime_error(""); }
        string work;
        size_t offset = 0;
        for (int i = 0; i <= get<0>(it1->second); i++) {
            if (!work.empty()) {
                work += ":";
            }
            const auto pos = target.find(':', offset);
            work += target.substr(offset, pos - offset);
            offset = pos + 1;
        }
        for (auto it2 = next(cbegin(orders), get<0>(it1->second) + 1); it2 != cend(orders); ++it2){
            if (!work.empty()) {
                work += ":";
            }
            auto it3 = tag_map.find(*it2);
            if (it3 == cend(tag_map)) { throw runtime_error(""); }
            if (is_max_value) {
                work += get<2>(it3->second);
            }
            else {
                work += get<1>(it3->second);
            }
        }
        return work;
    }

    vector<int> retrieve(string start, string end, string granularity) {
        vector<int> ids;

        const auto s1 = convert(start, granularity, false);
        const auto e1 = convert(end, granularity, true);

        auto it = data_.lower_bound(s1);
        while (it != cend(data_) && it->first <= e1) {
            ids.insert(std::end(ids), cbegin(it->second), cend(it->second));
            ++it;
        }

        return ids;
    }
};
//[[],[],[],[]]
static void test2() {
    LogSystem ls;
    ls.put(1, "2017:01:01:23:59:59");
    ls.put(2, "2017:01:02:23:59:59");
    output(ls.retrieve("2017:01:01:23:59:59", "2017:01:02:23:59:59", "Month"));
}

int main()
{
    test2();
    return 0;
}