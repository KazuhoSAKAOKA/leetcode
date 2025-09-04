// leetcode_Q0081.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <optional>
using namespace std;

class Solution {
public:

    static bool binary_search(const vector<int>& nums, int target, int left, int right) {
        while (left <= right) {
            auto current_index = left + (right - left) / 2;
            if (nums[current_index] == target) {
                return true;
            }
            if (nums[current_index] < target) {
                left = current_index + 1;
            }
            else {
                right = current_index - 1;
            }
        }
        return false;
    }



    static bool bad(vector<int>& nums, int target) {
        if (nums.empty()) { return false; }
        if (nums.size() == 1) { return nums[0] == target ? true : false; }
        int left = 0;
        int right = nums.size() - 1;

        const int left_val = nums[left];
        const int right_val = nums[right];
        if (left_val == target) { return true; }
        if (right_val == target) { return true; }

        if (left_val < right_val) { return binary_search(nums, target, left, right); }
        if (right_val < target && target < left_val) { return false; }
        const bool exist_front_section = left_val < target;

        while (left <= right && 0 <= left && right < nums.size()) {
            auto current_index = left + (right - left) / 2;
            if (nums[current_index] == target) {
                return true;
            }
            if (nums[current_index] < target) {
                if (exist_front_section) {
                    if (nums[current_index] < left_val) {
                        right = current_index - 1;
                    }
                    else {
                        left = current_index + 1;
                    }
                }
                else {
                    return binary_search(nums, target, current_index + 1, right);
                }
            }
            else {
                if (exist_front_section) {
                    return binary_search(nums, target, left, current_index - 1);
                }
                else {
                    if (right_val < nums[current_index]) {
                        left = current_index + 1;
                    }
                    else {
                        right = current_index - 1;
                    }
                }
            }
        }
        return false;
    }

    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
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

    bool search(vector<int>& nums, int target) {
        if (nums.empty()) { return false; }
        if (size(nums) == 1) { return nums[0] == target ? true : false; }
        const auto f = nums.front();
        const auto b = nums.back();
        if (f == target || b == target) { return true; }
        if (b < target && target < f) { return false; }
        if (f < target) {

            auto my_binary_search = [&](int left, int right)->bool {
                while ((right - left) > 1) {
                    const auto mid = (left + right) / 2;
                    if (target == nums[mid]) { return true; }
                    if (target < nums[mid]) {
                        left = mid;
                    }
                    else {
                        right = mid;
                    }
                }
                return false;
                };


        }
        else {

        }

    }
};


void test(vector<int>&& nums, int target) {
    std::cout << Solution().search(nums, target) << std::endl;
}


int main()
{
    test({ 1,0,1,1,1 }, 0);
    test({ 1 }, 0);
    test({ 2,5,6,0,0,1,2 }, 0);
    test({ 2,5,6,0,0,1,2 }, 3);
}