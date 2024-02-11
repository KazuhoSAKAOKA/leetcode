// leetcode_Q1463.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    using dp_status_type = pair<int, int>;

    static int get_before_max(const map<dp_status_type, int>& map, const dp_status_type& key) {
        int max_value = 0;
        static const vector<int> before{ -1,0,1, };
        for (auto&& r1 : before) {
            for (auto&& r2: before) {
                const auto before_key = make_pair(key.first + r1, key.second + r2);
                const auto it = map.find(before_key);
                if (it != cend(map)) {
                    max_value = max(max_value, it->second);
                }
            }
        }
        return max_value;
    }


    int cherryPickup(vector<vector<int>>& grid) {
        const size_t rows = grid.size();
        const size_t cols = grid.front().size();

        vector<map<dp_status_type, int>> dp(rows, map<dp_status_type, int>());

        const vector<int> nexts{ -1,0,1, };

        dp[0][make_pair(0, cols - 1)] = grid[0][0] + grid[0][cols - 1];

        for (int i = 1; i < rows; i++) {
            auto& before = dp[i - 1];
            auto& current = dp[i];
            for (auto& [key, value] : before) {
                auto& [r1, r2] = key;
                for (auto&& r1_nexts : nexts) {
                    const int r1_index = r1_nexts + r1;
                    if (r1_index < 0 || cols <= r1_index) { continue; }
                    for (auto&& r2_nexts : nexts) {
                        const int r2_index = r2_nexts + r2;
                        if (r2_index < 0 || cols <= r2_index) { continue; }
                        const auto key = make_pair(r1_index, r2_index);
                        const auto before_max = get_before_max(before, key);
                        if (r1_index != r2_index) {
                            current[key] = max(current[key], before_max + grid[i][r1_index] + grid[i][r2_index]);
                        }
                        else {
                            current[key] = max(current[key], before_max + grid[i][r1_index]);
                        }
                    }
                }
            }
        }

        int max_value = 0;
        for (auto&& [_, v] : dp[rows - 1]) {
            max_value = max(max_value, v);
        }
        return max_value;
    }
};


void test(vector<vector<int>>&& grid) {
    cout << Solution().cherryPickup(grid) << endl;
}

int main()
{
    test({ {3,1,1} ,{2,5,1},{1,5,5},{2,1,1} });
    test({ {1,0,0,0,0,0,1},{2,0,0,0,0,3,0},{2,0,9,0,0,0,0},{0,3,0,5,4,0,0},{1,0,2,3,0,0,6} });
}