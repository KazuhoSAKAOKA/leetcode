// leetcode_Q1092.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    
    static string rec(const string& str1, const string& str2, int index1, int index2, map<pair<int,int>, string>& memo) {
        if (size(str1) <= index1 && size(str2) <= index2) {
            return "";
        }
        const auto key = make_pair(index1, index2);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }


        if (size(str2) <= index2 && index1 < size(str1)) {
            string remain = str1.substr(index1);
            memo[key] = remain;
            return remain;
        }
        if (size(str1) <= index1 && index2 < size(str2)) {
            string remain = str2.substr(index2);
            memo[key] = remain;
            return remain;
        }

        if (str1[index1] == str2[index2]) {
            string cur = string(1, str1[index1]);
            cur += rec(str1, str2, index1 + 1, index2 + 1, memo);
            memo[key] = cur;
            return cur;
        }
        else {
            string v1 = string(1, str1[index1]) + rec(str1, str2, index1 + 1, index2, memo);
            string v2 = string(1, str2[index2]) + rec(str1, str2, index1, index2 + 1, memo);
            if (v1.size() < v2.size()) {
                memo[key] = v1;
                return v1;
            }
            else {
                memo[key] = v2;
                return v2;
            }
        }
    }

    static string mle(const string& str1, const string& str2) {
        map<pair<int, int>, string> memo;
        return rec(str1, str2, 0, 0, memo);
    }

    string shortestCommonSupersequence(string str1, string str2) {
        const auto len1 = size(str1);
        const auto len2 = size(str2);
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                if (str1[i] == str2[j]) {
                    dp[i + 1][j + 1] = max(dp[i][j] + 1, max(dp[i][j + 1], dp[i + 1][j]));
                }
                else {
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }

        string work;
        int ind1 = len1;
        int ind2 = len2;
        while (!(ind1 == 0 && ind2 == 0)) {
            if (ind1 > 0 && ind2 > 0) {
                if (str1[ind1 - 1] == str2[ind2 - 1] && dp[ind1][ind2] == dp[ind1 - 1][ind2 - 1] + 1) {
                    work.push_back(str1[ind1 - 1]);
                    ind1--;
                    ind2--;
                }
                else if (dp[ind1][ind2] == dp[ind1 - 1][ind2]) {
                    work.push_back(str1[ind1 - 1]);
                    ind1--;
                }
                else if (dp[ind1][ind2] == dp[ind1][ind2 - 1]) {
                    work.push_back(str2[ind2 - 1]);
                    ind2--;
                }
                else {
                    work.push_back(str1[ind1 - 1]);
                    ind1--;
                }
            }
            else {
                if (ind1 > 0) {
                    work.push_back(str1[ind1 - 1]);
                    ind1--;
                }
                else {
                    work.push_back(str2[ind2 - 1]);
                    ind2--;
                }
            }
        }
        return string(crbegin(work), crend(work));
    }
};
void test(string&& str1, string&& str2) {
    cout << Solution().shortestCommonSupersequence(str1, str2) << endl;
}

int main(){
    test("ya", "xa");
    test("abac", "cab");
    test("bcaaacbbbcbdcaddadcacbdddcdcccdadadcbabaccbccdcdcbcaccacbbdcbabb", "dddbbdcbccaccbababaacbcbacdddcdabadcacddbacadabdabcdbaaabaccbdaa");
    test("aaaaaaaa", "aaaaaaaa");

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
\