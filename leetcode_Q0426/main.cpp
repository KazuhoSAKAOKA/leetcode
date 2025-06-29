#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
class Solution {
public:

    static pair<Node*, Node*> dfs(Node* node) {
        if (node == nullptr) {
            cerr << "invalid node is null" << endl;
            throw "dfs::nullptr";
        }
        Node* left = node->left;
        Node* right = node->right;

        Node* cur_head = nullptr;
        Node* cur_tail = nullptr;
        if (left == nullptr) {
            cur_head = node;
        }
        else {
            const auto [left_head, left_tail] = dfs(left);
            if (left_head == nullptr) {
                cerr << "invalid left head is null" << endl;
                throw "dfs::left_head::nullptr";
            }
            if (left_tail == nullptr) {
                cerr << "invalid left tail is null" << endl;
                throw "dfs::left_tail::nullptr";
            }

            cur_head = left_head;
            left_tail->right = node;
            node->left = left_tail;
        }
        if (right == nullptr) {
            cur_tail = node;
        }
        else {
            const auto [right_head, right_tail] = dfs(right);
            if (right_head == nullptr) {
                cerr << "invalid right_head is null" << endl;
                throw "dfs::right_head::nullptr";
            }
            if (right_tail == nullptr) {
                cerr << "invalid right_tail is null" << endl;
                throw "dfs::right_tail::nullptr";
            }

            right_head->left = node;
            node->right = right_head;
            cur_tail = right_tail;
        }
        return { cur_head, cur_tail };
    }


    Node* treeToDoublyList(Node* root) {
        const auto [head, tail] = dfs(root);
        head->left = tail;
        tail->right = head;
        return head;
    }
};


void test1() {
    Node* root = new Node(4);
    root->left = new Node(2);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right = new Node(5);

    Node* p = Solution().treeToDoublyList(root);
}
int main() {
    test1();
	return 0;
}