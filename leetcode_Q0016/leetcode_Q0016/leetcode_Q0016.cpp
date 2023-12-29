// leetcode_Q0016.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>

using namespace std;

class Solution {

    pair<vector<int>::const_iterator, int> nearest_binary_search(const vector<int>::const_iterator& begin, const vector<int>::const_iterator& last, int value) {
        auto range_begin = begin;
        auto range_end = last;

        auto it = next(range_begin, distance(range_begin, range_end) / 2);
        int min_diff = abs(*it - value);
        auto min_diff_it = it;
        auto last_it = it;
        for (;;) {
            const auto current = *it;
            if (current == value) { return make_pair(it, 0); }
            if (current < value) {
                range_begin = it;
            }
            else {
                range_end = it;
            }
            const auto current_diff = abs(value - current);
            if (current_diff < min_diff) {
                min_diff = min_diff;
                min_diff_it = it;
            }
            it = next(range_begin, distance(range_begin, range_end) / 2);
            if (last_it == it) { break; }
            last_it = it;
        }
        return make_pair(min_diff_it, min_diff);
    }

    int treeSumClosest1(const vector<int>& nums, int target) {

        const auto end_it = cend(nums);
        int mindiff = INT_MAX;
        int closestValue = INT_MAX;
        for (size_t i = 0; i < nums.size() - 2; i++) {
            for (size_t j = i + 1; j < nums.size() - 1; j++) {
                const auto value = target - (nums[i] + nums[j]);

                const auto begin_it = next(cbegin(nums), j + 1);
                const auto [it, diff] = nearest_binary_search(begin_it, end_it, value);

                if (diff == 0) {
                    return target;
                }
                if (diff < mindiff) {
                    mindiff = diff;
                    closestValue = nums[i] + nums[j] + *it;
                }
            }
        }
        return closestValue;
    }

public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));

        if (nums.size() < 4 ) {
            return treeSumClosest1(nums, target);
        }
        vector<int> delegates;
        delegates.emplace_back(nums[0]);
        delegates.emplace_back(nums[1]);
        delegates.emplace_back(nums[2]);
        for(size_t i = 3; i < nums.size(); i++){
            if (nums[i - 3] != nums[i]) {
                delegates.emplace_back(nums[i]);
            }
        }
        return  treeSumClosest1(delegates, target);
    }
};



void test(vector<int>&& list, int target, int expected)
{
    const auto v = Solution().threeSumClosest(list, target);
    std::cout << v << "," << ((v == expected) ? "ok" : "ng") << std::endl;
}

int main()
{
    //test(vector<int>{-1, 2, 1, -4}, 1, 2);
    //test(vector<int>{0, 0, 0}, 1, 0);
    test(vector<int>{1, 1, 1, 1}, 1, 3);
}

