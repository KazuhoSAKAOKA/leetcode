#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(begin(players), end(players), greater<int>());
        sort(begin(trainers), end(trainers), greater<int>());
        int count = 0;
        auto it = cbegin(trainers);
        auto it_player = cbegin(players);
        while (it != cend(trainers)) {
            const auto value = *it;
            it_player = lower_bound(it_player, cend(players), value, [](auto element, auto val) { return element > val; });
            if (it_player == cend(players)) {
                break;
            }
            count++;
            ++it_player;
            ++it;
        }


        return count;
    }
};

static void test(vector<int>&& players, vector<int>&& trainers) {
    cout << Solution().matchPlayersAndTrainers(players, trainers) << endl;
}
int main() {
    test(get_list_int("[8,8,8]"), get_list_int("[8,8,8]"));
    test(get_list_int("[4,7,9]"), get_list_int("[8,2,5,8]"));
    test(get_list_int("[1,1,1]"), get_list_int("[10]"));
    return 0;
}