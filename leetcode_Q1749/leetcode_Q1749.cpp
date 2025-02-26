// leetcode_Q1749.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int cur_plus = 0;
        int cur_minus = 0;
        int plus_left = 0;
        int minus_left = 0;
        int max_sum = 0;

        for (int r = 0; r < size(nums); r++) {
            cur_plus += nums[r];
            cur_minus += nums[r];

            while (plus_left <= r && cur_plus < 0) {
                cur_plus -= nums[plus_left];
                plus_left++;
            }

            while (minus_left <= r && cur_minus > 0) {
                cur_minus -= nums[minus_left];
                minus_left++;
            }

            max_sum = max(max_sum, cur_plus);
            max_sum = max(max_sum, abs(cur_minus));
        }
        return max_sum;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maxAbsoluteSum(nums) << endl;
}
int main()
{
    test(get_list_int("[2,-5,1,-4,3,-2]"));
    test(get_list_int("[1,-3,2,3,-4]"));
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
