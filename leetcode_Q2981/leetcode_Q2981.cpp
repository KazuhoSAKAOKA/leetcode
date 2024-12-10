// leetcode_Q2981.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

template <typename T = long long>
T bs(T ok, T ng, std::function<bool(T)> check) {
    while (abs(ng - ok) > 1) {
        const auto mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        }
        else {
            ng = mid;
        }
    }
    return ok;
}
class Solution {
public:
    int maximumLength(string s) {
        vector<map<int, int, std::greater<>>> freqs_map_list(26);

        int streak = 1;
        char before = s.front();
        for (auto i = 1; i < size(s); i++) {
            const auto& c = s[i];
            if (before != c) {
                freqs_map_list[before - 'a'][streak]++;
                streak = 1;
                before = c;
            }
            else {
                streak++;
            }
        }
        freqs_map_list[before - 'a'][streak]++;

        const auto ans = bs<int>(0, size(s), [&](int v) {
            for (auto&& mp : freqs_map_list) {
                if (mp.empty()) { continue; }
                map<int, int> max_map;
                for (auto&& [len, count] : mp) {
                    if (len < v) { break; }
                    max_map[len] += count;
                    if (max_map[len] >= 3) { return true; }
                    if (len - v >= 1) {
                        max_map[len - 1] += count * 2;
                        if (max_map[len - 1] >= 3) { return true; }
                        if (len - v >= 2) {
                            max_map[len - 2] += count * 3;
                            if (max_map[len - 2] >= 3) { return true; }
                        }
                    }
                }
            }
            return false;
            });

        if (ans == 0) { return -1; }
        return ans;
    }
};

void test(string&& s) {
    cout << Solution().maximumLength(s) << endl;
}
int main()
{
    test("aaaa");
    test("abcdef");
    test("abcaba");
    return 0;
}