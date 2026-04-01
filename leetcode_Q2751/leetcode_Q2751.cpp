// leetcode_Q2751.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static vector<int> past_survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        map<int, size_t> left_dirs;
        map<int, size_t> right_dirs;

        for (size_t i = 0; i < positions.size(); i++) {
            if (directions[i] == 'L') {
                left_dirs.insert({positions[i], i});
            }
            else {
                right_dirs.insert({ positions[i], i });
            }
        }

        for (auto it = rbegin(right_dirs); it != rend(right_dirs); ++it) {
            const auto [first_pos, index] = *it;
            auto other_begin_it = left_dirs.upper_bound(first_pos);
            if (healths[index] == 0) {
                continue;
            }
            for (auto other_it = other_begin_it; other_it != end(left_dirs); ++other_it) {
                const auto [_, other_index] = *other_it;
                if (healths[other_index] == 0) {
                    continue;
                }
                if (healths[index] == healths[other_index]) {
                    healths[index] = 0;
                    healths[other_index] = 0;
                }
                else if (healths[index] < healths[other_index]) {
                    healths[index] = 0;
                    healths[other_index]--;
                }
                else {
                    healths[index]--;
                    healths[other_index] = 0;
                }

                if (healths[index] == 0) {
                    break;
                }
            }
        }

        vector<int> ans;
        ans.reserve(healths.size());
        for (auto&& health : healths) {
            if (health > 0) {
                ans.emplace_back(health);
            }
        }
        return ans;
    }

    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        const auto n = size(positions);
        vector<size_t> indexes(n);
        for (size_t i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](size_t a, size_t b) { return positions[a] < positions[b]; });

        vector<size_t> stk;
        for (auto&& index : indexes) {
            stk.push_back(index);
            while (size(stk) > 1 && directions[stk[size(stk) - 2]] == 'R' && directions[stk[size(stk) - 1]] == 'L') {
                if (healths[stk[size(stk) - 2]] == healths[stk[size(stk) - 1]]) {
                    stk.pop_back();
                    stk.pop_back();
                }
                else if (healths[stk[size(stk) - 2]] > healths[stk[size(stk) - 1]]) {
                    stk.pop_back();
                    healths[stk[size(stk) - 1]]--;
                }
                else {
                    stk[size(stk) - 2] = stk[size(stk) - 1];
                    stk.pop_back();
                    healths[stk[size(stk) - 1]]--;
                }
            }
        }
        sort(begin(stk), end(stk));
        vector<int> ans(size(stk));
        for (size_t i = 0; i < size(stk); i++) {
            ans[i] = healths[stk[i]];
        }
        return ans;
    }
};

void test(vector<int>&& positions, vector<int>&& healths, string&& directions) {
    const auto ans = Solution().survivedRobotsHealths(positions, healths, directions);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
int main()
{
    test(get_list_int("[5,4,3,2,1]"), get_list_int("[2,17,9,15,10]"), "RRRRR");
    test(get_list_int("[3,5,2,6]"), get_list_int("[10,10,15,12]"), "RLRL");
    test(get_list_int("[1,2,5,6]"), get_list_int("[10,10,11,11]"), "RLRL");
    return 0;
}