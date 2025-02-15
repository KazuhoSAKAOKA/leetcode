// leetcode_Q1352.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;
class ProductOfNumbers {
    vector<long long> prefix_products_;
    vector<int> prefix_zeros_;
public:
    ProductOfNumbers() :prefix_products_(1, 1), prefix_zeros_(1, 0) {

    }

    void add(int num) {
        if (num == 0) {
            prefix_products_.emplace_back(1 * prefix_products_.back());
            prefix_zeros_.emplace_back(1 + prefix_zeros_.back());
        }
        else {
            prefix_products_.emplace_back(num * prefix_products_.back());
            prefix_zeros_.emplace_back(prefix_zeros_.back());
        }
    }

    int getProduct(int k) {
        const auto index = size(prefix_products_) - k - 1;
        if (prefix_zeros_.back() == prefix_zeros_[index]) {
            return static_cast<int>(prefix_products_.back() / prefix_products_[index]);
        }
        else {
            return 0;
        }
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
