#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
using namespace std;
class FindSumPairs {
    map<int, int> num1_map;
    unordered_map<int, int> num2_map;
    vector<int> nums2;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) :nums2(nums2){
        for (auto&& num : nums1) {
            num1_map[num]++;
        }
        for (auto&& num : nums2) {
            num2_map[num]++;
        }

    }

    void add(int index, int val) {
        num2_map[nums2[index]]--;
        nums2[index] += val;
        num2_map[nums2[index]]++;
    }

    int count(int tot) {
        int total = 0;
        for (auto it = cbegin(num1_map); it != cend(num1_map); ++it) {
            const auto it2 = num2_map.find(tot - it->first);
            if (it2 != cend(num2_map)) {
                total += it->second * it2->second;
            }
        }
        return total;
    }
};

int main() {
	return 0;
}