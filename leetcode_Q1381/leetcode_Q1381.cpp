// leetcode_Q1381.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class CustomStack {
public:
    CustomStack(int maxSize) :buffer_(new int[maxSize]), size_(0), capacity_(maxSize){

    }
    ~CustomStack() {
        delete [] buffer_;
    }

    void push(int x) {
        if (size_ < capacity_) {
            buffer_[size_] = x;
            size_++;
        }
    }

    int pop() {
        if (size_ == 0) {
            return -1;
        }
        const auto value = buffer_[size_ -1] ;
        size_--;
        return value;
    }

    void increment(int k, int val) {
        for (size_t i = 0; i < min(size_, static_cast<size_t>(k)); i++) {
            buffer_[i] += val;
        }
    }
private:
    int* buffer_;
    size_t size_;
    const size_t capacity_;
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
