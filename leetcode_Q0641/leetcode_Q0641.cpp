// leetcode_Q0641.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class MyCircularDeque {
public:
    MyCircularDeque(int k) : storage_(new int[k]), index_(0), size_(0), capacity_(k) {

    }
    ~MyCircularDeque() {
        delete[] storage_;
    }


    bool insertFront(int value) {
        if (size_ == capacity_) {
            return false;
        }
        if (index_ == 0) {
            index_ = capacity_ - 1;
        }
        else {
            index_--;
        }
        storage_[index_] = value;
        size_++;
        return true;
    }

    bool insertLast(int value) {
        if (size_ == capacity_) {
            return false;
        }
        storage_[(index_ + size_) % capacity_] = value;
        size_++;
        return true;
    }

    bool deleteFront() {
        if (size_ == 0) {
            return false;
        }
        size_--;
        index_++;
        index_ %= capacity_;
        return true;
    }

    bool deleteLast() {
        if (size_ == 0) {
            return false;
        }
        size_--;
        return true;
    }

    int getFront() {
        if (size_ == 0) {
            return -1;
        }
        return storage_[index_];
    }

    int getRear() {
        if (size_ == 0) {
            return -1;
        }
        return storage_[(index_ + size_ - 1) % capacity_];
    }

    bool isEmpty() {
        return size_ == 0;
    }

    bool isFull() {
        return size_ == capacity_;
    }

private:
    int* storage_;
    size_t index_;
    size_t size_;
    size_t capacity_;
};

int main()
{

    return 0;
}