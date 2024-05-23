
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    static bool check(int k, const unordered_set<int>& sub_set, int new_value) {
        if (sub_set.count(new_value) != 0) { return true; }
        for (auto&& v : sub_set) {
            if (abs(new_value - v) == k) {
                return false;
            }
        }
        return true;
    }

    static int tle(const vector<int>& nums, int k) {
        vector<unordered_set<int>> before;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            vector<unordered_set<int>> current(before);
            current.emplace_back(unordered_set<int>{nums[i]});
            ans++;
            for (auto&& ss : before) {
                if (check(k, ss, nums[i])) {
                    auto cp(ss);
                    cp.insert(nums[i]);
                    current.emplace_back(cp);
                    ans++;
                }
            }
            before = current;
        }

        return ans;
    }
    
    static int rec(const vector<int>& nums, int index, int k, set<int>& current) {
        if (nums.size() == index) {
            return 1;
        }
        int total = rec(nums, index + 1, k, current);
        if (current.count(nums[index] - k) == 0) {
            current.insert(nums[index]);
            total += rec(nums, index + 1, k, current);
            current.erase(nums[index]);
        }
        return total;
    }
    static int mle(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        set<int> current;
        const auto ans = rec(nums, 0, k, current) - 1;
        return ans;

    }

    static int tle2(vector<int>& nums, int k) {
        int total = 0;
        sort(begin(nums), end(nums));
        long long limit = (1 << nums.size());
        auto check = [&](long long bits)->bool {
            set<int> temp;
            for (int i = 0; i < nums.size(); i++) {
                if ((bits & (1 << i)) != 0) {
                    if (temp.count(nums[i] - k) != 0) {
                        return false;
                    }
                    temp.insert(nums[i]);
                }
            }
            return true;
            };

        for (long long bits = 0; bits < limit; bits++) {
            if (check(bits)) {
                total++;
            }
        }
        return total - 1;
    }

    int rec(const vector<int>& nums, map<int, int>& freq_map, int index, int k) {
        if (index == nums.size()) {
            return 1;
        }

        int total = rec(nums, freq_map, index + 1, k);
        if (freq_map[nums[index] - k] > 0) {
            
        }
        else{
            freq_map[nums[index]]++;
            total += rec(nums, freq_map, index + 1, k);
            freq_map[nums[index]]--;
        }
        return total;
    }

    int beautifulSubsets(vector<int>& nums, int k) {
        
        sort(begin(nums), end(nums));
        map<int, int> freq_map;
        return rec(nums, freq_map, 0, k) - 1;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().beautifulSubsets(nums, k) << endl;
}

int main()
{
    test(get_list_int("[2,4,6]"), 2);

    test(get_list_int("[2,4,6,8]"), 2);
    test(get_list_int("[15,6,3,25,14,29,21,16,28,23,11,9,4,30,24,12,26,1,27,18]"), 7);
    test(get_list_int("[1]"), 1);
}