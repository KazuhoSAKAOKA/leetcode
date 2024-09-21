// leetcode_Q0386.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <set>
#include <cassert>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    vector<int> solve_naive(int n) {
        vector<string> values;
        for (int i = 1; i <= n; i++) {
            values.emplace_back(to_string(i));
        }
        sort(begin(values), end(values));
        vector<int> ans;
        ans.reserve(n);
        transform(cbegin(values), cend(values), back_inserter(ans), [](const auto& a) { return stoi(a); });
        return ans;
    }

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

    vector<int> lexicalOrder(int n) {
        vector<int> ans;
        ans.reserve(n);
        lexi_num current{ "1", };
        ans.emplace_back(1);
        for (int i = 0; i < n - 1; i++) {
            current = get_next(current, n);
            ans.emplace_back(current.to_int());
        }

        return ans;
    }
};

void test(int n) {
    output(Solution().lexicalOrder(n));
}

int main()
{
    output(Solution().solve_naive(10000));
    test(10000);

    test(13);
    test(2);
    return 0;
}