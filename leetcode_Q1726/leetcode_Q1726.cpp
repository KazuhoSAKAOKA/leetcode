// leetcode_Q1726.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        map<long long, int> product_freq_map;
        int count = 0;
        for (int i = 0; i < size(nums); i++) {
            for (int j = i + 1; j < size(nums); j++) {
                const auto v = static_cast<long long>(nums[i]) * static_cast<long long>(nums[j]);
                auto it = product_freq_map.find(v);
                if (it == cend(product_freq_map)) {
                    product_freq_map.insert({ v,1 });
                }
                else {
                    count += it->second * 8;
                    it->second++;
                }
            }
        }
        return count;
    }
};


int main()
{

	return 0;
}