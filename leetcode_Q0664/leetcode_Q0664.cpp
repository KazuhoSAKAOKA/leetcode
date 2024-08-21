// leetcode_Q0664.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
#pragma region 
    static int rec(const string& s, int offset, int len) {
        if (len <= 1) {
            return max(0, len);
        }

        map<int, vector<int>> target_map;

        int max_width = 0;
        vector<int> char_begins(26, -1);
        for (int i = 0; i < len; i++) {
            const int c_index = static_cast<int>(s[i + offset] - 'a');
            if (char_begins[c_index] < 0) {
                char_begins[c_index] = i;
            }
            else {
                const auto w = i - char_begins[c_index] + 1;
                target_map[w].push_back(c_index);
                max_width = max(max_width, w);
            }
        }
        if (target_map.empty()) {
            return len;
        }
        const auto& max_items = target_map[max_width];
        int min_op_count = len;
        for (auto&& target_index : max_items) {
            int count = 1;
            const int current_offset = char_begins[target_index];

            count += rec(s, offset, current_offset);
            count += rec(s, offset + current_offset + max_width, len - (current_offset + max_width));

            auto left = 1;
            while (left < max_width - 1 && s[offset + current_offset + left] == s[offset + current_offset]) {
                left++;
            }
            auto right = max_width - 2;
            while (right > left && s[offset + current_offset + right] == s[offset + current_offset]) {
                right--;
            }
            const auto inner_len = right - left + 1;
            count += rec(s, offset + current_offset + left, inner_len);
            min_op_count = min(min_op_count, count);
        }
        return min_op_count;
    }
    static int greedy_WA(const string& s, int offset, int len) {
        return rec(s, 0, size(s));
    }
#pragma endregion

    static int move_same_chars(const string& s, int offset, int index, int len) {
        int i = 1;
        while (index + i < len && s[offset + index] == s[offset + index + i]) {
            i++;
        }
        return i;
    }

    static int rec2(const string& s, string& current, map<string, int>& memo) {
        //if (s.empty()) {
        //    return 0;
        //}
        //auto it = memo.find(current);
        //if (it != cend(memo)) {
        //    it->second;
        //}


        //const char target = s[index];
        //int current_target_len = move_same_chars(s, index, 0, len);

        //int min_op_count = 1 + rec2(s, index + current_target_len, len - current_target_len, memo);
        //int inner_string_op_count = 0;
        //int current_segment_begin = current_target_len;
        //current_target_len++;
        //while(current_target_len <= len) {
        //    if (s[index + current_target_len - 1] == target) {
        //        const int inner_len = current_target_len - current_segment_begin - 1;
        //        const int inner_count = rec2(s, index + current_segment_begin, inner_len, memo);
        //        inner_string_op_count += inner_count;

        //         const int series = move_same_chars(s, index, current_target_len - 1, len);
        //         current_target_len += series - 1;
        //        //while (current_target_len + 1 < len && s[index + current_target_len + 1] == target) {
        //        //    current_target_len++;
        //        //}

        //        const int op_count = inner_string_op_count + 1 + rec2(s, index + current_target_len, len - current_target_len, memo);
        //        min_op_count = min(min_op_count, op_count);
        //        current_segment_begin = current_target_len;
        //    }
        //    current_target_len++;
        //}
        //memo[index][len] = min_op_count;
        //return min_op_count;
    }

    template<typename MAP, typename KEY, typename VALUE>
    static void set_map_min(MAP& mp, const KEY& key, VALUE value) {
        auto it = mp.find(key);
        if (it == cend(mp)) {
            mp[key] = value;
        }
        else {
            it->second = min(it->second, value);
        }
    }

    int strangePrinter(string s) {

        map<string, int> before;
        string temp(size(s), ' ');
        for (int i = 0; i < size(s); i++) {
            temp[i] = s[0];
            before[temp] = 1;
        }

        for (int i = 1; i < size(s); i++) {
            map<string, int> current;
            for (auto&& [key, v] : before) {
                for (int len = 1; len <= size(s) - i; len++) {
                    auto current_key = key;
                    int cost = 0;
                    for (int k = 0; k < len; k++) {
                        if (current_key[i + k] != s[i]) {
                            cost = 1;
                            current_key[i + k] = s[i];
                        }
                    }
                    set_map_min(current, current_key, v + cost);
                }
            }
            before = current;
        }
        int min_cost = size(s);
        for (auto&& [_, cost]: before) {
            min_cost = min(min_cost, cost);
        }

        return min_cost;

    }
};
void test(string&& s) {
    cout << Solution().strangePrinter(s) << endl;
}
int main()
{
    test("aaabbb");
    test("aba");

    test("aababba");


    test("abacababacab");
    test("leetcode");
    test("abbbba");
    test("abababa");
    return 0;
}