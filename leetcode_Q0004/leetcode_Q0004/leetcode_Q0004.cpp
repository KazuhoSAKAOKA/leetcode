// leetcode_Q0004.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int get_next(vector<int>::const_iterator& it) {
        const auto v = *it;
        ++it;
        return v;
    }

    int get_next(vector<int>::const_iterator& it1, vector<int>::const_iterator end1, vector<int>::const_iterator& it2, vector<int>::const_iterator end2)
    {
        if (it1 != end1) {
            if (it2 != end2) {
                if (*it1 < *it2) {
                    return get_next(it1);
                }
                else {
                    return get_next(it2);
                }
            }
            else {
                return get_next(it1);
            }
        }
        else {
            if (it2 != end2) {
                return get_next(it2);
            }
        }
        throw "UNEXPECTED";
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const auto n = nums1.size();
        const auto m = nums2.size();
        const auto total = n + m;
        const auto half = total / 2 + ((total % 2 == 0) ? 0 : 1);
        if (total == 0) { return 0.0; }
        auto it1 = cbegin(nums1);
        auto it2 = cbegin(nums2);
        const auto end1 = cend(nums1);
        const auto end2 = cend(nums2);
        int mid = 0;
        for (size_t index = 0; index < half; index++) {
            mid = get_next(it1, cend(nums1), it2, cend(nums2));
        }
        if (total % 2 == 0) {
            return (static_cast<double>(mid) + static_cast<double>(get_next(it1, end1, it2, end2))) / 2;
        }
        return static_cast<double>(mid);
    }
};

void output(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().findMedianSortedArrays(nums1, nums2) << std::endl;
}

int main()
{
    output(vector<int>{ 1, 3 }, vector<int>{ 2});
    output(vector<int>{ 1, 2 }, vector<int>{ 3,4,});
    output(vector<int>{  }, vector<int>{  });
    output(vector<int>{ 1 }, vector<int>{  });
    output(vector<int>{  }, vector<int>{ 1 });
    output(vector<int>{ 1 }, vector<int>{ 2 });
}

