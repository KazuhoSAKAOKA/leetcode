// leetcode_Q2061.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>

#include "./../utility/leetcode_testcase_helper.h"


using namespace std;

class Solution {
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        const auto H = room.size();
        const auto W = room.front().size();
        int ans = 0;

        using position = pair<int, int>;
        using state = pair<position, int>;
        
        state current = { {0,0},0 };
        set<state> exists;
        set<position> cleaned{ {0,0} };

        auto next_dir = [](int dir) {
            return dir == 3 ? 0 : dir + 1;
            };
        static const vector<position> moves{ {0,1,},{1,0},{0,-1},{-1,0}, };

        auto get_next = [&](const state& s) {
            const auto next_y = s.first.first + moves[s.second].first;
            const auto next_x = s.first.second + moves[s.second].second;
            if (next_y < 0 || H <= next_y || next_x < 0 || W <= next_x || room[next_y][next_x] != 0) {
                return state{ s.first, next_dir(s.second) };
            }
            return state{ {next_y, next_x}, s.second };
            };

        for (;;) {
            current = get_next(current);
            if (exists.find(current) != cend(exists)) {
                break;
            }
            exists.insert(current);
            cleaned.insert(current.first);
        }

        return static_cast<int>(cleaned.size());
    }
};

void test(vector<vector<int>>&& room) {
    cout << Solution().numberOfCleanRooms(room) << endl;
}

const string example_1 = "[[0,0,0],[1,1,0],[0,0,0]]";
const string example_2 = "[[0,1,0],[1,0,0],[0,0,0]]";
const string example_3 = "[[0,0,0],[0,0,0],[0,0,0]]";

int main()
{
    test(get_matrix_int(example_1));
    test(get_matrix_int(example_2));
    test(get_matrix_int(example_3));
}