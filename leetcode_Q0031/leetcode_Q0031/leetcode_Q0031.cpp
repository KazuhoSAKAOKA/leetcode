// leetcode_Q0031.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(begin(nums), end(nums));
    }
};

void output(const vector<int>& nums) {
    
    for (auto&& v : nums) {
        cout << v << ",";
    }

    cout << std::endl;
}

int main()
{
    vector<int> v{ 1,2,3 };
    while (next_permutation(begin(v), end(v))) {
        output(v);
    }
}
