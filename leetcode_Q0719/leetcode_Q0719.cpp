// leetcode_Q0719.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int tle(const vector<int>& nums, int k) {
        vector<int> distances;
        const size_t n = size(nums);
        distances.reserve(n * (n - 1));
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                distances.emplace_back(abs(nums[i] - nums[j]));
            }
        }
        sort(begin(distances), end(distances));
        return distances[k - 1];
    }


    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int arraySize = nums.size();

        // Largest element in the sorted array
        int maxElement = nums[arraySize - 1];

        // Maximum possible distance
        int maxPossibleDistance = maxElement * 2;

        // Initialize arrays for prefix counts and value counts
        vector<int> prefixCount(maxPossibleDistance, 0);
        unordered_map<int, int> valueCount;

        // Populate the prefixCount array
        int index = 0;
        for (int value = 0; value < maxPossibleDistance; ++value) {
            while (index < arraySize && nums[index] <= value) {
                ++index;
            }
            prefixCount[value] = index;
        }

        // Populate the valueCount map
        for (int i = 0; i < arraySize; ++i) {
            ++valueCount[nums[i]];
        }

        // Binary search for the k-th smallest distance
        int low = 0, high = maxElement;
        while (low < high) {
            int mid = (low + high) / 2;

            // Count pairs with distance <= mid
            int count = countPairs(nums, prefixCount, valueCount, mid);

            // Adjust binary search bounds based on count
            if (count < k) {
                low = mid + 1;
            }
            else {
                high = mid;
            }
        }
        return low;
    }

private:
    // Count number of pairs with distance <= m
    int countPairs(vector<int>& nums, vector<int>& prefixCount,
        unordered_map<int, int>& valueCount, int maxDistance) {
        int count = 0;
        int arraySize = nums.size();
        int index = 0;

        while (index < arraySize) {
            int currentValue = nums[index];
            int valueCountForCurrent = valueCount.at(currentValue);

            // Calculate pairs involving current value with distance <=
            // maxDistance
            int pairsWithLargerValues =
                prefixCount[currentValue + maxDistance] -
                prefixCount[currentValue];
            int pairsWithSameValues =
                valueCountForCurrent * (valueCountForCurrent - 1) / 2;

            count += pairsWithLargerValues * valueCountForCurrent +
                pairsWithSameValues;

            // Skip duplicate values
            while (index + 1 < arraySize && nums[index] == nums[index + 1]) {
                ++index;
            }
            ++index;
        }
        return count;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().smallestDistancePair(nums, k) << endl;
}
int main()
{
    test(get_list_int("[1,6,1]"), 3);

    test(get_list_int("[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]"), 5);
    test(get_list_int("[1,3,1]"), 1);
    test(get_list_int("[1,1,1]"), 2);

    return 0;
}