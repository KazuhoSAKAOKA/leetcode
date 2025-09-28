#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        map<string, map<string, set<int>>> info_map;
        map<int, set<string>> ts_web_map;
        for (int i = 0; i < size(username); i++) {
            const auto& un = username[i];
            const auto& ts = timestamp[i];
            const auto& ws = website[i];
            info_map[un][ws].insert(ts);
            ts_web_map[ts].insert(ws);
        }

        auto cal_score = [&](const string& a, const string& b, const string& c)->int {
            int count = 0;
            for (auto&& [_, inner_map] : info_map) {
                const auto& it1 = inner_map.find(a);
                const auto& it2 = inner_map.find(b);
                const auto& it3 = inner_map.find(c);

                if (it1 != cend(inner_map) && it2 != cend(inner_map)&& it3 != cend(inner_map)) {
                    const auto& ts1 = it1->second;
                    const auto& ts2 = it2->second;
                    const auto& ts3 = it3->second;

                    const auto time1 = *cbegin(ts1);
                    const auto time_it2 = ts2.upper_bound(time1);
                    if (time_it2 != cend(ts2)) {
                        const auto time2 = *time_it2;
                        const auto time_it3 = ts3.upper_bound(time2);
                        if (time_it3 != cend(ts3)) {
                            count++;
                        }
                    }
                }
            }
            return count;
            };

        vector<string> ans;
        int max_score = 0;

        for (auto it1 = cbegin(ts_web_map); it1 != cend(ts_web_map); ++it1) {
            for (auto&& ws1 : it1->second) {
                for (auto it2 = next(it1); it2 != cend(ts_web_map); ++it2) {
                    for (auto&& ws2 : it2->second) {
                        for (auto it3 = next(it2); it3 != cend(ts_web_map); ++it3) {
                            for (auto&& ws3 : it3->second) {
                                const auto score = cal_score(ws1, ws2, ws3);
                                if (max_score < score) {
                                    max_score = score;
                                    ans = { ws1, ws2, ws3, };
                                }
                                else if (max_score == score) {
                                    vector<string> temp{ ws1, ws2, ws3, };
                                    if (temp < ans) {
                                        ans = temp;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return ans;
    }
};
static void test(vector<string>&& username, vector<int>&& timestamp, vector<string>&& website) {
    output(Solution().mostVisitedPattern(username, timestamp, website));
}

int main() {
    test(get_list_str(R"(["ua","ua","ua","ub","ub","ub"])"), get_list_int("[1,2,3,4,5,6]"), get_list_str(R"(["a","b","c","a","b","a"])"));
    test(get_list_str(R"(["joe","joe","joe","james","james","james","james","mary","mary","mary"])"), get_list_int("[1,2,3,4,5,6,7,8,9,10]"), get_list_str(R"(["home","about","career","home","cart","maps","home","home","about","career"])"));
    test(get_list_str(R"(["ua","ua","ua","ub","ub","ub"])"), get_list_int("[1,2,3,4,5,6]"), get_list_str(R"(["a","b","a","a","b","c"])"));
    return 0;
}