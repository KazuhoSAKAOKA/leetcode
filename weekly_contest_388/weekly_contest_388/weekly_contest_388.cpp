// weekly_contest_388.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <string>
using namespace std;

namespace problem1 {

class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        const int total_apples = accumulate(cbegin(apple), cend(apple), 0, [](const auto a, const auto b) { return a + b; });
        sort(begin(capacity), end(capacity), [](const auto a, const auto b) { return a > b; });
        int remain = total_apples;
        int index = 0;
        while (remain > 0 && index < capacity.size()) {
            remain -= capacity[index];
            index++;
        }
        return index;
    }
};

void test(vector<int>&& apple, vector<int>&& capacity) {
    cout << Solution().minimumBoxes(apple, capacity) << endl;
}

void run() {
    test({ 1,3,2 }, { 4,3,1,5,2 });
    test({ 5,5,5 }, { 2,4,2,7 });
}

}

namespace problem2 {

class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        sort(begin(happiness), end(happiness), [](const auto a, const auto b) { return a > b; });
        
        long long total = 0;
        for (int i = 0; i < min(k, static_cast<int>(happiness.size())); i++) {
            total += static_cast<long long>(max(0, happiness[i] - i));
        }
        return total;
    }
};

void test(vector<int>&& happiness, int k) {
    cout << Solution().maximumHappinessSum(happiness, k) << endl;
}

void run() {
    test({ 1,2,3 }, 2);
    test({ 1,1,1,1,}, 2);
    test({ 2,3,4,5,}, 1);
}

}

namespace problem3 {

class Solution {
public:

    static void enum_substrings(const string& arr, int index, string& current, set<string>& ans) {
        if (arr.size() <= index) {
            return;
        }
        current += arr[index];
        ans.emplace(current);
        for (int i = 1; index + i < arr.size(); i++) {
            current += arr[index + i];
            ans.emplace(current);
        }
        for (int i = 0; index + i < arr.size(); i++) {
            current.pop_back();
        }
        enum_substrings(arr, index + 1, current, ans);
    }

    static string get_not_occurs(const vector<set<string>>& sets, int index) {
        map<int, set<string>> values;

        auto contains = [&](const string& s) {
                for (int i = 0; i < sets.size(); i++) {
                    if (i == index) { continue; }
                    if (sets[i].find(s) != cend(sets[i])) { return true; }
                }
                return false;
            };

        int min_len = INT_MAX;
        const auto& target = sets[index];
        for (auto&& substr : target) {
            if (contains(substr)) {
                continue;
            }
            values[substr.size()].emplace(substr);
            min_len = min(static_cast<int>(substr.size()), min_len);
        }


        if (values.empty()) {
            return "";
        }
        return *cbegin(values[min_len]);
    }

    vector<string> shortestSubstrings(vector<string>& arr) {
        vector<set<string>> sub_strs;
        sub_strs.reserve(arr.size());
        for (auto&& values : arr) {
            set<string> temp;
            string current;
            enum_substrings(values, 0, current, temp);
            sub_strs.emplace_back(temp);
        }
        vector<string> ans;
        for (auto i = 0; i < sub_strs.size(); i++) {
            ans.emplace_back(get_not_occurs(sub_strs, i));
        }
        return ans;
    }
};

void test(vector<string>&& arr) {
    const auto ans = Solution().shortestSubstrings(arr);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

void run() {
    test({ "cab","ad","bad","c" });
    test({ "abc","bcd","abcd" });
}

}


namespace problem4 {
class Solution {
public:

    static void get_max_or_min_subarrsum(const vector<int>& nums, vector<bool>& used, int index, long long current, pair<long long, vector<bool>>& target, bool is_max) {
        if (nums.size() <= index) {
            return;
        }

        if (!used[index]) {
            auto current_used(used);
            auto current_value = current + nums[index];
            current_used[index] = true;

            if (is_max) {
                if (target.first < current_value) {
                    target.first = current_value;
                    target.second = current_used;
                }
            }
            else {
                if (target.first > current_value) {
                    target.first = current_value;
                    target.second = current_used;
                }
            }

            for (int i = 1; index + i < nums.size(); i++) {
                current_value += nums[index + i];
                current_used[index + i] = true;
                if (is_max) {
                    if (nums[index + i] < 0) {
                        break;
                    }
                    if (target.first < current_value) {
                        target.first = current_value;
                        target.second = current_used;
                    }
                }
                else {
                    if (nums[index + i] > 0) {
                        break;
                    }
                    if (target.first > current_value) {
                        target.first = current_value;
                        target.second = current_used;
                    }
                }
            }
        }
        get_max_or_min_subarrsum(nums, used, index + 1, current, target, is_max);
    }


    long long maximumStrength(vector<int>& nums, int k) {
        long long total = 0;
        vector<bool> used(nums.size(), false);
        for (int i = 0; i < k; i++) {
            const auto x = k - i;
            bool is_max;
            
            pair<long long, vector<bool>> target = make_pair(0LL, used);
            if (i % 2 == 0) {
                is_max = true;
                target.first = LLONG_MIN;
            }
            else {
                is_max = false;
                target.first = LLONG_MAX;
            }
            get_max_or_min_subarrsum(nums, used, 0, 0, target, is_max);

            if (i % 2 == 0) {
                total += target.first * x;
                used = target.second;
            }
            else {
                total -= target.first * x;
                used = target.second;
            }
        }
        return total;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maximumStrength(nums, k) << endl;

}

void run() {
    test({ 1,2,3,-1,2 }, 3);
    test({ 12,-2,-2,-2,-2 }, 5);
    test({ -1,-2,-3 }, 1);
}

}

int main()
{

//	problem1::run();
//    problem2::run();
//    problem3::run();
    problem4::run();
}