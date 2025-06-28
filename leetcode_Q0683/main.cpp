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
    static int tle(vector<int>& bulbs, int k) {
        const auto n = size(bulbs);
        vector<bool> state(n);

        auto check = [&]()->bool {
            bool prev_on = false;
            bool counting = false;
            int off_bulbs = 0;
            for (int j = 0; j < n; j++) {
                if (state[j]) {
                    if (counting) {
                        if (off_bulbs == k) {
                            return true;
                        }
                        counting = false;
                        off_bulbs = 0;
                    }
                    prev_on = true;
                }
                else {
                    if (prev_on) {
                        counting = true;
                        off_bulbs = 1;
                    }
                    else if (counting) {
                        off_bulbs++;
                    }
                    prev_on = false;
                }
            }
            return false;
            };
        for (int i = 0; i < n; i++) {
            state[bulbs[i] - 1] = true;

            if (check()) {
                return i + 1;
            }
        }
        return -1;
    }


    int kEmptySlots(vector<int>& bulbs, int k) {
        const auto n = size(bulbs);
        set<int> states;

        for (int i = 0; i < n; i++) {
            const auto target = bulbs[i];
            auto [target_it, _] = states.insert(target);

            if (target_it != cbegin(states)) {
                const auto prev_it = prev(target_it);
                if (target - *prev_it - 1 == k) {
                    return i + 1;
                }
            }
            const auto next_it = next(target_it);
            if (next_it != cend(states)) {
                if (*next_it - target - 1 == k) {
                    return i + 1;
                }
            }
        }
        return -1;
    }
};

void test(vector<int>&& bulbs, int k) {
    cout << Solution().kEmptySlots(bulbs, k) << endl;
}

int main() {
    test(get_list_int("[1,3,2]"), 1);
    test(get_list_int("[5,39,25,28,16,58,70,29,67,24,78,13,9,64,98,38,44,96,27,88,75,84,69,34,55,12,47,33,77,15,31,74,2,26,76,10,17,72,100,36,6,90,4,95,49,21,94,79,62,32,1,35,60,18,3,53,82,48,54,30,19,87,40,85,68,57,11,42,92,61,71,37,14,51,50,83,22,93,91,65,99,52,7,46,89,80,20,8,97,86,23,66,81,59,56,63,43,41,73,45]"), 4);
    test(get_list_int("[1,2,3]"), 1);
    return 0;
}