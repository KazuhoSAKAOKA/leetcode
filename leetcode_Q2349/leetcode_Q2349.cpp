// leetcode_Q2349.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class NumberContainers {
    unordered_map<int, int> index_to_number_map_;
    unordered_map<int, set<int>> number_to_indexes_map_;
public:
    NumberContainers() {

    }

    void change(int index, int number) {
        auto it_index = index_to_number_map_.find(index);
        if (it_index != end(index_to_number_map_)){
            number_to_indexes_map_[it_index->second].erase(index);
            if (number_to_indexes_map_[it_index->second].empty()) {
                number_to_indexes_map_.erase(it_index->second);
            }
            it_index->second = number;
        }
        else {
            index_to_number_map_.insert({ index, number });
        }

        number_to_indexes_map_[number].insert(index);
    }

    int find(int number) {
        auto it = number_to_indexes_map_.find(number);
        if (it == cend(number_to_indexes_map_)) {
            return -1;
        }
        return *cbegin(it->second);
    }
};

int main()
{
    return 0;
}