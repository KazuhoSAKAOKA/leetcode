// leetcode_Q0036.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


class Solution {
public:

    static void removeCharsRow(const vector<vector<char>>& board, int y, unordered_set<char>& set) {
        for (auto i = 0; i < 9; i++) {
            const char v = board[y][i];
            set.erase(v);
        }
    }
    static void removeCharsCol(const vector<vector<char>>& board, int x, unordered_set<char>& set) {
        for (auto i = 0; i < 9; i++) {
            const char v = board[i][x];
            set.erase(v);
        }
    }

    static void removeCharsSquare(const vector<vector<char>>& board, int x, int y, unordered_set<char>& set) {
        const int yBase = (y / 3) * 3;
        const int xBase = (x / 3) * 3;
        for (auto y = 0; y < 3; y++) {
            for (auto x = 0; x < 3; x++) {
                const char v = board[y + yBase][x + xBase];
                set.erase(v);
            }
        }
    }

    static unordered_set<char> getChars(const vector<vector<char>>& board, int x, int y)
    {
        unordered_set<char> set{'1','2','3','4','5','6','7','8','9',};
        removeCharsRow(board, y, set);
        removeCharsCol(board, x, set);
        removeCharsSquare(board, x, y, set);
        return set;
    }

    static bool isValidSudokuCompletion(vector<vector<char>>& board, const vector<pair<int, int>>& targetIndexList, int index) {
        if (targetIndexList.size() <= index) { return true; }
        auto [y, x] = targetIndexList[index];
        const auto chars = getChars(board, x, y);
        if (chars.empty()) { return false; }
        for (auto&& c : chars) {
            board[y][x] = c;
            if (isValidSudokuCompletion(board, targetIndexList, index + 1)) { return true; }
            board[y][x] = '.';
        }
        return false;
    }
    bool isValidSudokuCompletion(vector<vector<char>>& board) {
        vector<pair<int, int>> targetIndexList;
        for (auto y = 0; y < 9; y++) {
            for (auto x = 0; x < 9; x++) {
                if (board[y][x] == '.') {
                    targetIndexList.push_back(make_pair(y, x));
                }
            }
        }
        return isValidSudokuCompletion(board, targetIndexList, 0);
    }


    static bool isValidRow(const vector<vector<char>>& board, int y) {
        unordered_set<char> set;
        for (auto i = 0; i < 9; i++) {
            const char v = board[y][i];
            if (v == '.') { continue; }
            if (set.find(v) != cend(set)) { return false; }
            set.insert(v);
        }
        return true;
    }
    static bool isValidCol(const vector<vector<char>>& board, int x) {
        unordered_set<char> set;
        for (auto i = 0; i < 9; i++) {
            const char v = board[i][x];
            if (v == '.') { continue; }
            if (set.find(v) != cend(set)) { return false; }
            set.insert(v);
        }
        return true;
    }

    static bool isValidSquare(const vector<vector<char>>& board, int index) {
        unordered_set<char> set;
        const int yBase = (index / 3) * 3;
        const int xBase = (index % 3) * 3;
        for (auto y = 0; y < 3; y++) {
            for (auto x = 0; x < 3; x++) {
                const char v = board[y + yBase][x + xBase];
                if (v == '.') { continue; }
                if (set.find(v) != cend(set)) { return false; }
                set.insert(v);
            }
        }
        return true;
    }


    bool isValidSudoku(vector<vector<char>>& board) {
        for (auto i = 0; i < 9; i++) {
            if (!isValidCol(board, i)) { return false; }
            if (!isValidRow(board, i)) { return false; }
            if (!isValidSquare(board, i)) { return false; }
        }
        return true;
    }
};


void test(vector<vector<char>>&& board) {
    cout << (Solution().isValidSudoku(board) ? "true" : "false") << endl;
}

int main()
{
    test(
        { {'.','8','7','6','5','4','3','2','1'},{'2','.','.','.','.','.','.','.','.'},{'3','.','.','.','.','.','.','.','.'},{'4','.','.','.','.','.','.','.','.'},{'5','.','.','.','.','.','.','.','.'},{'6','.','.','.','.','.','.','.','.'},{'7','.','.','.','.','.','.','.','.'},{'8','.','.','.','.','.','.','.','.'},{'9','.','.','.','.','.','.','.','.'} }
    );


    test(
{ {'5','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'} }
    );
    test(
{ {'8','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'} }
    );
}

