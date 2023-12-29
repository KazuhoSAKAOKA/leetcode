// leetcode_Q0074.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        const vector<int> temp{ target };
        const auto it = lower_bound(cbegin(matrix), cend(matrix), temp, [](const auto& a, const auto& b) { return a.front() < b.front(); });
        if (it == cend(matrix)) {
            return binary_search(cbegin(matrix.back()), cend(matrix.back()), target);
        }
        if (it->front() == target) {
            return true;
        }
        if (it == cbegin(matrix)) {
            return false;
        }
        const auto it2 = prev(it);
        const auto& list = *it2;
        return binary_search(cbegin(list), cend(list), target);
    }
};

void test(vector<vector<int>>&& matrix, int target) {
    cout << Solution().searchMatrix(matrix, target) << endl;
}


int main()
{
    test({ {1,3,5,7},{10,11,16,20},{23,30,34,60} }, 3);
    test({ {1,3,5,7},{10,11,16,20},{23,30,34,60} }, 13);
}

