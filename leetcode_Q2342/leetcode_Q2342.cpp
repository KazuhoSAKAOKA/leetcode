// leetcode_Q2342.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Solution {
public:

    static int sum_digits(int value) {
        int total = 0;
        auto cur = value;
        while (cur > 0) {
            total += cur % 10;
            cur /= 10;
        }
        return total;
    }
    int maximumSum(vector<int>& nums) {
        map<int, multiset<int>> freq_map;
        for (auto&& num : nums) {
            const auto s = sum_digits(num);
            freq_map[s].insert(num);
            if (size(freq_map[s]) > 2) {
                freq_map[s].erase(begin(freq_map[s]));
            }
        }
        int max_value = -1;
        for (auto&& [_, list] : freq_map) {
            if (size(list) > 1) {
                auto it = cbegin(list);
                const auto v = *it + *next(it);
                max_value = max(max_value, v);
            }
        }
        return max_value;
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
