// leetcode_Q0349.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(begin(nums1), end(nums1));
        sort(begin(nums2), end(nums2));

        set<int> ans;

        auto it1 = cbegin(nums1);
        auto it2 = cbegin(nums2);

        while (it1 != cend(nums1) && it2 != cend(nums2)) {
            if (*it1 == *it2) {
                ans.insert(*it1);
                ++it1;
                ++it2;
            }
            else {
                if (*it1 < *it2) {
                    ++it1;
                }
                else {
                    ++it2;
                }
            }
        }

        return vector<int>(cbegin(ans), cend(ans));
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2) {
    const auto ans = Solution().intersection(nums1, nums2);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test({1,2,2,1}, {2,2,});
    test({4,9,5,}, {9,4,9,8,4});
}
