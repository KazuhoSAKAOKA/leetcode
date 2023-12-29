// leetcode_Q0170.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class TwoSum {
public:
    TwoSum() {

    }

    void add(int number) {
        for (auto&& v : m_values) {
            m_sums.insert(v + number);
        }
        m_values.insert(number);
    }

    bool find(int value) {
        return m_sums.find(value) != cend(m_sums);
    }

private:
    unordered_set<int> m_values;
    unordered_set<int> m_sums;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */


int main()
{
    TwoSum obj;
    obj.add(0);
    std::cout << obj.find(0) << std::endl;
}

