// leetcode_Q2463.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    using memo_key_t = tuple<int, int, int>;
    using memo_t = map<memo_key_t, pair<long long, bool>>;
    static pair<long long, bool> rec(const vector<int>& robot, const vector<vector<int>>& factory, int index, int factory_index, int current_factory_remain, long long remain_margin, memo_t& memo) {
        if (size(robot) == index) {
            return { 0LL, true };
        }

        const auto key = memo_key_t(index, factory_index, current_factory_remain);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int cur_factory_index = factory_index;
        int cur_factory_remain = current_factory_remain;
        if (cur_factory_remain == 0) {
            cur_factory_index++;
            if (size(factory) == cur_factory_index) {
                const pair<long long, bool> r = make_pair(LLONG_MAX, false);
                memo.insert(make_pair(key, r));
                return r;
            }
            cur_factory_remain = factory[cur_factory_index].back();
        }

        long long cur_margin = remain_margin;
        long long min_distance = LLONG_MAX;
        while (cur_margin >= 0) {
            cur_factory_remain--;
            const auto cur_distance_opt = rec(robot, factory, index + 1, cur_factory_index, cur_factory_remain, cur_margin, memo);
            if (!cur_distance_opt.second) {
                break;
            }
                        
            const auto cur_distance = cur_distance_opt.first + abs(factory[cur_factory_index].front() - robot[index]);
            min_distance = min(min_distance, cur_distance);

            cur_factory_index++;
            if (size(factory) == cur_factory_index) {
                break;
            }
            cur_margin -= cur_factory_remain;
            cur_factory_remain = factory[cur_factory_index].back();
        }
        if (min_distance == LLONG_MAX) {
            const pair<long long, bool> r = make_pair(LLONG_MAX, false);
            memo.insert(make_pair(key, r));
            return r;
        }
        else {
            const pair<long long, bool> r = make_pair(min_distance, true);
            memo.insert(make_pair(key, r));
            return r;
        }
    }

    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(begin(robot), end(robot));

        vector<vector<int>> factory1;
        factory1.reserve(size(factory));
        for (auto&& f : factory) {
            if (f.back() > 0) {
                factory1.emplace_back(f);
            }
        }
        sort(begin(factory1), end(factory1), [](const auto& a, const auto& b) { return a.front() < b.front(); });
        long long capacity = 0;
        for (auto&& fac : factory1) {
            capacity += static_cast<long long>(fac.back());
        }

        long long margin = capacity - static_cast<long long>(size(robot));
        memo_t memo;
        const auto ans = rec(robot, factory1, 0, 0, factory1[0].back(), margin, memo);
        return ans.first;
    }
};

void test(vector<int>&& robot, vector<vector<int>>&& factory) {
    cout << Solution().minimumTotalDistance(robot, factory) << endl;
}

int main()
{
    test(get_list_int("[789300819,-600989788,529140594,-592135328,-840831288,209726656,-671200998]"), get_matrix_int("[[-865262624,6],[-717666169,0],[725929046,2],[449443632,3],[-912630111,0],[270903707,3],[-769206598,2],[-299780916,4],[-159433745,5],[-467185764,3],[849991650,7],[-292158515,6],[940410553,6],[258278787,0],[83034539,2],[54441577,3],[-235385712,2],[75791769,3]]"));
    test(get_list_int("[9,11,99,101]"), get_matrix_int("[[10,1],[7,1],[14,1],[100,1],[96,1],[103,1]]"));
    test(get_list_int("[0,4,6]"), get_matrix_int("[[2,2],[6,2]]"));
    test(get_list_int("[1,-1]"), get_matrix_int("[[-2,1],[2,1]]"));
    return 0;
}