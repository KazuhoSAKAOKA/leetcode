// leetcode_Q0432.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

class AllOne {
public:
    AllOne() {

    }

    void inc(string key) {
        const auto count = freq_map_[key]++;
        if (count > 0) {
            dec_revmap(count, key);
        }
        reverse_map_[count + 1].insert(key);
    }

    void dec(string key) {
        const auto it = freq_map_.find(key);
        if (it == end(freq_map_)) {
            return;//assert
        }
        const auto cur_size = it->second;
        dec_revmap(cur_size, key);

        if (cur_size == 1) {
            freq_map_.erase(it);
        }
        else {
            it->second--;
            reverse_map_[cur_size - 1].insert(key);
        }
    }

    string getMaxKey() {
        if (freq_map_.empty()) {
            return "";
        }
        const auto it = crbegin(reverse_map_);
        return *cbegin(it->second);
    }

    string getMinKey() {
        if (freq_map_.empty()) {
            return "";
        }
        const auto it = cbegin(reverse_map_);
        return *cbegin(it->second);
    }

private:

    void dec_revmap(size_t count, const string& key) {
        auto it = reverse_map_.find(count);
        if (it == end(reverse_map_)) {
            return;//assert
        }
        it->second.erase(key);
        if (it->second.empty()) {
            reverse_map_.erase(it);
        }
    }

    unordered_map<string, size_t> freq_map_;
    map<size_t, set<string>> reverse_map_;
};


int main()
{
    AllOne target;
    target.inc("hello");
    target.inc("hello");
    cout << target.getMaxKey() << endl;
    cout << target.getMinKey() << endl;
    target.inc("leet");
    cout << target.getMaxKey() << endl;
    cout << target.getMinKey() << endl;

    return 0;
}