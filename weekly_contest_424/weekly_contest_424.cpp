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

    static bool simulate(const vector<int>& nums, int start, int inc) {
        int cur = start;
        vector<int> numscpy(nums);
        while (0 <= cur && cur < size(nums)) {
            if (numscpy[cur] == 0) {
                cur += inc;
            }
            else {
                numscpy[cur]--;
                inc *= -1;
                cur += inc;
            }
        }
        return all_of(cbegin(numscpy), cend(numscpy), [](auto a) {return a == 0; });
    }


    int countValidSelections(vector<int>& nums) {
        int count = 0;
        const vector<int> incs{ -1,1 };
        for (int i = 0; i < size(nums); i++) {
            if (nums[i] == 0) {
                for (auto&& inc : incs) {
                    if (simulate(nums, i, inc)) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().countValidSelections(nums) << endl;
}
static void run() {
    test(get_list_int("[1,0,2,0,3]"));
    test(get_list_int("[2,3,4,0,4,1,0]"));
}
}
namespace problem2 {

class Solution {
public:
    static bool tle(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> upper_limits(size(nums));
        for (auto&& query : queries) {
            const int l = query.front();
            const int r = query.back();
            for (int i = l; i <= r; i++) {
                upper_limits[i]++;
            }
        }
        for (int i = 0; i < size(nums); i++) {
            if (upper_limits[i] < nums[i]) {
                return false;
            }
        }
        return true;
    }


    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        map<int, int> left_map;
        map<int, int> right_map;

        for (auto&& query : queries) {
            left_map[query.front()]++;
            right_map[query.back()]++;
        }
        int current_count = 0;

        for (int i = 0; i < size(nums); i++) {
            auto it_left = left_map.find(i);
            if (it_left != cend(left_map)) {
                current_count += it_left->second;
            }
            if (current_count < nums[i]) {
                return false;
            }
            auto it_right = right_map.find(i);
            if (it_right != cend(right_map)) {
                current_count -= it_right->second;
            }
        }
        return true;
    }
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().isZeroArray(nums, queries) << endl;
}
static void run() {
    test(get_list_int("[1,0,1]"), get_matrix_int("[[0,2]]"));
    test(get_list_int("[4,3,2,1]"), get_matrix_int("[[1,3],[0,2]]"));
}
}
namespace problem3 {


class Solution {
public:
    struct info_plus {
        int index;
        int value;
        int total;
    };

    int bin_search(const vector<info_plus*>& list, function<bool(const info_plus*)> pred) {
        int left = 0;
        int right = size(list);
        while (right - left > 1) {
            const auto mid = (right + left) / 2;
            if (pred(list[mid])) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        return left;
    }

    int isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        struct info {
            int index;
            int value;
        };
        map<int, vector<info>> left_map;
        map<int, vector<int>> right_map;

        for (int i = 0; i < size(queries);i++) {
            const auto& query = queries[i];
            const auto l = query[0];
            const auto r = query[1];
            const auto val = query[2];

            left_map[l].emplace_back(info{ i, val });
            right_map[r].emplace_back(i);
        }
        int ans_k = INT_MAX;


        vector<info_plus*> current_state;

        for (int i = 0; i < size(nums); i++) {
            auto it_left = left_map.find(i);
            if (it_left != cend(left_map)) {
                for (auto&& item : it_left->second) {
                    auto before = bin_search(current_state, [&](const info_plus* p) { return p->index < item.index; });
                    int cur_total = before == size(current_state) ? 0 : current_state[before]->total;
                    int new_total = cur_total + item.value;
                    auto insert_it = current_state.insert(before, new info_plus{ item.index, item.value, new_total });

                    for (auto it1 = next(insert_it); it1 != end(current_state); ++it1) {
                        (*before)->total += item.value;
                    }
                }
            }
            const auto it_detect = lower_bound(cbegin(current_state), cend(current_state), nullptr, [&](const info_plus* p, const info_plus* _ig) { return nums[i] <= p->total; });

            if (it_detect == cend(current_state)) {
                for (auto&& ptr_it : current_state) {
                    delete ptr_it;
                }
                return -1;
            }

            const auto new_k = static_cast<int>(distance(cbegin(current_state), it_detect));
            ans_k = min(ans_k, new_k);
            auto it_right = right_map.find(i);
            if (it_right != cend(right_map)) {
                int min_index = INT_MAX;
                for (auto&& index : it_right->second) {
                    auto target = lower_bound(begin(current_state), end(current_state), nullptr, [&](const info_plus* p, const info_plus* _ig) { return p->index == index; });
                    int target_index = static_cast<int>(distance(begin(current_state), target));
                    min_index = min(min_index, target_index);
                    delete *target;
                    current_state.erase(target);
                }
                int new_total = min_index == 0 ? 0 : current_state[min_index - 1]->total;

                for (int i = min_index; i < size(current_state); i++) {
                    new_total += current_state[i]->value;
                    current_state[i]->total = new_total;
                }
            }
        }
        for (auto&& ptr_it : current_state) {
            delete ptr_it;
        }

        return ans_k;
    }
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    cout << Solution().isZeroArray(nums, queries) << endl;
}
static void run() {
    test(get_list_int("[2,0,2]"), get_matrix_int("[[0,2,1],[0,2,1],[1,1,3]]"));
    test(get_list_int("[4,3,2,1]"), get_matrix_int("[[1,3,2],[0,2,1]]"));
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