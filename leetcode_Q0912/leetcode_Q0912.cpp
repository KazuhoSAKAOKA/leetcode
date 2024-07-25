// leetcode_Q0912.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int select_pivot_index(const vector<int>& nums, int begin_index, int size) {
        if (size < 3) {
            return begin_index;
        }
        const int mid_index = begin_index + size / 2;
        const int last_index = begin_index + size - 1;
        if (nums[begin_index] < nums[mid_index]) {
            // begin,mid,last
            if (nums[mid_index] < nums[last_index]) {
                return mid_index;
            }
            else {
                // begin,last,mid
                if (nums[begin_index] < nums[last_index]) {
                    return last_index;
                }
                // last,begin,mid
                else {
                    return begin_index;
                }
            }
        }
        else {
            // mid,begin,last
            if (nums[begin_index] < nums[last_index]) {
                return begin_index;
            }
            else {
                // mid,last,begin
                if (nums[mid_index] < nums[last_index]) {
                    return last_index;
                }
                // last,mid,begin
                else {
                    return mid_index;
                }
            }
        }
    }

    static int partition(vector<int>& nums, int begin_index, int size) {
        int lower_count = 0;

        const auto pivot_index = select_pivot_index(nums, begin_index, size);
        const auto pivot = nums[pivot_index];
        swap(nums[pivot_index], nums[begin_index + size - 1]);
        for (int i = begin_index; i < begin_index + size - 1; i++) {
            if (nums[i] < pivot) {
                swap(nums[begin_index + lower_count], nums[i]);
                lower_count++;
            }
        }
        swap(nums[begin_index + lower_count], nums[begin_index + size - 1]);
        return lower_count;
    }

    static void quick_sort(vector<int>& nums, int begin_index, int size) {
        if (size <= 1) {
            return;
        }
        const auto lower_count = partition(nums, begin_index, size);
        quick_sort(nums, begin_index, lower_count);
        quick_sort(nums, begin_index + lower_count + 1, size - lower_count - 1);
    }


    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size());
        return nums;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().sortArray(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(get_list_int("[5,2,3,1]"));
    test(get_list_int("[5,1,1,2,0,0]"));
    return 0;
}