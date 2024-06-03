// leetcode_Q1940.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <list>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> longestCommonSubsequence(vector<vector<int>>& arrays) {
        list<int> work(cbegin(arrays.front()), cend(arrays.front()));

        for (int i = 1; i < arrays.size(); i++) {
            const auto& current = arrays[i];
            auto it = begin(work);
            int index = 0;
            while (index < current.size() && it != cend(work)) {
                if (current[index] == *it) {
                    ++it;
                    ++index;
                    continue;
                }
                else if (current[index] < *it) {
                    ++index;
                }
                else {
                    it = work.erase(it);
                }
            }

            while (it != end(work)) {
                it = work.erase(it);
            }
        }

        return vector<int>(cbegin(work), cend(work));
    }
};

void test(vector<vector<int>>&& arrays) {
    const auto ans = Solution().longestCommonSubsequence(arrays);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main() {
    test(get_matrix_int("[[1,2,3,4,5,6,7,9,10],[1,3,4,5,7,8,9,10],[1,2,6,7,8,10],[1,2,3,4,5,6,7,8,9,10],[2,4,5,6,7,8,9,10],[2,6,7,8,9]]"));
    test(get_matrix_int("[[1,3,4],[1,4,7,9]]"));
    test(get_matrix_int("[[2,3,6,8],[1,2,3,5,6,7,10],[2,3,4,6,9]]"));
    test(get_matrix_int("[[1,2,3,4,5],[6,7,8]]"));
}