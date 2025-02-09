// leetcode_Q0407.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int wa(const vector<vector<int>>& heightMap) {
        const auto H = size(heightMap);
        const auto W = size(heightMap.front());
        vector<vector<int>> water_grid_x(H, vector<int>(W, 0));
        vector<vector<int>> water_grid_y(H, vector<int>(W, 0));


        for (int y = 0; y < H; y++) {
            stack<int> height_stack;
            height_stack.push(-1);

            for (int x = 0; x < W; x++) {
                while (height_stack.top() != -1 && heightMap[y][height_stack.top()] < heightMap[y][x]) {
                    const auto water_height = min(heightMap[y][height_stack.top()], heightMap[y][x]);
                    for (int index = height_stack.top() + 1; index <= x - 1; index++) {
                        water_grid_x[y][index] = water_height;
                    }
                    height_stack.pop();
                }
                if (height_stack.top() != -1) {
                    const auto start = height_stack.top();
                    const auto water_height = min(heightMap[y][start], heightMap[y][x]);
                    for (int index = start + 1; index <= x - 1; index++) {
                        water_grid_x[y][index] = water_height;
                    }
                }
                height_stack.push(x);
            }
        }
        for (int x = 0; x < W; x++) {
            stack<int> height_stack;
            height_stack.push(-1);
            for (int y = 0; y < H; y++) {
                while (height_stack.top() != -1 && heightMap[height_stack.top()][x] < heightMap[y][x]) {
                    const auto water_height = min(heightMap[height_stack.top()][x], heightMap[y][x]);
                    for (int index = height_stack.top() + 1; index <= y - 1; index++) {
                        water_grid_y[index][x] = water_height;
                    }
                    height_stack.pop();
                }
                if (height_stack.top() != -1) {
                    const auto start = height_stack.top();
                    const auto water_height = min(heightMap[start][x], heightMap[y][x]);
                    for (int index = start; index <= y; index++) {
                        water_grid_y[index][x] = water_height;
                    }
                }
                height_stack.push(y);
            }
        }

        int total = 0;
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                const auto v = max(0, min(water_grid_x[y][x], water_grid_y[y][x]) - heightMap[y][x]);
                total += v;
            }
        }


        return total;
    }


    static int get_height(const vector<vector<int>>& heightMap, vector<vector<int>>& water_heights, int y, int x) {
        if (water_heights[y][x] >= 0) {
            return water_heights[y][x];
        }
        const auto w1 = get_height(heightMap, water_heights, y - 1, x);
        const auto w2 = get_height(heightMap, water_heights, y + 1, x);
        const auto w3 = get_height(heightMap, water_heights, y, x - 1);
        const auto w4 = get_height(heightMap, water_heights, y, x + 1);
        const auto w0 = heightMap[y][x];
        const auto w = min(w1, min(w2, min(w3, min(w4, w0))));
        water_heights[y][x] = w;
        return w;
    }

    int trapRainWater(vector<vector<int>>& heightMap) {
        const auto H = size(heightMap);
        const auto W = size(heightMap.front());
        vector<vector<int>> water_heights(H, vector<int>(W, -1));

        for (int i = 0; i < H; i++) {
            water_heights[i][0] = heightMap[i][0];
            water_heights[i][W - 1] = heightMap[i][W - 1];
        }
        for (int j = 0; j < W; j++) {
            water_heights[0][j] = heightMap[0][j];
            water_heights[H - 1][j] = heightMap[H - 1][j];
        }
        for (int i = 1; i < H - 1; i++) {
            for (int j = 1; j < W - 1; j++) {
            }
        }
    }
};

void test(vector<vector<int>>&& heightMap) {
    cout << Solution().trapRainWater(heightMap) << endl;
}
int main()
{
    test(get_matrix_int("[[12,13,1,12],[13,4,13,12],[13,8,10,12],[12,13,12,12],[13,13,13,13]]"));
    test(get_matrix_int("[[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]"));
    test(get_matrix_int("[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]"));
    return 0;
}