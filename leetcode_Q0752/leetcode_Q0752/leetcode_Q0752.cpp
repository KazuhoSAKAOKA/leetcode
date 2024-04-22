// leetcode_Q0752.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:

    static string rotate(const string& current, int column, bool inc) {
        string s;
        for (int i = 0; i < 4; i++) {
            if (i == column) {
                if (inc && current[i] == '9') {
                    s += '0';
                }
                else if (!inc && current[i] == '0') {
                    s += '9';
                }
                else {
                    if (inc) {
                        s += current[i] + static_cast<char>(1);
                    }
                    else {
                        s += current[i] - static_cast<char>(1);
                    }
                }
            }
            else {
                s += current[i];
            }
        }
        return s;
    }

    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadend_sets(cbegin(deadends), cend(deadends));
        string start = "0000";
        if (deadend_sets.find(start) != cend(deadend_sets)) { return -1; }
        if (target == start) { return 0; }

        unordered_set<string> checked{ start };
        vector<bool> directions{ false,true, };
        using DS = pair<string, int>;
        queue<DS> s_queue;
        s_queue.push({ start, 0 });
        while (!s_queue.empty()) {
            const auto [current, step] = s_queue.front();
            s_queue.pop();
            for (int i = 0; i < 4; i++) {
                for (auto&& direction : directions) {
                    const auto new_value = rotate(current, i, direction);
                    if (new_value == target) {
                        return step + 1;
                    }
                    if (checked.find(new_value) == cend(checked) && deadend_sets.find(new_value) == cend(deadend_sets)) {
                        checked.insert(new_value);
                        s_queue.push({ new_value, step + 1 });
                    }
                }
            }
        }

        return -1;
    }
};

void test(vector<string>&& deadends, string&& target) {
    cout << Solution().openLock(deadends, target) << endl;
}


int main()
{
    test({ "0201","0101","0102","1212","2002" }, "0202");
    test({ "8888" }, "0009");
    test({ "8887","8889","8878","8898","8788","8988","7888","9888" }, "8888");
}