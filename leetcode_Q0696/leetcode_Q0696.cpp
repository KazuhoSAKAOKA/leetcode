#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countBinarySubstrings(string s) {
        int prev_streak = 0;
        int cur_streak = 0;
        char cur_char = 0;
        int count = 0;

        for (auto&& c : s) {
            if (c == cur_char) {
                cur_streak++;
            }
            else {
                count += min(cur_streak, prev_streak);
                prev_streak = cur_streak;
                cur_streak = 1;
                cur_char = c;
            }
        }
        count += min(cur_streak, prev_streak);
        return count;
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
