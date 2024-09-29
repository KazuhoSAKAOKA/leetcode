// leetcode_Q1804.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Trie {
public:
    Trie() {

    }

    void insert(string word) {
        Node* current = &root_;
        for (auto&& c : word) {
            auto it = current->childs_.find(c);
            if (it != cend(current->childs_)) {
                current = it->second;
            }
            else {
                auto [new_it, _] = current->childs_.insert({ c, new Node() });
                current = new_it->second;
            }
            current->exist_count_++;
        }
        current->end_count_++;
    }

    int countWordsEqualTo(string word) {
        const Node* current = &root_;
        for (auto&& c : word) {
            auto it = current->childs_.find(c);
            if (it != cend(current->childs_) && it->second->exist_count_ > 0) {
                current = it->second;
            }
            else {
                return 0;
            }
        }
        return static_cast<int>(current->end_count_);
    }

    int countWordsStartingWith(string prefix) {
        const Node* current = &root_;
        for (auto&& c : prefix) {
            auto it = current->childs_.find(c);
            if (it != cend(current->childs_) && it->second->exist_count_ > 0) {
                current = it->second;
            }
            else {
                return 0;
            }
        }
        return static_cast<int>(current->exist_count_);
    }

    void erase(string word) {
        Node* current = &root_;
        for (auto&& c : word) {
            auto it = current->childs_.find(c);
            if (it != cend(current->childs_)) {
                current = it->second;
            }
            else {
                //assert?
                return;
            }
            current->exist_count_--;
        }
        current->end_count_--;
    }

private:
    struct Node {
        unordered_map<char, Node*> childs_;
        size_t exist_count_;
        size_t end_count_;
    };

    Node root_;
};

int main()
{
    Trie trie;
    trie.insert("apple");               // Inserts "apple".
    trie.insert("apple");               // Inserts another "apple".
    cout << trie.countWordsEqualTo("apple") << endl;    // There are two instances of "apple" so return 2.
    cout << trie.countWordsStartingWith("app") << endl; // "app" is a prefix of "apple" so return 2.
    trie.erase("apple");                // Erases one "apple".
    cout << trie.countWordsEqualTo("apple") << endl;    // Now there is only one instance of "apple" so return 1.
    cout << trie.countWordsStartingWith("app") << endl; // return 1
    trie.erase("apple");                // Erases "apple". Now the trie is empty.
    cout << trie.countWordsStartingWith("app") << endl; // return 0
    return 0;
}
