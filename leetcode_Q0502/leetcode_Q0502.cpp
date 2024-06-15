// leetcode_Q0502.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static int rec(int k, int w, const vector<int>& profits, const vector<int>& capital, vector<bool>& used_projects) {
        if (k == 0) {
            return w;
        }
        int max_value = 0;
        for (int i = 0; i < profits.size(); i++) {
            if (!used_projects[i]) {
                if (capital[i] <= w) {
                    used_projects[i] = true;
                    const auto value = rec(k - 1, w + profits[i], profits, capital, used_projects);
                    max_value = max(max_value, value);
                    used_projects[i] = false;
                }
            }
        }
        return max_value;
    }

    static int tle(int k, int w, const vector<int>& profits, const vector<int>& capital) {
        vector<bool> used_projects(profits.size(), false);
        return rec(k, w, profits, capital, used_projects);
    }

    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        using P = pair<int, int>;
        vector<P> pc(profits.size(), P(0, 0));
        for (int i = 0; i < profits.size(); i++) {
            pc[i] = P(capital[i], profits[i]);
        }
        sort(begin(pc), end(pc), [](const P& a, const P& b) {
            if (a.first != b.first) {
                return a.first < b.first;
                }
            return a.second < b.second;
            });
        priority_queue<int> profits_pq;
        
        int current_capital = w;
        int count = 0;
        int pc_index = 0;

        while (count < k) {
            while (pc_index < pc.size() && pc[pc_index].first <= current_capital) {
                profits_pq.push(pc[pc_index].second);
                pc_index++;
            }
            if (profits_pq.empty()) {
                break;
            }
            const auto top = profits_pq.top();
            profits_pq.pop();
            current_capital += top;
            count++;
        }
        return current_capital;
    }
};

void test(int k, int w, vector<int>&& profits, vector<int>&& capital) {
    cout << Solution().findMaximizedCapital(k, w, profits, capital) << endl;
}
int main()
{
    test(2, 0, get_list_int("[1,2,3]"), get_list_int("[0,1,1]"));
    test(3, 0, get_list_int("[1,2,3]"), get_list_int("[0,1,2]"));
}