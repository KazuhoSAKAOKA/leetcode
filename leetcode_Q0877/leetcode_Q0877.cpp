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
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    static pair<long long, long long> rec(const vector<int>& piles, int start, int length, map<pair<int,int>, pair<long long, long long>>& memo) {
        if (length == 0) {
            return { 0LL,0LL };
        }
        const auto key = make_pair(start, length);
        auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        const auto [myscore1, oppscore1] = rec(piles, start + 1, length - 1, memo);
        const auto [myscore2, oppscore2] = rec(piles, start, length - 1, memo);
        const auto myscore1_p = myscore1 + piles[start];
        const auto myscore2_p = myscore2 + piles[start + length - 1];
        const auto diff1 = myscore1_p - oppscore1;
        const auto diff2 = myscore2_p - oppscore2;
        pair<long long, long long> r;
        if (diff2 < diff1) {
            r = make_pair(oppscore1, myscore1_p);
        }
        else {
            r = make_pair(oppscore2, myscore2_p);
        }
        memo.insert({ key, r });
        return r;
    }
    bool stoneGame(vector<int>& piles) {
        map<pair<int, int>, pair<long long, long long>> memo;
        const auto [bob, alice] = rec(piles, 0, static_cast<int>(size(piles)), memo);
        return alice > bob;
    }
};

static void test(vector<int>&& piles) {
    cout << Solution().stoneGame(piles) << endl;
}

int main() {
    test(get_list_int("[1,100,4,1]"));
    test(get_list_int("[5,3,4,5]"));
    test(get_list_int("[3,7,2,3]"));
    return 0;
}

