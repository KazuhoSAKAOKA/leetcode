// leetcode_Q0650.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <optional>

using namespace std;

class Solution {
public:
    using memo_key_t = pair<int, int>;
    using memo_t = map<memo_key_t, optional<int>>;

    static optional<int> rec(int n, int clipboard_len, int current, memo_t& memo) {
        if (n == current) {
            return 0;
        }
        const auto key = memo_key_t(clipboard_len, current);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }
        optional<int> value = nullopt;
        // paste
        if (clipboard_len > 0 && current + clipboard_len <= n) {
            const auto v1 = rec(n, clipboard_len, current + clipboard_len, memo);
            if (v1.has_value()) {
                value = v1.value() + 1;
            }
        }
        // copy
        if (current * 2 <= n && clipboard_len != current) {
            const auto v2 = rec(n, current, current, memo);
            if (v2.has_value()) {
                if (value.has_value()) {
                    value = min(value.value(), v2.value() + 1);
                }
                else {
                    value = v2.value() + 1;
                }
            }
        }
        memo[key] = value;
        return value;
    }

    int minSteps(int n) {
        memo_t memo;
        return rec(n, 0, 1, memo).value();
    }
};

void test(int n) {
    cout << Solution().minSteps(n) << endl;
}

int main()
{
    test(1000);
    test(3);
    test(1);
    return 0;
}