// leetcode_Q0120.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

class Solution {
public:
    using MEMO_KEY = tuple<int, int>;
    using MEMO_TYPE = map<MEMO_KEY, int>;
    static int rec(const vector<vector<int>>& triangle, int depth_index, int left_index, MEMO_TYPE& memo) {
        if (triangle.size() == depth_index) {
            return 0;
        }
        const auto key = MEMO_KEY(depth_index, left_index);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }
        const auto& list = triangle[depth_index];
        if (list.size() == 1) {
            const auto value = rec(triangle, depth_index + 1, left_index, memo) + list.front();
            memo[key] = value;
            return value;
        }
        else {
            const auto value = min(
                rec(triangle, depth_index + 1, left_index, memo) + list[left_index],
                rec(triangle, depth_index + 1, left_index + 1, memo) + list[left_index + 1]) ;
            memo[key] = value;
            return value;
        }
    }


    int minimumTotal(vector<vector<int>>& triangle) {
        MEMO_TYPE memo;
        return rec(triangle, 0, 0, memo);
    }
};

void test(vector<vector<int>>&& triangle) {
    cout << Solution().minimumTotal(triangle) << endl;
}

int main()
{
    test({ {-1} ,{-2,-3} });

    test({ {-7},{-2,1},{-5,-5,9},{-4,-5,4,4},{-6,-6,2,-1,-5},{3,7,8,-3,7,-9},{-9,-1,-9,6,9,0,7},{-7,0,-6,-8,7,1,-4,9},{-3,2,-6,-9,-7,-6,-9,4,0},{-8,-6,-3,-9,-2,-6,7,-5,0,7},{-9,-1,-2,4,-2,4,4,-1,2,-5,5},{1,1,-6,1,-2,-4,4,-2,6,-6,0,6},{-3,-3,-6,-2,-6,-2,7,-9,-5,-7,-5,5,1} });
    test({ {2} ,{3,4},{6,5,7},{4,1,8,3} });
    test({ {-10} });
}