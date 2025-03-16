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

    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    long long repairCars(vector<int>& ranks, int cars) {
        long long ok = static_cast<long long>(cars)* static_cast<long long>(cars) * static_cast<long long>(*max_element(cbegin(ranks), cend(ranks)));
        long long ng = 0;

        auto check = [&](long long time)->bool {
            long long remain = cars;
            for (auto&& rank : ranks) {
                const auto cur_cars = static_cast<long long>(sqrt(time / rank));
                remain -= cur_cars;
            }
            return remain <= 0;
            };
        return binary_search_meguru<long long>(ok, ng, check);
    }

};

void test(vector<int>&& ranks, int cars) {
    cout << Solution().repairCars(ranks, cars) << endl;
}

int main() {
    test(get_list_int("[4,2,3,1]"), 10);
    test(get_list_int("[5,1,8]"), 6);
    return 0;
}