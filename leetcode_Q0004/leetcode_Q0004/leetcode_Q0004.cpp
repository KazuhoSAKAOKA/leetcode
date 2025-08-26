// leetcode_Q0004.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <functional>


using namespace std;


class Solution {
public:
    static int get_next(vector<int>::const_iterator& it) {
        const auto v = *it;
        ++it;
        return v;
    }

    static int get_next(vector<int>::const_iterator& it1, vector<int>::const_iterator end1, vector<int>::const_iterator& it2, vector<int>::const_iterator end2)
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
    static double past(vector<int>& nums1, vector<int>& nums2) {
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

    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const auto n = nums1.size();
        const auto m = nums2.size();
        const auto total = n + m;
        if (total == 0) { return 0.0; }

        auto get_mid = [](const vector<int>& nums) -> double {
            const auto len = size(nums);
            if (len % 2 == 1) {
                return static_cast<double>(nums[len / 2]);
            }
            return  (static_cast<double>(nums[len / 2 - 1]) + static_cast<double>(nums[len / 2])) / 2;
        };
        if (n == 0) {
            return get_mid(nums2);
        }
        else if (m == 0) {
            return get_mid(nums1);
        }
        
        auto get_counts = [](const vector<int>& nums, int val)->tuple<int, int, int> {
            const auto lower_it = lower_bound(cbegin(nums), cend(nums), val);
            const auto upper_it = upper_bound(cbegin(nums), cend(nums), val);
            const int c1 = distance(cbegin(nums), lower_it);
            const int c2 = distance(lower_it, upper_it);
            return { c1,c2, static_cast<int>(size(nums) - (c1 + c2)) };
            };

        const auto target = total % 2 == 1 ? total / 2 : total / 2 - 1;
        const auto val = binary_search_meguru<int>(max(nums1[n - 1], nums2[m - 1]), min(nums1[0], nums2[0]) - 1,
            [&](int current)->bool {
                const auto [low1, mid1, upper1] = get_counts(nums1, current);
                const auto [low2, mid2, upper2] = get_counts(nums2, current);
                return target < low1 + low2 + mid1 + mid2;
            });
        if (total % 2 == 1) {
            return static_cast<double>(val);
        }
        const auto [low1,eq1,l1] = get_counts(nums1, val);
        const auto [low2,eq2,l2] = get_counts(nums2, val);

        if ((eq1 + eq2) > 1 && (low1 + low2 + eq1 + eq2) != (l1 + l2)) {
            return static_cast<double>(val);
        }
        int next_val;
        if (l1 == 0) {
            if (l2 == 0) {
                throw exception();
            }
            next_val = *upper_bound(cbegin(nums2), cend(nums2), val);
        }
        else if (l2 == 0) {
            next_val = *upper_bound(cbegin(nums1), cend(nums1), val);
        }
        else {
            next_val = min(*upper_bound(cbegin(nums1), cend(nums1), val), *upper_bound(cbegin(nums2), cend(nums2), val));
        }

        const auto ans = (static_cast<double>(val) + static_cast<double>(next_val)) / 2;
        return ans;
    }
};

void output(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().findMedianSortedArrays(nums1, nums2) << std::endl;
}

int main()
{
    output(vector<int>{ 2, 2, 4, 4}, vector<int>{ 2, 2, 4, 4 });
    output(vector<int>{ }, vector<int>{ 2,3 });
    output(vector<int>{ 1, 3 }, vector<int>{ 2 });
    output(vector<int>{ 2, 2, 4, 4, }, vector<int>{ 2, 2, 2, 4, 4 });
    output(vector<int>{ 0,0, }, vector<int>{ 0,0, });
    output(vector<int>{ 1 }, vector<int>{ 2 });
    output(vector<int>{ 1, 3 }, vector<int>{ 2});
    output(vector<int>{ 1, 2 }, vector<int>{ 3,4,});
    output(vector<int>{  }, vector<int>{  });
    output(vector<int>{ 1 }, vector<int>{  });
    output(vector<int>{  }, vector<int>{ 1 });
}

