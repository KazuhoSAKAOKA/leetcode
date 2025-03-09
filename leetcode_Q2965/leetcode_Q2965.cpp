// leetcode_Q2965.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        const auto n = size(grid);
        vector<bool> exists(n * n);
        int a = -1;
        for (auto&& list : grid) {
            for (auto&& num : list) {
                const int index = num - 1;
                if (exists[index]) {
                    a = num;
                }
                else {
                    exists[index] = true;
                }
            }
        }
        for (int i = 0; i < n * n; i++) {
            if (!exists[i]) {
                return { a,i + 1 };
            }
        }
        return vector<int>();
    }
};

void test() {

}
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
