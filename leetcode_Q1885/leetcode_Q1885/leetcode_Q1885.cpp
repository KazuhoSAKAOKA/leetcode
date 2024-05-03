// leetcode_Q1885.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;



class Solution {
public:

    static long long bf(const vector<int>& nums1, const vector<int>& nums2) {
        if (nums1.size() < 2) {
            return 0LL;
        }

        long long count = 0;

        for (int i = 0; i < nums1.size() - 1; i++) {
            for (int j = i + 1; j < nums1.size(); j++) {
                if (nums1[i] + nums1[j] > nums2[i] + nums2[j]) {
                    count++;
                }
            }
        }

        return count;
    }

    static long long using_map(const vector<int>& nums1, const vector<int>& nums2) {
        vector<int> first_data(nums1.size(), 0);
        map<int, int> second_data;
        for (int i = 0; i < nums1.size(); i++) {
            first_data[i] = nums1[i] - nums2[i];
            second_data[nums2[i] - nums1[i]]++;
        }
        long long count = 0;
        for (int i = 0; i < nums1.size() - 1; i++) {
            const auto v = nums2[i] - nums1[i];
            second_data[v]--;
            if (second_data[v] == 0) {
                second_data.erase(v);
            }
            auto it = second_data.lower_bound(first_data[i]);
            int current = 0;
            for (auto rev_it = decltype(second_data)::reverse_iterator(it); rev_it != crend(second_data); ++rev_it) {
                
                current += rev_it->second;
                count += rev_it->second;
            }
            cout << i << "," << current << endl;
        }
        return count;
    }


    long long countPairs(vector<int>& nums1, vector<int>& nums2) {
        vector<int> diff(nums1.size(), 0);
        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = nums1[i] - nums2[i];
        }

        sort(begin(diff), end(diff));

        long long count = 0;
        for (int i = 0; i < diff.size() - 1; i++) {
            if (0 < diff[i]) {
                count += static_cast<long long>(diff.size() - i - 1);
            }
            else {
                const auto it = upper_bound(next(cbegin(diff), i + 1), cend(diff), -diff[i]);
                const auto dist = distance(it, cend(diff));
                count += static_cast<long long>(dist);
            }
        }


        return count;
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().countPairs(nums1, nums2) << endl;
}

int main()
{
    test({ 5,1,1,15,3,14,19,1,9,12,6,8,2,4,19,17,19,5, }, { 1,16,5,3,7,9,19,3,7,2,13,4,4,17,13,12,19,16, });
    test({ 2,1,2,1, }, { 1,2,1,2, });
    test({ 1,10,6,2, }, { 1,4,1,5, });
}