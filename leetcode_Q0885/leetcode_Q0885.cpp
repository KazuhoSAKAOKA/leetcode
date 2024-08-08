// leetcode_Q0885.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    enum class direction {
        right,
        down,
        left,
        up,
    };

    static direction get_next_dir(direction dir) {
        switch (dir) {
        case direction::right:
            return direction::down;
        case direction::down:
            return direction::left;
        case direction::left:
            return direction::up;
        case direction::up:
            return direction::right;
        }
        cerr << "invalid dir" << static_cast<int>(dir) << endl;
        throw exception();
    }

    static string to_string(direction dir) {
        switch (dir) {
        case direction::right:
            return "right";
        case direction::down:
            return "down";
        case direction::left:
            return "left";
        case direction::up:
            return "up";
        }
    }


    struct point {
        int row;
        int col;
        point operator+(const point& other) const {
            return point{ row + other.row, col + other.col };
        }
        point next(const direction& dir) const {
            switch (dir) {
            case direction::right:
                return point{ row, col + 1 };
            case direction::down:
                return point{ row + 1, col };
            case direction::left:
                return point{ row, col - 1 };
            case direction::up:
                return point{ row - 1, col };
            }
            cerr << "invalid dir" << static_cast<int>(dir) << endl;
            throw exception();
        }
    };

    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> ans;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        ans.reserve(rows * cols);
        if (rows == 1 && cols == 1) {
            ans.push_back({rStart, cStart});
            return ans;
        }
        point current{ rStart, cStart };

        direction current_dir = direction::right;

        auto in_range = [&](const point& p) {
            if (p.row < 0 || p.col < 0 || rows <= p.row || cols <= p.col) {
                return false;
            }
            return true;
            };

        auto move_next = [&](const point& p, direction dir)->pair<point, direction> {
            const auto next = p.next(dir);
            const auto next_dir = get_next_dir(dir);
            const auto next_dir_next = next.next(next_dir);
            if (!in_range(next_dir_next) || !visited[next_dir_next.row][next_dir_next.col]) {
                return {next, next_dir};
            }
            return { next,dir };
        };

        for(;;) {
            //cout << "pos{" << current.row << "," << current.col << "} next dir{" << to_string(current_dir) << "}" << endl;
            if (in_range(current)) {
                visited[current.row][current.col] = true;
                ans.push_back({ current.row, current.col });
                if (rows * cols == ans.size()) {
                    break;
                }
            }
            const auto [c, d] = move_next(current, current_dir);
            current = c;
            current_dir = d;
        }
        return ans;
    }
};

void test(int rows, int cols, int rStart, int cStart) {
    const auto ans = Solution().spiralMatrixIII(rows, cols, rStart, cStart);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << "\n";
    }
    cout << endl;
}
int main()
{
    test(1, 4, 0, 0);
    test(5, 6, 1, 4);
}