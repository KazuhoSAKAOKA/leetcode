// leetcode_Q0096.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:

    long backtrack(const vector<int>& list, map<vector<int>, int>& memo) {
        const auto it = memo.find(list);
        if (it != cend(memo)) {
            return it->second;
        }
        if (list.size() <= 1) {
            return 1;
        }
        long count = 0;
        for (auto it = cbegin(list); it != cend(list); ++it) {
            const auto left = backtrack(vector<int>(cbegin(list), it), memo);
            const auto right = backtrack(vector<int>(next(it), cend(list)), memo);
            count += left * right;
        }
        memo[list] = count;
        return count;
    }


    long numTrees(int n) {
        vector<int> list;
        for (int i = 0; i < n; i++) {
            list.emplace_back(i + 1);
        }
        map<vector<int>, int> memo;
        return backtrack(list, memo);
    }
};

int main()
{
    for (int i = 1; i <= 19; i++) {
        cout << i << ":" << Solution().numTrees(i) << endl;
    }
}

