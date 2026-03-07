// leetcode_Q0631.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <string>
#include <set>

using namespace std;


class Excel {
    vector<vector<int>> data_;
    map<pair<int, int>, set<pair<int, int>>> references_;
    map<pair<int, int>, map<pair<int, int>, int>> distributions_;


    static int get_col(char c) {
        return c - 'A';
    }
    static int stoint(const string& s, int offset) {
        int value = 0;
        for (int i = size(s) - 1; i >= offset; i--) {
            value *= 10;
            value += static_cast<int>(s[i] - '0');
        }
        return value;
    }

    static pair<int, int> parse(const string& cell) {
        const string temp = cell.substr(1);
        const int r = stoi(temp) - 1;
        const int c = get_col(cell[0]);
        return { r,c };
    }

    void clear_sum(const pair<int, int>& key) {
        for (auto&& dest: references_[key]) {
            distributions_[dest].erase(key);
        }
        references_[key].clear();
    }
    inline int get(const pair<int, int>& key) {
        return data_[key.first][key.second];
    }

    void set(const pair<int, int>& key, int val) {
        const auto before = data_[key.first][key.second];
        const auto diff = val - before;
        data_[key.first][key.second] = val;
        for (auto&& [dest, mul] : distributions_[key]) {
            set(dest, get(dest) + diff * mul);
        }
    }

public:
    Excel(int height, char width):data_(height, vector<int>(width - 'A' + 1)) {
    }

    void set(int row, char column, int val) {
        auto key = make_pair(row - 1, get_col(column));
        set(key, val);
        clear_sum(key);
    }

    int get(int row, char column) {
        return get(make_pair(row - 1, get_col(column)));
    }

    int sum(int row, char column, vector<string> numbers) {
        auto key = make_pair(row - 1, get_col(column));
        int t = 0;
        map<pair<int, int>, int> new_dists;
        std::set<pair<int, int>> new_refs;

        for (auto&& num : numbers) {
            auto sep = num.find(':');
            if (sep == string::npos) {
                const auto current = parse(num);
                t += get(current);
                new_refs.insert(current);
                new_dists[current]++;
            }
            else {
                const string n1 = num.substr(0, sep);
                const string n2 = num.substr(sep + 1);
                const auto p1 = parse(n1);
                const auto p2 = parse(n2);

                const auto incr = (p1.first <= p2.first ? 1 : -1);
                const auto incc = (p1.second <= p2.second ? 1 : -1);
                for (int r = p1.first; r != (p2.first + incr); r += incr) {
                    for (int c = p1.second; c != (p2.second + incc); c += incc) {
                        const auto current = make_pair(r, c);
                        t += get(current);
                        new_refs.insert(current);
                        new_dists[current]++;
                    }
                }
            }
        }
        set(key, t);
        clear_sum(key);
        references_[key] = new_refs;
        for (auto&& [dest,mul] : new_dists) {
            distributions_[dest][key] = mul;
        }
        return t;
    }
};

static void test1() {
    Excel e(3, 'C');
    e.set(1, 'A', 2);
    cout << e.sum(3, 'C', { "A1","A1:B2" }) << endl;
    e.set(2, 'B', 2);
    cout << e.get(3, 'C') << endl;
}

static void test2() {
    Excel e(3, 'C');
    cout << e.sum(1, 'A', {"A2"}) << endl;
    e.set(2, 'A', 1);
    cout << e.sum(3, 'A', { "A1" }) << endl;
    cout << e.get(1, 'A') << endl;
}

static void test3() {
    Excel e(5, 'E');
    e.set(1, 'A', 1);
    cout << e.sum(2, 'B', { "A1" }) << endl;
    e.set(2, 'B', 0);
    cout << e.get(2, 'B') << endl;
    e.set(1, 'A', 5);
    cout << e.get(2, 'B') << endl;
}

static void test4() {
    Excel e(5, 'E');

    e.set(1, 'A', 5);
    e.set(1, 'B', 3);
    e.set(1, 'C', 2);
    cout << e.sum(1, 'C', { "A1","A1:B1" }) << endl;
    cout << e.get(1, 'C') << endl;
    e.set(1, 'B', 5);
    cout << e.get(1, 'C') << endl;
    cout << e.sum(1, 'B', { "A1:A5" }) << endl;
    e.set(5, 'A', 10);
    cout << e.get(1, 'B') << endl;
    cout << e.get(1, 'C') << endl;
    cout << e.sum(3, 'C', { "A1:C1","A1:A5" }) << endl;
    e.set(3, 'A', 3);
    cout << e.get(1, 'B') << endl;
    cout << e.get(1, 'C') << endl;
    cout << e.get(3, 'C') << endl;
    cout << e.get(5, 'A') << endl;
}

static void test5() {
    Excel e(26, 'Z');
    e.set(1, 'A', 1);
    e.set(1, 'I', 1);
    cout << e.sum(7, 'D', { "A1:D6", "A1:G3", "A1:C12" }) << endl;
    cout << e.sum(10, 'G', { "A1:D7", "D1:F10", "D3:I8", "I1:I9" }) << endl;
}
static void test6() {
    Excel e(5, 'E');
    cout << e.get(1, 'A') << endl;
    e.set(1, 'A', 1);
    cout << e.get(1, 'A') << endl;
    cout << e.sum(2, 'B', { "A1", "A1", }) << endl;
    e.set(1, 'A', 2);
    cout << e.get(2, 'B') << endl;
    cout << e.sum(3, 'C', { "B2", "A1:B2", }) << endl;
    e.set(2, 'B', 0);
    cout << e.get(3, 'C') << endl;
    e.set(1, 'A', 5);
    cout << e.get(2, 'B') << endl;
    cout << e.get(3, 'C') << endl;
}


int main()
{
    test6();
    return 0;
}
