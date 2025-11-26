#include <iostream>
#include <unordered_set>
using namespace std;
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0) {
            return -1;
        }
        unordered_set<long long> exists;
        long long v = 1;

        int len = 1;
        for (;;) {
            const auto m = v % k;
            if (m == 0) {
                break;
            }
            if (exists.count(m) != 0) {
                return -1;
            }
            exists.insert(m);
            v = (10 * v + 1) % k;
            len++;
        }

        return len;
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
