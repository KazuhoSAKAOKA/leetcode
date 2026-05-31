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
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(begin(asteroids), end(asteroids));
        long long current = mass;
        for (auto&& m : asteroids) {
            if (current < m) {
                return false;
            }
            current += m;
        }
        return true;
    }
};

static void test(int mass, vector<int>&& asteroids) {
    cout << Solution().asteroidsDestroyed(mass, asteroids) << endl;
}

int main() {
    test(10, get_list_int("[3,9,19,5,21]"));
    test(5, get_list_int("[4,9,23,4]"));
    return 0;
}