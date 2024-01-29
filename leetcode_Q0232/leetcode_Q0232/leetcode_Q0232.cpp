// leetcode_Q0232.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <stack>

using namespace std;


class MyQueue {
public:
    MyQueue() {

    }

    void push(int x) {
        _in_buffer.push(x);
    }

    int pop() {
        if (!_out_buffer.empty()) {
            int top = _out_buffer.top();
            _out_buffer.pop();
            return top;
        }
        restack();
        int top = _out_buffer.top();
        _out_buffer.pop();
        return top;
    }

    int peek() {
        if (!_out_buffer.empty()) {
            return _out_buffer.top();
        }
        restack();
        return _out_buffer.top();
    }

    bool empty() {
        return _in_buffer.empty() && _out_buffer.empty();
    }

private:
    stack<int> _in_buffer;
    stack<int> _out_buffer;

    void restack() {
        while (!_in_buffer.empty()) {
            _out_buffer.push(_in_buffer.top());
            _in_buffer.pop();
        }
    }


};



int main()
{
    MyQueue queue;

    queue.push(1);
    queue.push(2);
    queue.push(3);
    cout << queue.peek() << ",expect 1" << endl;
    queue.push(4);
    cout << queue.peek() << ",expect 1" << endl;
    cout << queue.pop() << ",expect 1" << endl;
    cout << queue.pop() << ",expect 2" << endl;
    cout << queue.pop() << ",expect 3" << endl;
    cout << queue.pop() << ",expect 4" << endl;

}

