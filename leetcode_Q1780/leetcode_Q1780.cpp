// leetcode_Q1780.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    static bool check(int n, vector<int>& powers, int index) {
        if (n == 0) { return true; }
        if (size(powers) == index) {
            return false;
        }
        if (powers[index] > n) {
            return false;
        }
        if (check(n, powers, index + 1)) {
            return true;
        }
        return check(n - powers[index], powers, index + 1);
    }

    bool checkPowersOfThree(int n) {
        vector<int> powers;
        long long value = 1;

        while (value <= n) {
            powers.emplace_back(static_cast<int>(value));
            value *= 3;
        }

        return check(n, powers, 0);
    }
};

void test(int n) {
    cout << Solution().checkPowersOfThree(n) << endl;
}
int main()
{
    test(1000000);
    test(27);
    test(12);
    test(91);
    test(21);
    return 0;
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
