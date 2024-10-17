// leetcode_Q0670.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>
#include <map>


using namespace std;

class Solution {
public:
    int maximumSwap(int num) {

        auto val = to_string(num);
        map<char, int> right_map;
        for (int i = size(val) - 1; i >= 0; i--) {
            auto it = right_map.insert(make_pair(val[i], i));
        }

        auto check = [&](int cur_index)-> pair<bool, int> {
            const char cur = val[cur_index];
            for (auto it = crbegin(right_map); it != crend(right_map); ++it) {
                if (it->first <= cur) {
                    return { false, 0 };
                }
                if (cur_index < it->second) {
                    return { true, it->second };
                }
            }
            return { false,0 };
            };

        for (int i = 0; i < size(val); i++) {
            const auto [r, index] = check(i);
            if (r) {
                swap(val[i], val[index]);
                break;
            }
        }
        return stoi(val);
    }
};

void test(int num) {
    cout << Solution().maximumSwap(num) << endl;
}

int main()
{
    test(98368);
    test(2736);
    test(9973);
    return 0;
}