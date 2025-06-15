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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        const auto n = size(nums);
        const auto bit_max = (1 << (n + 1)) - 1;
        for (int bit = 0; bit < bit_max; bit++) {
            long long current1 = 1;
            long long current2 = 1;
            for (int i = 0; i < n; i++) {
                if (bit & (1 << i)) {
                    current1 *= static_cast<long long>(nums[i]);
                }
                else {
                    current2 *= static_cast<long long>(nums[i]);
                }
                if (current1 > target || current2 > target) {
                    break;
                }
            }
            if (current1 == target && current2 == target) {
                return true;
            }
        }

        return false;
    }
};
void test(vector<int>&& nums, long long target) {
    cout << Solution().checkEqualPartitions(nums, target) << endl;
}

static void run() {
    test(get_list_int("[3,1,6,8,4]"), 24);
    test(get_list_int("[2,5,3,7]"), 15);
}
}
namespace problem2 {
class Solution {
public:

    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
		const auto n = size(grid.front());
		const auto m = size(grid);
		vector<vector<int>> ans(m - k + 1, vector<int>(n - k + 1));
		if (k == 1) {
			return ans;
		}
		for (int i = 0; i < m - k + 1; i++) {
			for (int j = 0; j < n - k + 1; j++) {
				set<int> values;
				for (int l = 0; l < k; l++) {
					for (int m = 0; m < k; m++) {
						values.insert(grid[i + l][j + m]);
					}
				}
				int min_diff = INT_MAX;
				auto it = cbegin(values);
				int before = *it;
				++it;
				while (it != cend(values)) {
					min_diff = min(min_diff, abs(before - *it));
					before = *it;
					++it;
				}
				ans[i][j] = min_diff == INT_MAX ? 0 : min_diff;
			}
		}
        return ans;
    }
}; 
void test(vector<vector<int>>&& grid, int k) {
    output_matrix(Solution().minAbsDiff(grid, k));
}

static void run() {
	test(get_matrix_int("[[39461,84541],[-64975,33143]]"), 2);
	test(get_matrix_int("[[1,8],[3,-2]]"), 2);
    test(get_matrix_int("[[3,-1]]"), 1);
    test(get_matrix_int("[[1,-2,3],[2,3,5]]"), 2);
}
}
namespace problem3 {
const vector<pair<int, int>> directions{ {-1,0},{1,0}, {0,-1}, {0,1} };

class Solution {
public:

    static int dfs(const vector<string>& classroom, int energy, int y, int x, int cur_energy, set<pair<int, int>>& remains, int cur_cost, vector<vector<int>>& costs) {
        if (remains.empty()) {
            return cur_cost;
        }

        if (classroom[y][x] == 'L') {
            if (size(remains) == 1) {
                return cur_cost;
            }
            remains.erase({ y,x });
        }
        if (classroom[y][x] == 'R') {
            cur_energy = energy;
        }
        else {
            if (cur_energy == 0) {
                return INT_MAX / 2;
            }
            if (costs[y][x] <= cur_cost) {
                return INT_MAX / 2;
            }
        }
        costs[y][x] = min(costs[y][x], cur_cost);
        int min_step = INT_MAX;
        for (auto&& [dy,dx] : directions) {
            const auto nexty = y + dy;
            const auto nextx = x + dx;
            if (0 <= nexty && nexty < size(classroom) && 0 <= nextx && nextx < size(classroom.front()) && classroom[nexty][nextx] != 'X') {
                min_step = min(min_step, dfs(classroom, energy, nexty, nextx, cur_energy - 1, remains, cur_cost+1, costs));
            }
        }

        if (classroom[y][x] == 'L') {
            remains.insert({ y,x });
        }
        return min_step;
    }

    int minMoves(vector<string>& classroom, int energy) {
        const auto n = size(classroom);
        const auto m = size(classroom.front());
        pair<int, int> cur(0, 0);
        set<pair<int, int>> litters;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                if (classroom[y][x] == 'S') {
                    cur = { y,x };
                }
                else if (classroom[y][x] == 'L') {
                    litters.insert(make_pair(y, x));
                }
            }
        }
        vector<vector<int>> costs(n, vector<int>(m, INT_MAX));
        return dfs(classroom, energy, cur.first, cur.second, energy, litters, 0, costs);
    }
};
void test(vector<string>&& classroom, int energy) {
    cout << Solution().minMoves(classroom, energy) << endl;
}
static void run() {
    test(get_list_str(R"(["L.S", "RXL"])"), 3);
    test(get_list_str(R"(["S.", "XL"])"), 2);
    test(get_list_str(R"(["LS", "RL"])"), 4);
}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}