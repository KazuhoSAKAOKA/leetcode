#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class PhoneDirectory {
    set<int> assigned;
    set<int> not_assigned;
    int max_numbers;
public:
    PhoneDirectory(int maxNumbers) :max_numbers(maxNumbers){
        for (int i = 0; i < max_numbers; i++) {
            not_assigned.insert(i);
        }
    }

    int get() {
        if (not_assigned.empty()) { return -1; }
        auto it = begin(not_assigned);
        const auto id = *it;
        not_assigned.erase(it);
        assigned.insert(id);
        return id;
    }

    bool check(int number) {
        return assigned.count(number) == 0;
    }

    void release(int number) {
        auto it = assigned.find(number);
        if (it == cend(assigned)) { return; }
        const auto id = *it;
        assigned.erase(id);
        not_assigned.insert(id);
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
