// leetcode_Q2337.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
class Solution {
public:
    bool canChange(string start, string target) {
        int start_index = 0;
        map<int,int> left_to_right;
        vector<pair<int, int>> right_to_left;

        auto find = [](char c, const string& s, int offset, int endv, int increment) {
            for (int i = offset; i != endv; i += increment) {
                if (s[i] == c) {
                    return i;
                }
                else if (s[i] != '_') {
                    return -1;
                }
            }
            return -1;
            };
        for (int i = 0; i < size(start); i++) {
            if (target[i] == 'L') {
                const auto pos = find('L', start, start_index, size(start), 1);
                if (pos < 0) {
                    return false;
                }
                left_to_right[i] = pos;
                start_index = pos + 1;
            }
            else {
                if (start_index == i) {
                    if (start[start_index] == 'L') {
                        return false;
                    }
                    start_index++;
                }
            }
        }
        start_index = size(start) - 1;
        for (int i = size(start) - 1; i >= 0; i--) {
            if (target[i] == 'R') {
                const auto pos = find('R', start, start_index, -1, -1);
                if (pos < 0) {
                    return false;
                }
                right_to_left.emplace_back(make_pair(pos, i));
                start_index = pos - 1;
            }
            else {
                if (start_index == i) {
                    if (start[start_index] == 'R') {
                        return false;
                    }
                    start_index--;
                }
            }
        }
        for (auto&& r : right_to_left) {
            auto it = left_to_right.lower_bound(r.first);
            for (auto it1 = it; it1 != cend(left_to_right); ++it1) {
                if (r.second < it1->first) {
                    break;
                }
                if (max(r.first, it1->first) < min(r.second, it1->second)) {
                    return false;
                }
            }
        }
        return true;
    }
};

void test(string&& start, string&& target) {
    cout << Solution().canChange(start, target) << endl;
}
int main()
{
    test("R__L", "_LR_");
    test("_L__R__R_", "L______RR");
    test("R_L_", "__LR");
    test("_R", "R_");
    return 0;
}