// leetcode_Q0037.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
        unordered_set<char> set{ '1','2','3','4','5','6','7','8','9', };
        removeCharsRow(board, y, set);
        removeCharsCol(board, x, set);
        removeCharsSquare(board, x, y, set);
        return set;
    }

    static bool solveSudokuCompletion(vector<vector<char>>& board, const vector<pair<int, int>>& targetIndexList, int index) {
        if (targetIndexList.size() <= index) { return true; }
        auto [y, x] = targetIndexList[index];
        const auto chars = getChars(board, x, y);
        if (chars.empty()) { return false; }
        for (auto&& c : chars) {
            board[y][x] = c;
            if (solveSudokuCompletion(board, targetIndexList, index + 1)) { return true; }
            board[y][x] = '.';
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        vector<pair<int, int>> targetIndexList;
        for (auto y = 0; y < 9; y++) {
            for (auto x = 0; x < 9; x++) {
                if (board[y][x] == '.') {
                    targetIndexList.push_back(make_pair(y, x));
                }
            }
        }
        solveSudokuCompletion(board, targetIndexList, 0);
    }
};

int main()
{
    std::cout << "Hello World!\n";
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
