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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int countPartitions(vector<int>& nums) {
        const auto N = size(nums);
        vector<long long> prefix_sums(N + 1);
        for (int i = 0; i < N; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }

        int total_count = 0;
        for (int i = 1; i < N; i++) {
            const auto left = prefix_sums[i] - prefix_sums[0];
            const auto right = prefix_sums[N] - prefix_sums[i];
            if (abs(left - right) % 2 == 0) {
                total_count++;
            }
        }
        return total_count;
    }
}; 

void test(vector<int>&& nums) {
    cout << Solution().countPartitions(nums) << endl;
}

static void run() {
    test(get_list_int("[10,10,3,7,6]"));
    test(get_list_int("[1,2,2]"));
    test(get_list_int("[2,4,6,8]"));
}
}
namespace problem2 {
class Solution {
public:
    enum class EVTYPE{
        offline,
        message,
    };
    enum class USERS_TYPE {
        all,
        here,
        list,
    };
    struct USERS {
        USERS_TYPE users_type;
        vector<int> users;
    };
    struct EVENT {
        EVTYPE evtype;
        int timestamp;
        USERS users;
    };


    static vector<int> get_ids(const string& idmessage) {
        size_t offset = 0;
        vector<int> ids;
        while (offset < size(idmessage)) {
            auto pos = idmessage.find("id", offset);
            if (pos == string::npos) {
                break;
            }
            auto pos2 = idmessage.find(' ', pos+2);

            const auto idstr = pos2 == string::npos ? idmessage.substr(pos + 2) : idmessage.substr(pos + 2, pos2 - (pos + 2));
            const auto id = stoi(idstr);
            ids.emplace_back(id);
            if (pos2 == string::npos) {
                break;
            }
            offset = pos2 + 1;
        }
        return ids;
    }

    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        const auto N = size(events);
        vector<EVENT> events1;
        events1.reserve(N);
        for (auto&& ev : events) {
            const auto& message = ev[0];
            const auto timestamp = stoi(ev[1]);
            const auto& body = ev[2];
            if (message == "MESSAGE") {
                if (body == "ALL") {
                    events1.emplace_back(EVENT{ EVTYPE::message, timestamp, USERS{USERS_TYPE::all, } });
                }
                else if (body == "HERE") {
                    events1.emplace_back(EVENT{ EVTYPE::message, timestamp, USERS{USERS_TYPE::here, } });
                }
                else {
                    auto ids = get_ids(body);
                    events1.emplace_back(EVENT{ EVTYPE::message, timestamp, USERS{USERS_TYPE::list,ids } });
                }
            }
            else {
                const auto user = stoi(body);
                events1.emplace_back(EVENT{ EVTYPE::offline, timestamp, USERS{USERS_TYPE::list,{user} } });
            }
        }

        sort(begin(events1), end(events1), [](const EVENT& a, const EVENT& b) {
            if (a.timestamp != b.timestamp) {
                return a.timestamp < b.timestamp;
            }
            return static_cast<int>(a.evtype) < static_cast<int>(b.evtype);
            });
        //for (auto&& ev : events1) {
        //    cout << ev.timestamp;
        //    if (ev.evtype == EVTYPE::message) {
        //        cout << ":message:";
        //    }
        //    else {
        //        cout << ":offline:";
        //    }
        //    if (ev.users.users_type == USERS_TYPE::all) {
        //        cout << "all";
        //    }
        //    else if (ev.users.users_type == USERS_TYPE::here) {
        //        cout << "here";
        //    }
        //    else {
        //        for (auto&& id : ev.users.users) {
        //            cout << id << ",";
        //        }
        //    }
        //    cout << endl;
        //}

        struct USER_STATE {
            bool online;
            int online_time;
        };
        vector<USER_STATE> user_states(numberOfUsers, { true, 0, });
        auto compare = [&](const int& a, const int& b) {
            return user_states[a].online_time > user_states[b].online_time;
            };
        priority_queue<int, vector<int>, decltype(compare)> pq(compare);
        vector<int> ans(numberOfUsers);
        int online_users = numberOfUsers;

        for (auto&& [ev, timestamp, users] : events1) {
            while (!pq.empty() && user_states[pq.top()].online_time <= timestamp) {
                auto& u = user_states[pq.top()];
                if (u.online_time <= timestamp && !u.online) {
                    u.online = true;
                    online_users++;
                }
                pq.pop();
            }

            if (ev == EVTYPE::message) {

                if (users.users_type == USERS_TYPE::all) {
                    for (int i = 0; i < numberOfUsers; i++) {
                        ans[i]++;
                    }
                }
                else if (users.users_type == USERS_TYPE::here) {
                    for (int i = 0; i < numberOfUsers; i++) {
                        if (user_states[i].online) {
                            ans[i]++;
                        }
                    }
                }
                else {
                    for (auto&& id : users.users) {
                        ans[id]++;
                    }
                }
            }
            else {
                const auto user = users.users.front();
                user_states[user].online = false;
                user_states[user].online_time = timestamp + 60;
                pq.push(user);
            }
        }
        return ans;
    }
}; 
void test(int numberOfUsers, vector<vector<string>>&& events) {
    output(Solution().countMentions(numberOfUsers, events));
}
static void run() {
    test(10, get_matrix_str(R"([["MESSAGE","73","ALL"],["MESSAGE","86","id7 id1 id5 id6 id7"],["OFFLINE","57","6"],["MESSAGE","48","HERE"],["OFFLINE","4","8"],["OFFLINE","27","1"],["MESSAGE","20","id2 id2 id3 id0 id6"],["OFFLINE","62","0"],["MESSAGE","48","id7 id3 id9 id8 id0 id5 id3 id5 id2 id0"],["MESSAGE","85","HERE"],["MESSAGE","84","ALL"],["MESSAGE","11","HERE"],["MESSAGE","72","HERE"],["OFFLINE","47","5"],["MESSAGE","87","HERE"],["OFFLINE","1","0"],["MESSAGE","71","HERE"],["MESSAGE","13","HERE"]])"));
    //test(3, get_matrix_str(R"([["MESSAGE","2","HERE"],["OFFLINE","2","1"],["OFFLINE","1","0"],["MESSAGE","61","HERE"]])"));
    //test(2, get_matrix_str(R"([["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]])"));
    //test(2, get_matrix_str(R"([["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]])"));
    //test(2, get_matrix_str(R"([["OFFLINE","10","0"],["MESSAGE","12","HERE"]])"));
}
}
namespace problem3 {

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        const auto N = size(nums);
        vector<vector<int>> exists(N + 1, vector<int>(50));

        exists[0][nums[0] - 1]++;
        for (int i = 1; i < N; i++) {
            exists[i][nums[i] - 1]++;
            for (int j = 0; j < 50; j++) {
                exists[i][j] += exists[i - 1][j];
            }
        }

        for (int l = 0; l < N; l++) {
            for (int r = l + 1; r < N; r++) {
                int outer_k_count_left = exists[l][k - 1] - exists[0][k - 1];
                int outer_k_count_right = exists[N][k - 1] - exists[r][k - 1];
                int max_same_count = 0;
                for (int j = 0; j < 50; j++) {
                    exists[i][j] += exists[i - 1][j];
                }
            }
        }


        return first_k + range_max_value;
    }
};
void test(vector<int>&& nums, int k) {
    cout << Solution().maxFrequency(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4,5,6]"), 1);
    test(get_list_int("[10,2,3,4,5,5,4,3,2,2]"), 1);
}
}
namespace problem4 {
    static void run() {
    }
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}