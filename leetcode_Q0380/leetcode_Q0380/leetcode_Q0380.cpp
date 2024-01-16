// leetcode_Q0380.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <unordered_set>

using namespace std;

constexpr size_t HashListSize = 1 << 16 + 1;

class RandomizedSet {

private:
    struct node_type;
    using node_ptr = node_type*;
    struct node_type {
        int _value;
        node_ptr _next;

        node_type(int value) : _value(value), _next(nullptr){}
        ~node_type() { delete _next; }
    };

    vector<node_ptr> _node_list;
    unordered_set<int> _hash_set;
public:
    RandomizedSet()
        :_node_list(HashListSize, nullptr),
        _hash_set()
    {

    }
    ~RandomizedSet(){
        for (auto&& ptr : _node_list) { delete ptr; }
    }

    bool insert(int val) {
        const auto hash = val % HashListSize;
        if (_node_list[hash] == nullptr) {
            _node_list[hash] = new node_type(val);
            _hash_set.insert(hash);
            return true;
        }

        node_ptr node = _node_list[hash];
        if (node->_value == val) { return false; }

        while (node->_next != nullptr) {
            node = node->_next;
            if (node->_value == val) { return false; }
        }

        node->_next = new node_type(val);
        return true;
    }
    

    bool remove(int val) {
        const auto hash = val % HashListSize;
        if (_node_list[hash] == nullptr) {
            return false;
        }
        if (_node_list[hash]->_value == val) {
            if (_node_list[hash]->_next != nullptr) {
                node_ptr temp = _node_list[hash]->_next;
                delete _node_list[hash];
                _node_list[hash] = temp;
            }
            else {
                delete _node_list[hash];
                _node_list[hash] = nullptr;
                _hash_set.erase(hash);
            }
            return true;
        }

        node_ptr node = _node_list[hash];
        while (node->_next != nullptr) {
            node_ptr before = node;
            node = node->_next;
            if (node->_value == val) {
                if (node->_next != nullptr) {
                    node_ptr temp = node->_next;
                    delete before->_next;
                    before->_next = temp;
                }
                else {
                    delete before->_next;
                    before->_next = nullptr;
                }
                return true;
            }
        }

        return false;
    }

    int getRandom() {
        if (_hash_set.size() == 0) { return 0; }
        int r = static_cast<int>((static_cast<double>(rand()) / RAND_MAX) * _hash_set.size());
        if (_hash_set.size() <= r) {
            r = _hash_set.size() - 1;
        }
        const int index = *next(cbegin(_hash_set), r);
        node_ptr node = _node_list[index];

        if (node->_next == nullptr) { return node->_value; }

        //手抜き(同じハッシュの場合)
        while (node->_next != nullptr) {
            if (rand() < (RAND_MAX / 2)) {
                return node->_value;
            }
            node = node->_next;
        }
        return node->_value;
    }
};


int main()
{
 
    RandomizedSet s;
    cout << s.insert(1) << endl;
    cout << s.insert(10) << endl;
    cout << s.insert(20) << endl;
    cout << s.insert(30) << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;
    cout << s.getRandom() << endl;


}