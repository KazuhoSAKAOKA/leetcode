// leetcode_Q0440.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <cassert>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:


    struct lexi_num {
        string value_;
        bool operator<(const lexi_num& other) const {
            for (size_t i = 0; i < min(size(value_), size(other.value_)); i++) {
                if (value_[i] != other.value_[i]) {
                    return value_[i] < other.value_[i];
                }
            }
            return size(value_) < size(other.value_);
        }
        int to_int() const {
            return stoi(value_);
        }

        optional<lexi_num> increment() const {
            if (value_.back() == '9') {
                return nullopt;
            }
            auto temp(value_);
            temp.back() = temp.back() + static_cast<char>(1);
            return lexi_num{ temp };
        }
        lexi_num multiple() const {
            return lexi_num{ value_ + '0' };
        }
        optional<lexi_num> back() const {
            if (size(value_) == 1) { return nullopt; }
            auto temp = value_.substr(0, size(value_) - 1);
            while (!temp.empty() && temp.back() == '9') {
                temp.pop_back();
            }
            if (temp.empty()) {
                return nullopt;
            }
            temp.back() = temp.back() + static_cast<char>(1);
            return lexi_num{ temp, };
        }
    };

    lexi_num get_next(const lexi_num& current, int limit) {
        set<lexi_num> candidates;
        auto candidate1 = current.multiple();
        if (candidate1.to_int() <= limit) {
            candidates.insert(candidate1);
        }
        auto candidate2 = current.increment();
        if (candidate2.has_value() && candidate2.value().to_int() <= limit) {
            candidates.insert(candidate2.value());
        }
        auto candidate3 = current.back();
        if (candidate3.has_value() && candidate3.value().to_int() <= limit) {
            candidates.insert(candidate3.value());
        }
        assert(!candidates.empty());
        return *cbegin(candidates);
    }

    int tle(int n, int k) {
        lexi_num current{ "1", };
        for (int i = 0; i < k - 1; i++) {
            current = get_next(current, n);
        }
        return current.to_int();
    }

    static vector<int> create_columns(int value) {
        int current = value;
        vector<int> columns;
        while (current > 0) {
            columns.emplace_back(current % 10);
            current /= 10;
        }
        return vector<int>(crbegin(columns), crend(columns));
    }

    static int rec(const vector<int>& limit_columns, int target, bool lower, int current_index, int counted) {
        if (lower && size(limit_columns) == target) {
            return 10;
        }
        else {

        }
    }

    int findKthNumber(int n, int k) {
        const vector<int> limit = create_columns(n);
    }
};

void test(int n, int k) {
    cout << Solution().findKthNumber(n, k) << endl;
}

int main()
{
    test(13, 2);
    test(1, 1);
    return 0;
}