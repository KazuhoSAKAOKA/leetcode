// leetcode_Q2225.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        set<int> players;
        unordered_map<int, vector<int>> loses;

        for (auto&& match : matches) {
            players.insert(cbegin(match), cend(match));
            loses[match[1]].emplace_back(match[0]);
        }

        vector<vector<int>> ans(2, vector<int>());
        for (auto&& player : players) {
            const auto it = loses.find(player);
            if (it != cend(loses)) {
                if (it->second.size() == 1) {
                    ans[1].emplace_back(player);
                }
            }
            else {
                ans[0].emplace_back(player);
            }
        }

        return ans;
    }
};

void test(vector<vector<int>>&& matches) {
    const auto ans = Solution().findWinners(matches);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    test({ {1,3},{2,3},{3,6},{5,6},{5,7},{4,5},{4,8},{4,9},{10,4},{10,9} });
    test({ {2,3},{1,3},{5,4},{6,4} });
}
