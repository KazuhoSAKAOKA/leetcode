#include <iostream>
#include <vector>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int total = 0;
        auto get_time = [](const vector<int>& a, const vector<int>& b)-> int {
            const auto diffy = abs(a[0] - b[0]);
            const auto diffx = abs(a[1] - b[1]);
            const auto slant = min(diffy, diffx);
            return max(diffy, diffx) - slant + slant;
            };
        for (int i = 1; i < size(points); i++) {
            total += get_time(points[i - 1], points[i]);
        }
        return total;
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
