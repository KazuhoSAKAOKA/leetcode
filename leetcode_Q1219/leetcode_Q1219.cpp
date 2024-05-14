// leetcode_Q1219.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <chrono>
using namespace std;

class Solution {
public:

    using point = pair<int, int>;
    static point add_point(const point& a, const point& b) {
        return point(a.first + b.first, a.second + b.second);
    }

    static int get_max_gold_rec(const vector<vector<int>>& grid, const point& current, set<point>& routes) {
        if (grid[current.first][current.second] == 0) {
            return 0;
        }

        static const point directions[] = {
            point(-1,0),
            point(1,0),
            point(0, -1),
            point(0, 1),
        };

        int max_gold = 0;
        routes.insert(current);
        for (auto&& d : directions) {
            const auto pos = add_point(current, d);
            if (pos.first < 0 || grid.size() <= pos.first || pos.second < 0 || grid.front().size() <= pos.second) {
                continue;
            }
            if (routes.find(pos) != cend(routes)) {
                continue;
            }
            if (grid[pos.first][pos.second] == 0) {
                continue;
            }
            max_gold = max(max_gold, get_max_gold_rec(grid, pos, routes));
        }
        routes.erase(current);
        return max_gold + grid[current.first][current.second];
    }

    int brute_force(const vector<vector<int>>& grid) {
        int max_gold = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.front().size(); j++) {
                set<point> routes;
                max_gold = max(max_gold, get_max_gold_rec(grid, point(i, j), routes));
            }
        }
        return max_gold;
    }



    int getMaximumGold(vector<vector<int>>& grid) {
        return brute_force(grid);
    }


};

void test(vector<vector<int>>&& grid) {
    cout << Solution().getMaximumGold(grid) << endl;
}

int main()
{
    test({ {1,0,7,0,0,0},{2,0,6,0,1,0},{3,5,6,7,4,2},{4,3,1,0,2,0},{3,0,5,0,20,0} });
    test({ {0,6,0,},{5,8,7,},{0,9,0,}, });
    test({ {1,0,7,},{2,0,6,},{3,4,5,}, {0,3,0,},{9,0,20,}, });
}