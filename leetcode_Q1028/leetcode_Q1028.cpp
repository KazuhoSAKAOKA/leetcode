// leetcode_Q1028.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;
class Solution {
public:
    static size_t get_depth(const string& traversal, int index) {
        int len = 0;
        while (index + len < size(traversal) && traversal[index + len] == '-') {
            len++;
        }
        return len;
    }
    static int get_val_len(const string& traversal, int index) {
        int len = 0;
        while (index + len < size(traversal) && traversal[index + len] != '-') {
            len++;
        }
        return len;
    }

    static TreeNode* rec(const string& traversal, int& index, int depth) {
        if (size(traversal) <= index) {
            return nullptr;
        }
        const auto cur_depth = get_depth(traversal, index);
        if (depth != cur_depth) {
            return nullptr;
        }
        const auto val_len = get_val_len(traversal, index + cur_depth);
        const string val_str = traversal.substr(index + cur_depth, val_len);
        const int val = stoi(val_str);
        TreeNode* node = new TreeNode(val);
        index += cur_depth + val_len;
        node->left = rec(traversal, index, cur_depth + 1);
        node->right = rec(traversal, index, cur_depth + 1);
        return node;
    }

    TreeNode* recoverFromPreorder(string traversal) {
        int index = 0;
        return rec(traversal, index, 0);
    }
};

void test(string&& traversal) {
    output_treenode(Solution().recoverFromPreorder(traversal));
}

int main()
{
    test("1-2--3--4-5--6--7");
    test("1-2--3---4-5--6---7");
    test("1-401--349---90--88");
    return 0;
}