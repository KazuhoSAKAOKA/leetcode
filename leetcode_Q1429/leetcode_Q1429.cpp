// leetcode_Q1429.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class FirstUnique {
private:
    vector<int> num_queue_;
    unordered_map<int, int> freq_map_;
public:
    FirstUnique(vector<int>& nums) {
        for (auto&& num : nums) {
            const auto [it, bln] = freq_map_.insert({ num,1 });
            if (!bln) {
                it->second++;
            }
            else {
                num_queue_.emplace_back(num);
            }
        }
    }

    int showFirstUnique() {
        for (int i = 0; i < size(num_queue_); i++) {
            if (freq_map_[num_queue_[i]] == 1) {
                return num_queue_[i];
            }
        }
        return -1;
    }

    void add(int value) {
        const auto [it, bln] = freq_map_.insert({ value,1 });
        if (!bln) {
            it->second++;
        }
        else {
            num_queue_.emplace_back(value);
        }

    }
};


int main()
{

    return 0;
}