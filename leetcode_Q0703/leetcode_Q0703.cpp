// leetcode_Q0703.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class KthLargest {
    int k_;
    multiset<int> values_;
public:
    KthLargest(int k, vector<int>& nums) : k_(k), values_(cbegin(nums), cend(nums)){
    }

    int add(int val) {
        values_.insert(val);
        auto it = crbegin(values_);
        for (int i = 0; i < k_ - 1; i++) {
            ++it;
        }
        return *it;
    }
};

int main()
{


    auto nums = get_list_int("[4, 5, 8, 2]");
    KthLargest item(3, nums);
    cout << item.add(3) << endl;
    cout << item.add(5) << endl;
    cout << item.add(10) << endl;
    cout << item.add(9) << endl;
    cout << item.add(4) << endl;

}