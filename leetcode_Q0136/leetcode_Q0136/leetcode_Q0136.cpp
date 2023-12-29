// leetcode_Q0136.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if (nums.empty()) { return 0; }

        set<int> exists;
        for (auto&& v : nums) {
            const auto it = exists.find(v);
            if (it != cend(exists)) {
                exists.erase(it);
            }
            else {
                exists.insert(v);
            }
        }
        return *cbegin(exists);
    }
};

int main()
{
    vector<int> nums1{ 2,2,1 };
    std::cout << Solution().singleNumber(nums1) << std::endl;
    vector<int> nums2{ 4,1,2,1,2 };
    std::cout << Solution().singleNumber(nums2) << std::endl;
    vector<int> nums3{ 5 };
    std::cout << Solution().singleNumber(nums3) << std::endl;

}

