// leetcode_Q0079.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    bool exist_rec(vector<vector<char>>& board, string word, int index, const pair<int,int>& currentPoint, vector<vector<bool>>& used) {

        if (board[currentPoint.first][currentPoint.second] != word[index]) {
            used[currentPoint.first][currentPoint.second] = false;
            return false;
        }
        if (word.size() - 1 == index) { return true; }

        used[currentPoint.first][currentPoint.second] = true;

        static const pair<int, int> directions[]
        {
            {-1,0},{1,0}, {0,-1,},{0,1},
        };

        for (auto&& direction : directions) {
            const auto current = make_pair(currentPoint.first + direction.first, currentPoint.second + direction.second);
            if (current.first < 0 || board.size() <= current.first) { continue; }
            if (current.second < 0 || board.front().size() <= current.second) { continue; }
            if (used[current.first][current.second]) { continue; }
            if (exist_rec(board, word, index + 1, current, used)) {
                return true;
            }
        }
        used[currentPoint.first][currentPoint.second] = false;
        return false;
    }


    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> used(board.size(), vector<bool>(board.front().size(), false));

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.front().size(); j++) {
                if (exist_rec(board, word, 0, make_pair(i, j), used)) {
                    return true;
                }
            }
        }

        return false;
    }
};


void test(vector<vector<char>>&& board, const string& word) {
    cout << Solution().exist(board, word) << endl;
}


int main()
{
    test({ {'a','a'} }, "aaa");

    test({ {'A',} }, "A");

    test({ {'A', 'B', 'C', 'E'}, { 'S','F','C','S' }, { 'A','D','E','E' } }, "ABCCED");
    test({ {'A', 'B', 'C', 'E'}, { 'S','F','C','S' }, { 'A','D','E','E' } }, "SEE");
    test({ {'A', 'B', 'C', 'E'}, { 'S','F','C','S' }, { 'A','D','E','E' } }, "ABCB");
}