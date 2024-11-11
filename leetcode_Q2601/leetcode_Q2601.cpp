// leetcode_Q2601.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static set<int> eratosthenes(int num) {
        set<int> candidates;
        for (auto i = 2; i < num; i++) {
            candidates.insert(i);
        }
        int before = 1;
        for (;;) {
            auto it = candidates.upper_bound(before);
            if (it == end(candidates)) {
                break;
            }
            const auto current_prime = *it;
            auto it_loop = next(it);
            while (it_loop != end(candidates)) {
                if (*it_loop % current_prime == 0) {
                    it_loop = candidates.erase(it_loop);
                }
                else {
                    ++it_loop;
                }
            }
            before = current_prime;
        }
        return candidates;
    }

    bool primeSubOperation(vector<int>& nums) {
        const auto max_val = *max_element(cbegin(nums), cend(nums));
        const auto primes = eratosthenes(max_val);

        int before = nums.back();
        for (int i = size(nums) - 2; i >= 0; i--) {
            const auto diff = nums[i] - before;
            if (diff < 0) {
                before = nums[i];
            }
            else {
                const auto it = primes.upper_bound(diff);
                if (it == cend(primes)) {
                    return false;
                }
                const auto prime = *it;
                if (prime >= nums[i]) {
                    return false;
                }
                before = nums[i] - prime;
            }
        }
        return true;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().primeSubOperation(nums) << endl;
}
int main()
{
    test(get_list_int("[4,9,6,10]"));
    test(get_list_int("[6,8,11,12]"));
    test(get_list_int("[5,8,3]"));
    return 0;
}