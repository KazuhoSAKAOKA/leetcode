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
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        const auto n = size(nums);
        vector<long long> ans;
        map<int, int> freq_map;
        set<pair<int,int>, greater<pair<int, int>>> count_set;
        for (int i = 0; i < k; i++) {
            freq_map[nums[i]]++;
        }
        for (auto&& [num, freq] : freq_map) {
            count_set.insert({ freq, num });
        }
        long long cur_total = 0LL;
        set<pair<int, int>> cur_nums;
        {
            auto it = cbegin(count_set);
            while (size(cur_nums) < x && it != cend(count_set)) {
                const auto [freq, num] = *it;
                cur_total += static_cast<long long>(freq) * num;
                cur_nums.insert({ freq, num });
                ++it;
            }
        }
        ans.emplace_back(cur_total);

        auto append_value = [&](int append_num) {
            int freq;
            auto it = freq_map.find(append_num);
            if (it == cend(freq_map)) {
                freq_map.insert({ append_num, 1 });
                freq = 1;
            }
            else {
                it->second++;
                freq = it->second;
            }
            if (freq > 1) {
                count_set.erase({ freq - 1, append_num });
            }
            count_set.insert({ freq, append_num });
            };

        auto erase_value = [&](int erase_num) {
            auto it = freq_map.find(erase_num);
            if (it == cend(freq_map)) {
                throw runtime_error("!");
            }
            it->second--;
            const int freq = it->second;
            count_set.erase({ freq + 1, erase_num });
            if (freq > 0) {
                count_set.erase({ freq, erase_num });
            }
            };

        for (int i = 0; i + k < n; i++) {
            const auto erase_num = nums[i];
            const auto append_num = nums[i + k];
            append_value(append_num);
            erase_value(erase_num);
            const auto append_freq = freq_map[append_num];
            const auto erase_freq = freq_map[erase_num];
            if (size(cur_nums) < x) {
                cur_nums.erase({ append_freq - 1, append_num });
                cur_nums.erase({ erase_freq + 1, erase_num });
                cur_nums.insert({ append_freq, append_num });
                cur_nums.insert({ erase_freq, erase_num });
                cur_total += static_cast<long long>(append_num);
                cur_total -= static_cast<long long>(erase_num);
            }
            else {
                if (erase_num != append_num) {
                    const auto it_erase = cur_nums.find({ erase_freq + 1, erase_num });
                    if (it_erase != cend(cur_nums)) {
                        cur_nums.erase(it_erase);
                        if (erase_freq == 0) {
                            cur_total -= static_cast<long long>(erase_num);
                        }
                        else {
                            const pair<int, int> erase_pair = { erase_freq, erase_num };
                            const pair<int, int> min_pair = *cbegin(cur_nums);
                            const auto it_cand = count_set.upper_bound(min_pair);
                            if (it_cand != cend(count_set) && *it_cand > erase_pair) {
                                cur_nums.insert(*it_cand);
                                cur_total -= static_cast<long long>(erase_freq + 1) * erase_num;
                                cur_total += static_cast<long long>(it_cand->first) * it_cand->second;
                            }
                            else {
                                cur_nums.insert(erase_pair);
                                cur_total -= static_cast<long long>(erase_num);
                            }
                        }
                    }

                    const auto it_append = cur_nums.find({ append_freq - 1, append_num });
                    if (it_append != cend(cur_nums)) {
                        cur_nums.erase(it_append);
                        cur_nums.insert({ append_freq, append_num });
                        cur_total += static_cast<long long>(append_num);
                    }
                    else {
                        const pair<int, int> cand_pair = { append_freq, append_num };
                        if (cur_nums.empty()) {
                            const auto max_p = *cbegin(count_set);
                            cur_nums.insert(max_p);
                            cur_total += static_cast<long long>(max_p.first) * max_p.second;
                        }
                        else {
                            const pair<int, int> min_pair = upper_bound

                            if (size(cur_nums) < x) {
                                if (min_pair < cand_pair) {
                                    cur_nums.insert(cand_pair);
                                    cur_total += static_cast<long long>(append_freq) * append_num;
                                }
                                else {
                                    cur_nums.insert(min_pair);
                                    cur_total += static_cast<long long>(min_pair.first) * min_pair.second;
                                }
                            }
                            else {
                                if (min_pair < cand_pair) {
                                    cur_nums.erase(min_pair);
                                    cur_nums.insert(cand_pair);
                                    cur_total -= static_cast<long long>(min_pair.first) * min_pair.second;
                                    cur_total += static_cast<long long>(append_freq) * append_num;
                                }
                            }

                        }
                    }

                }
            }
            ans.emplace_back(cur_total);
        }
        return ans;
    }
};

static void test(vector<int>&& nums, int k, int x) {
    output(Solution().findXSum(nums, k, x));
}
int main() {
    test(get_list_int("[3,8,7,8,7,5]"), 2, 2);


    test(get_list_int("[10,7,6,9,8]"), 2, 1);


    test(get_list_int("[5,1]"), 1, 1);
    test(get_list_int("[1,1,2,2,3,4,2,3]"), 6, 2);
    return 0;
}