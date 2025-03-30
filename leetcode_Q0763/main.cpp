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
    vector<int> partitionLabels(string s) {
        vector<int> first_appear(26, -1);
        vector<int> last_appear(26, -1);

        for (int i = 0; i < size(s); i++) {
            const auto index = static_cast<int>(s[i] - 'a');
            if (first_appear[index] < 0) {
                first_appear[index] = i;
            }
            last_appear[index] = i;
        }
        vector<pair<int, int>> events;
        events.reserve(52);
        for (auto&& index : first_appear) {
            if (index >= 0) {
                events.emplace_back(make_pair(index, 1));
            }
        }
        for (auto&& index : last_appear) {
            if (index >= 0) {
                events.emplace_back(make_pair(index + 1, 0));
            }
        }
        sort(begin(events), end(events));
        int current_ranges = 0;
        auto it = cbegin(events);
        int current_begin = 0;
        vector<int> ans;
        while (it != cend(events)) {
            if (it->second == 1) {
                current_ranges++;
            }
            else {
                current_ranges--;
            }
            if(current_ranges==0){
                const int current_len = it->first - current_begin;
                ans.emplace_back(current_len);
                current_begin = it->first;
            }
            ++it;
        }
        if (current_ranges > 0) {
            throw exception();
        }
        return ans;
    }
};

void test(string&& s) {
    output(Solution().partitionLabels(s));
}

int main() {
    test("ababcbacadefegdehijhklij");
    test("eccbbbbdec");
    return 0;
}