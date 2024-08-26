// leetcode_Q0590.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cassert>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:

    static void rec(const Node* node, vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        for (auto&& child : node->children) {
            rec(child, result);
        }
        result.push_back(node->val);
    }

    vector<int> postorder(Node* root) {
        vector<int> result;
        rec(root, result);
        return result;
    }
};

Node* create_narr_tree(const vector<optional<int>>& values) {
    Node* root = new Node(values.front().value());
    if (size(values) <= 2) {
        return root;
    }
    assert(!values[1].has_value());
    vector<Node*> parents{ root };
    size_t index = 2;
    while (index < size(values)) {
        vector<Node*> current;
        for (auto&& parent : parents) {
            while (index < size(values) && values[index].has_value()) {
                Node* node = new Node(values[index].value());
                current.push_back(node);
                parent->children.push_back(node);
                index++;
            }
            index++;
        }
        parents = current;
    }
    return root;
}

void delete_node(Node* node) {
    if (node == nullptr) {
        return;
    }
    for (auto&& child : node->children) {
        delete_node(child);
        child = nullptr;
    }
    delete node;
}

void test(vector<optional<int>>&& values) {
    Node* root = create_narr_tree(values);
    const auto ans = Solution().postorder(root);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
    delete_node(root);
}
int main()
{
    test(get_list_optional_int("[1,null,3,2,4,null,5,6]"));
    test(get_list_optional_int("[1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]"));
    return 0;
}