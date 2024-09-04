// leetcode_Q0874.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int max_distance = 0;
        int x = 0;
        int y = 0;

        enum class direction {
            north,
            east,
            south,
            west,
        };
        direction current_dir = direction::north;

        auto get_inc = [](direction dir)->pair<int,int> {
            switch (dir) {
            case direction::north:
                return {0,1};
            case direction::east:
                return {1,0};
            case direction::south:
                return {0, -1};
            case direction::west:
                return { -1,0 };
            }
            };
        auto turn_left = [](direction dir)->direction {
            if (dir == direction::north) {
                return direction::west;
            }
            else {
                return static_cast<direction>(static_cast<int>(dir) - 1);
            }
            };
        auto turn_right = [](direction dir)->direction {
            if (dir == direction::west) {
                return direction::north;
            }
            else {
                return static_cast<direction>(static_cast<int>(dir) + 1);
            }
            };

        set<pair<int, int>> obstacles_set;
        for (auto&& obstacle : obstacles) {
            obstacles_set.insert({ obstacle[0],obstacle[1] });
        }

        for (auto&& command : commands) {
            if (command < 0) {
                if (command == -2) {
                    current_dir = turn_left(current_dir);
                }
                else {
                    current_dir = turn_right(current_dir);
                }
            }
            else {
                auto [inc_x, inc_y] = get_inc(current_dir);

                for (int i = 0; i < command; i++) {
                    int new_x = x + inc_x;
                    int new_y = y + inc_y;
                    if (obstacles_set.count({ new_x, new_y }) != 0) {
                        break;
                    }
                    x = new_x;
                    y = new_y;

                }

                max_distance = max(max_distance, x * x + y * y);
            }
        }
        return max_distance;
    }
};

void test(vector<int>&& commands, vector<vector<int>>&& obstacles) {
    cout << Solution().robotSim(commands, obstacles) << endl;
}

int main()
{
    test(get_list_int("[4,-1,3]"), get_matrix_int("[]"));
    test(get_list_int("[4,-1,4,-2,4]"), get_matrix_int("[[2,4]]"));
    test(get_list_int("[6,-1,-1,6]"), get_matrix_int("[]"));
    return 0;
}