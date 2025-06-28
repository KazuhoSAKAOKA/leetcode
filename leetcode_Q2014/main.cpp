#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>
#include <optional>

using namespace std;
class Solution {
public:

    static bool check(const string& s, int remain, int index, string& current, int cur_index, const vector<vector<int>>& prefix_sumss) {
        if (remain == 0) {
            return true;
        }
        const auto cindex = static_cast<int>(current[cur_index] - 'a');
        if (size(current) == 1) {
            return (prefix_sumss[cindex].back() - prefix_sumss[cindex][index]) >= remain;
        }
        const auto r = s.find(current[cur_index], index);
        if (r == string::npos) {
            return false;
        }

        if (cur_index < size(current) - 1) {
            return check(s, remain, r + 1, current, cur_index + 1, prefix_sumss);
        }
        return  check(s, remain - 1, r + 1, current, 0, prefix_sumss);
    }

    static string rec(const string& s, int k, int index, string& current, vector<int>& cur_used, const vector<vector<int>>& prefix_sumss) {
        if (size(s) == index || (size(s) - index) < size(current) * (k - 1)) {
            return current;
        }
        const auto cindex = static_cast<int>(s[index] - 'a');
        const auto remain = prefix_sumss[cindex].back() - prefix_sumss[cindex][index + 1];
        const auto reserved = cur_used[cindex] * (k - 1);
        const auto usables = remain - reserved;
        string max_len_str = current;
        if (usables >= 0) {
            const auto temp = rec(s, k, index + 1, current, cur_used, prefix_sumss);
            if (size(temp) > size(max_len_str) || (size(temp) == size(max_len_str) && temp > max_len_str)) {
                max_len_str = temp;
            }
        }
        if (usables >= k - 1) {
            current += s[index];
            cur_used[cindex]++;
            if (check(s, k - 1, index + 1, current, 0, prefix_sumss)) {
                if (size(current) > size(max_len_str) || (size(current) == size(max_len_str) && current > max_len_str)) {
                    max_len_str = current;
                }
                const auto temp = rec(s, k, index + 1, current, cur_used, prefix_sumss);
                if (size(temp) > size(max_len_str) || (size(temp) == size(max_len_str) && temp > max_len_str)) {
                    max_len_str = temp;
                }
            }
            cur_used[cindex]--;
            current.pop_back();
        }
        return max_len_str;
    }

    static string tle(string s, int k) {
        const auto n = size(s);
        vector<vector<int>> prefix_sumss(26, vector<int>(n + 1));
        for (int i = 0; i < n; i++) {
            const auto cindex = static_cast<int>(s[i] - 'a');
            prefix_sumss[cindex][i + 1] = 1;

            for (int j = 0; j < 26; j++) {
                prefix_sumss[j][i + 1] += prefix_sumss[j][i];
            }
        }
        string work = "";
        vector<int> cur_used(26);
        return rec(s, k, 0, work, cur_used, prefix_sumss);
    }


    static bool check2(const string& s, int remain, int index, const string& current, int cur_index) {
        if (remain == 0) {
            return true;
        }
        if (size(s) <= index) {
            return false;
        }
        const auto cindex = static_cast<int>(current[cur_index] - 'a');
        const auto r = s.find(current[cur_index], index);
        if (r == string::npos) {
            return false;
        }
        if (cur_index < size(current) - 1) {
            return check2(s, remain, r + 1, current, cur_index + 1);
        }
        return  check2(s, remain - 1, r + 1, current, 0);
    }

    optional<string> generate(const vector<int>& freqs, vector<int>& used, int length, string& current, function<bool(const string&)> pred) {
        if (size(current) == length) {
            if (pred(current)) {
                return current;
            }
            return nullopt;
        }
        for (int i = 0; i < 26; i++) {
            if (freqs[i] - used[i] > 0) {
                used[i]++;
                current += static_cast<char>((26 - i) + 'a' - 1);
                const auto result_opt = generate(freqs, used, length, current, pred);
                if (result_opt.has_value()) {
                    return result_opt;
                }
                current.pop_back();
                used[i]--;
            }
        }
        return nullopt;
    }

    string longestSubsequenceRepeatedK(string s, int k) {
        const auto n = size(s);
        vector<int> freqs(26);
        for (int i = 0; i < n; i++) {
            freqs[26 - (s[i] - 'a') - 1]++;
        }
        int total_count = 0;
        for (auto&& count : freqs) {
            count /= k;
            total_count += count;
        }

        string work = "";
        vector<int> used(26);
        for (int len = total_count; len > 0; len--) {
            const auto result_opt = generate(freqs, used, len, work, [&](const string& current) { return check2(s, k, 0, current, 0); });
            if (result_opt.has_value()) {
                return result_opt.value();
            }
        }
        return "";
    }
};
void test(string&& s, int k) {
    cout << Solution().longestSubsequenceRepeatedK(s, k) << endl;
}
int main() {
    test("letsleetcode", 2);
    test("zyzy", 2);
    test("abab", 2);
    test("sjnjhjjjvkake", 5);
    test("bbabbabbbbabaababab", 3);
    test("bb", 2);
    test("ab", 2);
    return 0;
}