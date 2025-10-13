#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 0.0000001) {
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


    double minmaxGasDist(vector<int>& stations, int k) {
        const auto n = size(stations);
        double max_len = 0.0;
        for (int i = 1; i < n; i++) {
            max_len = max(max_len, static_cast<double>(stations[i] - stations[i - 1]));
        }
        auto ans = binary_search_meguru<double>(max_len, 0,
            [&](double len)->bool {
                int count = 0;
                int index = 1;
                double before_value = stations[0];
                while (index < n) {
                    const auto cur_len = static_cast<double>(stations[index]) - before_value;
                    if (len < cur_len) {
                        if (k <= count) {
                            return false;
                        }
                        count++;
                        before_value += len;
                    }
                    else {
                        before_value = stations[index];
                        index++;
                    }
                }
                return true;
            });
        return ans;
    }
};

static void test(vector<int>&& stations, int k) {
    cout << Solution().minmaxGasDist(stations, k) << endl;
}

int main() {
    test(get_list_int("[23,24,36,39,46,56,57,65,84,98]"), 1);
    test(get_list_int("[1,2,3,4,5,6,7,8,9,10]"), 9);
    return 0;
}