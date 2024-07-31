// leetcode_Q1105.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    using memo_key_t = int;
    using memo_t = unordered_map<memo_key_t, int>;


    static int rec(const vector<vector<int>>& books, int shelfWidth, int index, memo_t& memo) {
        if (books.size() == index) {
            return 0;
        }

        const auto key = memo_key_t(index);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int min_height = INT_MAX;

        int current_width = 0;
        int current_index = index;
        int current_height = 0;
        while (current_index < books.size()) {
            const auto& thickness_height = books[current_index];
            const auto thickness = thickness_height[0];
            const auto height = thickness_height[1];
            current_width += thickness;
            if (shelfWidth < current_width) {
                break;
            }
            current_height = max(current_height, height);
            const auto temp = rec(books, shelfWidth, current_index + 1, memo);
            min_height = min(min_height, temp + current_height);
            current_index++;
        }

        memo[key] = min_height;
        return min_height;
    }



    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        memo_t memo;
        return rec(books, shelfWidth, 0, memo);
    }
};

void test(vector<vector<int>>&& books, int shelfWidth) {
    cout << Solution().minHeightShelves(books, shelfWidth) << endl;
}

int main()
{
    test(get_matrix_int("[[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]]"), 4);
    test(get_matrix_int("[[1,3],[2,4],[3,2]]"), 6);
    return 0;
}