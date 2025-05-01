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

    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }


    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int total_count = 0;
        sort(begin(tasks), end(tasks));
        //multiset<int, greater<int>> tasks_set(cbegin(tasks), cend(tasks));
        sort(begin(workers), end(workers), greater<int>());
        const auto n = size(tasks);
        const auto m = size(workers);

        auto check = [&](int count)->bool {
            multiset<int> workers_set(cbegin(workers), next(cbegin(workers), count));
            int remain_pills(pills);
            for (int task_index = count - 1; task_index >= 0; task_index--) {
                const auto cur_task = tasks[task_index];
                auto it = workers_set.lower_bound(cur_task);
                if (it != cend(workers_set)) {
                    workers_set.erase(it);
                    continue;
                }
                if (remain_pills == 0) { return false; }
                it = workers_set.lower_bound(cur_task - strength);
                if (it != cend(workers_set)) {
                    workers_set.erase(it);
                    remain_pills--;
                    continue;
                }
                return false;
            }
            return true;
            };
        return binary_search_meguru<int>(0, min(n, m) + 1, check);
    }

/*        for (auto&& worker : workers) {
            auto it = tasks_set.lower_bound(worker);
            if (it != cend(tasks_set)) {
                tasks_set.erase(it);
                total_count++;
            }
            else {
                if (0 < remain_pills) {
                    it = tasks_set.lower_bound(worker + strength);
                    if (it != cend(tasks_set)) {
                        tasks_set.erase(it);
                        total_count++;
                        remain_pills--;
                    }
                }
            }
        }
*/
};

void test(vector<int>&& tasks, vector<int>&& workers, int pills, int strength) {
    cout << Solution().maxTaskAssign(tasks, workers, pills, strength) << endl;
}
int main() {
    test(get_list_int("[5,9,8,5,9]"), get_list_int("[1,6,4,2,6]"), 1, 5);
    test(get_list_int("[3,2,1]"), get_list_int("0,3,3]"), 1, 1);
    test(get_list_int("[10,15,30]"), get_list_int("[0,10,10,10,10]"), 3, 10);
    test(get_list_int("[1,2,3,4,5]"), get_list_int("[4,4,4,4]"), 1, 5);
    test(get_list_int("[5,4]"), get_list_int("[0,0,0]"), 1, 5);
    return 0;
}