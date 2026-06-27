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
#include "./../utility/TreeNodeUtil.h"

using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* random;
    Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
    Node(int x, Node* left, Node* right, Node* random) : val(x), left(left), right(right), random(random) {}
};
using NodeCopy = Node;

class Solution {
public:

    static NodeCopy* dfs1(Node* node, map<Node*, NodeCopy*>& mp) {
        if (node == nullptr) {
            return nullptr;
        }
        NodeCopy* ptr = new NodeCopy();
        ptr->val = node->val;
        mp.insert({ node, ptr });
        ptr->left = dfs1(node->left, mp);
        ptr->right = dfs1(node->right, mp);
        ptr->random = nullptr;
        return ptr;
    }

    NodeCopy* copyRandomBinaryTree(Node* root) {
        map<Node*, NodeCopy*> mp;
        NodeCopy* root1 = dfs1(root, mp);
        for (auto&& [node, copied] : mp) {
            if (node->random != nullptr) {
                copied->random = mp[node->random];
            }
        }

        return root1;
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
