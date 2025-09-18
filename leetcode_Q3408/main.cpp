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
class TaskManager {
    map<int, map<int, int, greater<int>>, greater<int>> priority_map;
    map<int, pair<int, int>> task_map;

    void erase_priority_map(int task_id, int priority) {
        auto it = priority_map.find(priority);
        auto it2 = it->second.find(task_id);
        if (it2 != cend(it->second)) {
            it->second.erase(task_id);
        }
        if (it->second.empty()) {
            priority_map.erase(it);
        }
    }

    void erase_task_map(int task_id) {
        auto it = task_map.find(task_id);
        if (it != cend(task_map)) {
            task_map.erase(it);
        }
    }
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto&& task : tasks) {
            const auto& userid = task[0];
            const auto& taskid = task[1];
            const auto& priority = task[2];
            add(userid, taskid, priority);
        }
    }

    void add(int userId, int taskId, int priority) {
        auto it_p = priority_map.find(priority);
        if (it_p == cend(priority_map)) {
            priority_map[priority].insert({ taskId, userId });
        }
        else {
            auto& mp = it_p->second;
            auto it_t = mp.find(taskId);
            if (it_t != cend(mp)) {
                throw exception();
            }
            mp.insert({ taskId, userId });
        }

        const auto [a, b] = task_map.insert({ taskId, {userId, priority} });
        if (!b) {
            throw exception();
        }
    }

    void edit(int taskId, int newPriority) {
        const auto [userid, oldpriority] = task_map[taskId];
        if (newPriority == oldpriority) { return; }
        erase_priority_map(taskId, oldpriority);
        priority_map[newPriority].insert({ taskId,userid });
        task_map[taskId].second = newPriority;
    }

    void rmv(int taskId) {
        auto ittask = task_map.find(taskId);
        if (ittask != cend(task_map)) {
            erase_priority_map(taskId, ittask->second.second);
            erase_task_map(taskId);
        }
    }

    int execTop() {
        if (priority_map.empty()) {
            return -1;
        }
        auto it = begin(priority_map);
        const auto priority = it->first;
        auto& inner_map = it->second;
        auto it2 = begin(inner_map);
        const auto target_taskid = it2->first;
        const auto target_userid = it2->second;
        erase_priority_map(target_taskid, priority);
        erase_task_map(target_taskid);
        return target_userid;
    }
};
static void test(vector<vector<int>>&& a) {
    TaskManager tm(a);
    tm.rmv(6);
    cout << tm.execTop() << endl;
    tm.add(8, 20, 29);
    tm.edit(20, 49);
    cout << tm.execTop() << endl;
    tm.edit(1, 45);
    tm.add(2, 24, 40);
    cout << tm.execTop() << endl;
    tm.add(8, 5, 33);
    cout << tm.execTop() << endl;
    tm.rmv(24);
    cout << tm.execTop() << endl;
}
static void test2() {
    auto temp = get_matrix_int("[[9,1,24]]");
    TaskManager tm(temp);
    //tm.rmv(6);
    //cout << tm.execTop() << endl;
    tm.add(8, 20, 29);
    tm.edit(20, 49);
    cout << tm.execTop() << endl;
    tm.edit(1, 45);
    tm.add(2, 24, 40);
    cout << tm.execTop() << endl;
    tm.add(8, 5, 33);
    cout << tm.execTop() << endl;
    tm.rmv(24);
    cout << tm.execTop() << endl;
}


int main() {
    test2();
	return 0;
}