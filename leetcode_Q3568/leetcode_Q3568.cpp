#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include <bitset>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solutionx {
    static constexpr int dx[4] = { 0, 1, 0, -1 };
    static constexpr int dy[4] = { 1, 0, -1, 0 };

public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        vector id(m, vector<int>(n));
        int sx, sy, cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (classroom[i][j] == 'L') {
                    id[i][j] = 1 << cnt++;
                }
            }
        }

        vector bestEnergy(m, vector(n, vector<int>(1 << cnt, -1)));
        bestEnergy[sx][sy][0] = energy;
        struct Info {
            int x, y, mask, e, steps;
        };
        queue<Info> q;
        q.push({ sx, sy, 0, energy, 0 });
        while (!q.empty()) {
            Info t = q.front();
            q.pop();
            if (t.mask == (1 << cnt) - 1) {
                return t.steps;
            }
            if (t.e == 0) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                int nx = t.x + dx[i];
                int ny = t.y + dy[i];

                if (nx < 0 || nx >= m || ny < 0 || ny >= n ||
                    classroom[nx][ny] == 'X') {
                    continue;
                }

                int ne = classroom[nx][ny] == 'R' ? energy : t.e - 1;
                int nmask = t.mask | id[nx][ny];

                if (ne > bestEnergy[nx][ny][nmask]) {
                    bestEnergy[nx][ny][nmask] = ne;
                    q.push({ nx, ny, nmask, ne, t.steps + 1 });
                }
            }
        }
        return -1;
    }
};

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        const int n = size(classroom);
        const int m = size(classroom[0]);
        int sy = -1;
        int sx = -1;
        vector<pair<int, int>> litters;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                switch (classroom[y][x]) {
                case 'S':
                    sy = y;
                    sx = x;
                    break;
                case 'L':
                    litters.push_back({ y,x });
                    break;
                }
            }
        }
        const auto k = size(litters);
        if (k == 0) { return 0; }
        const int maskbits = (1 << k) - 1;
        vector<vector<vector<int>>> ve(n, vector<vector<int>>(m, vector<int>(maskbits + 1, 0)));
        map<pair<int, int>, int> mask_keys;
        for (int i = 0; i < k; i++) {
            mask_keys.insert({ litters[i], (1 << i) });
        }
        queue<tuple<int, int, int, int, int>> q;
        q.push({ sy,sx,0, energy,1 });
        ve[sy][sx][0] = energy;
        const vector<pair<int, int>> dirs{
            {-1,0 },{ 1,0 },{ 0,-1 },{ 0,1 },
        };
        while (!q.empty()) {
            auto [y, x, mask, e, step] = q.front();
            q.pop();
            const auto next_ene = e - 1;
            for (auto&& [dy, dx] : dirs) {
                const auto ny = y + dy;
                const auto nx = x + dx;
                if (0 <= ny && ny < n && 0 <= nx && nx < m && classroom[ny][nx] != 'X') {
                    int new_mask = mask;
                    int new_ene = next_ene;
                    switch (classroom[ny][nx]) {
                    case 'L':
                    {
                        const auto bit = mask_keys[{ny, nx}];
                        if ((new_mask & bit) == 0) {
                            new_mask |= bit;
                            if (new_mask == maskbits) {
                                return step;
                            }
                        }
                    }
                    break;
                    case 'R':
                        new_ene = energy;
                        break;
                    }
                    if (ve[ny][nx][mask] < new_ene) {
                        ve[ny][nx][new_mask] = new_ene;
                        q.push({ ny,nx,new_mask, new_ene, step + 1 });
                    }
                }
            }
        }
        return -1;
    }
};

static void test(vector<string>&& classroom, int energy) {
    cout << Solution().minMoves(classroom, energy) << endl;
}

int main() {
    test(get_list_str(R"(["SRXL", "LLR.", "XRRL"])"), 3);

    test(get_list_str(R"(["S.", "XL"])"), 2);
    test(get_list_str(R"(["LS", "RL"])"), 4);
    test(get_list_str(R"(["L.S", "RXL"])"), 3);
    return 0;
}
