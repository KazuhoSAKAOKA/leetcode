#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

using POINT = pair<int, int>;
static const map<char, POINT> dir_map{
    { 'L', {0,-1} },
    { 'R', {0,1} },
    { 'U', {-1,0} },
    { 'D', {1,0} },
};
POINT operator+(const POINT& p1, const POINT& p2) {
    return POINT{ p1.first + p2.first, p1.second + p2.second };
}

class SnakeGame {
private:

    const POINT size_;
    queue<POINT> foods_;

    POINT cur_head_;
    vector<vector<bool>> grid_;
    queue<POINT> snakes_;
    POINT cur_food_;

public:
    SnakeGame(int width, int height, vector<vector<int>>& food) 
        :size_({ height, width }), cur_head_({ 0,0 }), grid_(height, vector<bool>(width, false)), cur_food_({ food[0][0] ,food[0][1] }) {
        grid_[0][0] = true;
        snakes_.push({ 0,0 });
        for (int i = 1; i < size(food); i++) {
            foods_.push({ food[i][0] ,food[i][1] });
        }
    }
        
    int move(string direction) {
        const auto next_pos = cur_head_ + dir_map.at(direction[0]);
        if (next_pos.first < 0 || size_.first <= next_pos.first || next_pos.second < 0 || size_.second <= next_pos.second) {
            return -1;
        }

        snakes_.push(next_pos);
        if (next_pos == cur_food_) {
            if (foods_.empty()) {
                cur_food_ = { -1,-1 };
            }
            else {
                cur_food_ = foods_.front();
                foods_.pop();
            }
        }
        else {
            const auto tail = snakes_.front();
            grid_[tail.first][tail.second] = false;
            snakes_.pop();
        }
        if (grid_[next_pos.first][next_pos.second]) {
            return -1;
        }
        grid_[next_pos.first][next_pos.second] = true;
        cur_head_ = next_pos;
        return static_cast<int>(size(snakes_)) - 1;
    }
};

void test_run(int width, int height, vector<vector<int>>&& foods, vector<string>&& operates) {
    SnakeGame sg(width, height, foods);
    vector<int> ans;
    for (auto&& ope : operates) {
        ans.emplace_back(sg.move(ope));
    }
    output(ans);
}

int main() {
    test_run(3, 3, get_matrix_int("[[2,0],[0,0],[0,2],[2,2]]"), get_list_str(R"(["D","D","R","U","U","L","D","R","R","U","L","D"])"));
    test_run(3, 3, get_matrix_int("[[1,0],[0,0],[0,2],[2,2]]"), get_list_str(R"(["D","U"])"));
    return 0;
}