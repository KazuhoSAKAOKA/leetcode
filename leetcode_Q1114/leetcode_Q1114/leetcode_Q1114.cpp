// leetcode_Q1114.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

class Foo {
public:
    Foo() {

    }

    condition_variable m_condition;
    mutex m_mutex;
    bool m_first_called = false;
    bool m_second_called = false;

    void first(function<void()> printFirst) {
        printFirst();

        unique_lock<mutex> lock(m_mutex);
        m_first_called = true;
        m_condition.notify_all();
    }

    void second(function<void()> printSecond) {
        {
            unique_lock<mutex> lock(m_mutex);
            m_condition.wait(lock, [this]() { return m_first_called; });
        }
        printSecond();
        {
            unique_lock<mutex> lock(m_mutex);
            m_second_called = true;
            m_condition.notify_all();
        }
    }

    void third(function<void()> printThird) {
        {
            unique_lock<mutex> lock(m_mutex);
            m_condition.wait(lock, [this]() { return m_first_called && m_second_called; });
        }
        printThird();
    }
};

int main()
{
}

