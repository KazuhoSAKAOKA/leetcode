// leetcode_Q0857.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:

    static double rec(const vector<int>& quality, const vector<int>& wage,int index, int remain, vector<int>& current_indexes) {
        if(quality.size() == index && remain == 0){
            auto get_ratio = [&](const auto& index)->double {
                return static_cast<double>(wage[index]) / static_cast<double>(quality[index]);
                };

            const auto base_index = *max_element(cbegin(current_indexes), cend(current_indexes),
                [&](const auto& a, const auto& b) {
                    return get_ratio(a) < get_ratio(b);
                });
            const double base_ratio = get_ratio(base_index);
            const double total = accumulate(cbegin(current_indexes), cend(current_indexes), 0.0,
                [&](const double& a, const auto& b) {
                    const auto v = base_ratio * static_cast<double>(quality[b]);
                    const auto current_cost = max(static_cast<double>(wage[b]), v);
                    return a + current_cost;
                });

            return total;
        }

        if (quality.size() < index + remain) {
            return DBL_MAX;
        }
        double total = rec(quality, wage, index + 1, remain, current_indexes);
        if (remain > 0) {
            current_indexes.emplace_back(index);
            const double total_1 = rec(quality, wage, index + 1, remain - 1, current_indexes);
            current_indexes.pop_back();
            total = min(total, total_1);
        }
        return total;
    }

    static double expect_tle(const vector<int>& quality, const vector<int>& wage, int k) {
        vector<int> current_indexes;
        return rec(quality, wage, 0, k, current_indexes);
    }

    using memo_key_t = tuple<int, int, int>;// index, remain, first_select
    using memo_t = map<memo_key_t, double>;

    static double rec2(const vector<pair<double, int>>& rate_quality, int index, int remain, int first_selected_or_minus, memo_t& memo) {
        if (rate_quality.size() == index && remain == 0) {
            return 0.0;
        }
        if (rate_quality.size() < index + remain) {
            return DBL_MAX;
        }
        const auto key = memo_key_t(index, remain, first_selected_or_minus);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        double total = rec2(rate_quality, index + 1, remain, first_selected_or_minus, memo);

        if (remain > 0) {
            if (0 <= first_selected_or_minus) {
                const double current_value = rate_quality[first_selected_or_minus].first * static_cast<double>(rate_quality[index].second);
                const double total_1 = rec2(rate_quality, index + 1, remain - 1, first_selected_or_minus, memo) + current_value;
                total = min(total, total_1);
            }
            else {
                const double current_value = rate_quality[index].first * static_cast<double>(rate_quality[index].second);
                const double total_1 = rec2(rate_quality, index + 1, remain - 1, index, memo) + current_value;
                total = min(total, total_1);
            }
        }

        memo[key] = total;
        return total;
    }

    static double tle2(vector<int>& quality, vector<int>& wage, int k) {
        vector<pair<double, int>> rate_qualities;
        rate_qualities.reserve(quality.size());
        for (int i = 0; i < quality.size(); i++) {
            rate_qualities.emplace_back(make_pair(static_cast<double>(wage[i]) / static_cast<double>(quality[i]), quality[i]));
        }
        sort(begin(rate_qualities), end(rate_qualities), [](const auto& a, const auto& b) { return a > b; });

        memo_t memo;
        return rec2(rate_qualities, 0, k, -1, memo);
    }

    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        struct QW {
            int quality;
            int wage;
            double get_ratio() const {
                return static_cast<double>(wage) / static_cast<double>(quality);
            }
        };

        vector<QW> qw_list;
        qw_list.reserve(quality.size());
        for (int i = 0; i < quality.size(); i++) {
            qw_list.emplace_back(QW{ quality[i], wage[i] });
        }
        sort(begin(qw_list), end(qw_list), [](const auto& a, const auto& b) { return a.get_ratio() < b.get_ratio(); });

        double min_value = DBL_MAX;
        long long current_quality_total = 0;

        auto comparer = [&](const int& a, const int& b) { return qw_list[a].quality < qw_list[b].quality;  };
        priority_queue<int, vector<int>, decltype(comparer)> p_queue(comparer);
        for (int i = 0; i < qw_list.size();i++){
            p_queue.push(i);
            current_quality_total += qw_list[i].quality;

            if (k < p_queue.size()) {
                const auto top = p_queue.top();
                p_queue.pop();
                current_quality_total -= qw_list[top].quality;
                if (top == i) { continue; }
            }

            if (p_queue.size() == k) {
                min_value = min(min_value, qw_list[i].get_ratio() * current_quality_total);
            }
        }

        return min_value;
    }
};

void test(vector<int>&& quality, vector<int>&& wage, int k) {
    cout << Solution().mincostToHireWorkers(quality, wage, k) << endl;
}

int main() {
    test({ 10,20,5, }, { 70,50,30, }, 2);
    test({ 3,1,10,10,1, }, { 4,8,2,2,7, }, 3);
}
