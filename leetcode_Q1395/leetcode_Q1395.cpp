// leetcode_Q1395.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;



class Solution {
public:


    struct memo_key_t {
        int index;
        int team_size;
        int direction;
        int last_value;
        bool operator < (const memo_key_t& other) const {
            if (index != other.index) {
                return index < other.index;
            }
            if (team_size != other.team_size) {
                return team_size < other.team_size;
            }
            if (direction != other.direction) {
                return direction < other.direction;
            }
            return last_value < other.last_value;
        }
    };

    static bool allow_add(const memo_key_t& state, int value) {
        if (state.team_size <= 1) { return true; }
        if (state.direction > 0 && state.last_value < value) {
            return true;
        }
        if (state.direction < 0 && state.last_value > value) {
            return true;
        }
        return false;
    }

    using memo_t = vector<vector<vector<unordered_map<int, int>>>>;

    static int rec(const vector<int>& rating, int index, const memo_key_t& state, memo_t& memo) {
        if (state.team_size == 3) {
            return 1;
        }
        if (rating.size() == index) {
            return 0;
        }
        auto& inner_map = memo[state.index][state.team_size][state.direction + 1];
        const auto it = inner_map.find(state.last_value);
        if (it != cend(inner_map)) {
            return it->second;
        }
        int count = rec(rating, index + 1, { index + 1, state.team_size, state.direction, state.last_value }, memo);
        if (allow_add(state, rating[index])) {
            int direction = state.direction;
            if (state.team_size == 1) {
                if (state.last_value < rating[index]) {
                    direction = 1;
                }
                else {
                    direction = -1;
                }
            }
            count += rec(rating, index + 1, { index + 1, state.team_size + 1, direction, rating[index] }, memo);
        }
        inner_map[state.last_value] = count;
        return count;
    }

    static int tle(const vector<int>& rating) {
        memo_t memo(rating.size(), vector<vector<unordered_map<int, int>>>(3, vector<unordered_map<int, int>>(3)));
        const auto ans = rec(rating, 0, { 0, 0, 0, 0 }, memo);
        return ans;
    }

    static int rec2(const vector<int>& rating, int index, int team_index, vector<vector<int>>& memo, const function<bool(int,int)>& pred) {
        if (team_index == 2) {
            return 1;
        }
        if (rating.size() == index) {
            return 0;
        }
        if (memo[index][team_index] != -1) {
            return memo[index][team_index];
        }

        int count = 0;
        for (int i = index + 1; i < rating.size(); i++) {
            if (pred(rating[index], rating[i])) {
                count += rec2(rating, i, team_index + 1, memo, pred);
            }
        }
        memo[index][team_index] = count;
        return count;
    }


    int numTeams(vector<int>& rating) {
        vector<vector<int>> accmemo(rating.size(), vector<int>(3, -1));
        vector<vector<int>> decmemo(rating.size(), vector<int>(3, -1));
        int count = 0;
        for (int i = 0; i < rating.size(); i++) {
            count += rec2(rating, i, 0, accmemo, [](auto a, auto b) { return a < b; });
            count += rec2(rating, i, 0, decmemo, [](auto a, auto b) { return a > b; });
        }
        return count;
    }
};

void test(vector<int>&& rating) {
    cout << Solution().numTeams(rating) << endl;
}


int main()
{
    test(get_list_int("[2,5,3,4,1]"));
    test(get_list_int("[2,1,3]"));
    test(get_list_int("[1,2,3,4]"));
    return 0;
}